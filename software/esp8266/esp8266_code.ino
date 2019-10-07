/*
 * Copyright (c) 2019 Manuel BOUYER
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <LCD_3310.h>
#include <Wire.h>
#include <FS.h>
#include "../pic_controle/i2c.h"

#define SDA_PIN 2
#define SCL_PIN 4
#define DATA_READY  16

#define VERSIONM 0
#define VERSIONm 1

#define DISP_UPDATE 500 //ms
unsigned long disp_up_last = 0;

// motor status
bool motor_on = 0;

// sensors
unsigned char press;
unsigned char target_press = 115;
unsigned int current;

unsigned char buttons_state;
unsigned long plusminus_timer;
#define PLUSMINUS_SLOW 1000 // 1s
#define PLUSMINUS_FAST 3000 // 3s

// Access Point

const IPAddress local_IP(192,168,1,1);
const IPAddress subnet(255,255,255,0);

AsyncWebServer server(80);
DNSServer dnsServer;

static int
i2c_write(char reg, char value)
{
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(reg);
	Wire.write(value);
	return Wire.endTransmission();
	// 0:success
	// 1:data too long to fit in transmit buffer
	// 2:received NACK on transmit of address
	// 3:received NACK on transmit of data
	// 4:other error
}

static int
i2c_read(char reg, char *v, char count)
{
	int ret;
	int i;

	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(reg);
	ret = Wire.endTransmission();
	if (ret != 0)
		return -ret;

	Wire.requestFrom(I2C_ADDRESS, count);
	ret = Wire.available();
	for (i = 0; i < ret; i++) {
		v[i] = Wire.read();
	}
	return ret;
}

static void
do_motor(bool m)
{
	unsigned char flags = 0;
	int ret;
	char buf[17];

	motor_on = m;
	if (motor_on)
		flags |= I2C_FLAGS_MOTOR;

	while ((ret = i2c_write(I2C_W_FLAGS, flags)) != 0) {
		LCDClear();
		sprintf(buf, "write pic %d", ret);
		Serial.println(buf);
		LCDStr(5, 2, buf, 0, 5); 
		delay(500);
	}
}

static String
toStringIp(IPAddress ip) {
	String res = "";
	for (int i = 0; i < 3; i++) {
		res += String((ip >> (8 * i)) & 0xFF) + ".";
	}
	res += String(((ip >> 8 * 3)) & 0xFF);
	return res;
}

static void
handleNotFound(AsyncWebServerRequest *request) {
	Serial.print("request for http://");
	Serial.print(request->host());
	Serial.println(request->url());
	request->redirect(String("http://") + toStringIp(local_IP));
}

String
fill_html(const String& var)
{
	char buf[10];
	if(var == "PRESS") {
		return String(press*2);
	} else if (var == "CONS") {
		return String(target_press*2);
	} else if (var == "AMPS") {
		sprintf(buf, "%d.%d", current / 10, current % 10);
		return String(buf);
	}
	Serial.print("unknown HTML tag ");
	Serial.println(var);
	return String("");
}


void
setup() {
	char v[2];
	char buf[80];
	int ret, i;

	delay(1000);
	Serial.begin(57600);
	Serial.println();
	Serial.println("Configuring access point...");
	WiFi.softAP("interface de controle", "Projet_SESI",1,false,8);
	WiFi.softAPConfig(local_IP, local_IP, subnet);

	Serial.print("AP IP address: ");
	Serial.println(local_IP);

	/* Setup the DNS server redirecting all the domains to the apIP */
	dnsServer.setTTL(300);
	dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
	dnsServer.start(53, "*", local_IP);


	Wire.begin(SDA_PIN,SCL_PIN);
	Wire.setClock(100000); // clock 100KHz
	pinMode(16, INPUT);  // Data_ready

	LCDInit();
	LCDContrast (0x60);
	LCDClear();
	LCDUpdate();

	sprintf(buf, "aperosafe %d.%d", VERSIONM, VERSIONm);
	Serial.println("wait on PIC");
	LCDStr(5, 2, "wait on pic", 0, 5);
	while ((ret = i2c_read(I2C_R_VERSM, v, 2)) != 2) {
		sprintf(buf, "wait on pic %d", ret);
		Serial.println(buf);
		delay(500);
	}
	if (v[0] != PIC_VERSIONM) {
		sprintf(buf, "wrong pic %d.%d", v[0], v[1]);
		LCDStr(5, 2, buf, 0, 5); 
		Serial.println(buf);
		while (1) {
			delay(500);
		}
	}
	LCDClear();
	LCDUpdate();
	LCDStr(0, 1, "aperosafe", 0, 5); 
	Serial.println("aperosafe");
	sprintf(buf, "version %d.%d", VERSIONM, VERSIONm);
	LCDStr(5, 2, buf, 0, 5); 
	Serial.println(buf);
	sprintf(buf, "pic %d.%d", v[0], v[1]);
	LCDStr(5, 3, buf, 0, 5); 
	Serial.println(buf);
	// wait 10s, unless key press
	for (i = 0; i < 100; i++) {
		if (digitalRead(DATA_READY))
			break;
		delay(100);
	}
	if (!SPIFFS.begin()) {
		LCDClear();
		LCDStr(0, 1, "FS fail", 0, 10); 
		Serial.println("FS fail");
		while (!digitalRead(DATA_READY)) {
			delay(100);
		}
	} else {
		FSInfo fs_info;
		if (SPIFFS.info(fs_info)) {
			sprintf(buf, "tot %d used %d bs %d ps %d mo %d mp %d",
			    fs_info.totalBytes,
			    fs_info.usedBytes,
			    fs_info.blockSize,
			    fs_info.pageSize,
			    fs_info.maxOpenFiles,
			    fs_info.maxPathLength);
			    Serial.println(buf);
		}
		Dir dir = SPIFFS.openDir("/http");
		while (dir.next()) {
			Serial.print(dir.fileName());
			File f = dir.openFile("r");
			Serial.println(f.size());
		}
		// Route for root / web page
		server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
		  request->send(SPIFFS, "/http/index.html", String(), false, fill_html);
		  });
			  
		// Route to load style.css file
		server.on("/as.css", HTTP_GET, [](AsyncWebServerRequest *request){
		  request->send(SPIFFS, "/http/as.css", "text/css");
		  });
		server.on("/stop", HTTP_POST, [](AsyncWebServerRequest *request){
		  do_motor(0);
		  request->redirect(String("http://") + toStringIp(local_IP));
		  });

		server.onNotFound(handleNotFound);
		server.begin();
		Serial.println("HTTP server started");
	}
	LCDClear();
	LCDUpdate();
}

void loop() {
	char buf[17];
	char v[2];
	char buttons;
	int ret;
	bool do_disp_up = 0;
	bool do_press_inv = 0;
	unsigned long bt_time;

	dnsServer.processNextRequest();

	sprintf(buf, "%d", WiFi.softAPgetStationNum());
	LCDStr(0, 0, buf, 0, 5);

#define MY_AMP    0
#define MY_PRES    (I2C_R_PRES - I2C_R_AMP)

	if (digitalRead(DATA_READY)) {
		if ((ret = i2c_read(I2C_R_BUTTONS, &buttons, 1)) != 1) {
			LCDClear();
			sprintf(buf, "read pic %d", ret);
			Serial.println(buf);
			LCDStr(5, 2, buf, 0, 5); 
			delay(500);
			return;
		}
		sprintf(buf, "buttons %x", buttons);
		Serial.println(buf);
		if (buttons & I2C_BUTTONS_STOP) {
			if (motor_on && !(buttons_state & I2C_BUTTONS_STOP))
				do_motor(0);
		} else if (!motor_on && (buttons & I2C_BUTTONS_START) &&
		    !(buttons_state & I2C_BUTTONS_START)) {
			if (press < target_press)
				do_motor(1);
			else
				do_press_inv = do_disp_up = 1;
		}
		if ((buttons & (I2C_BUTTONS_PLUS | I2C_BUTTONS_MINUS)) !=
		    (I2C_BUTTONS_PLUS | I2C_BUTTONS_MINUS)) {
			if ((buttons & I2C_BUTTONS_PLUS) &&
			    !(buttons_state & I2C_BUTTONS_PLUS)) {
				if (target_press < 125) {
					target_press++;
				}
				plusminus_timer = millis();
				do_disp_up = 1;
			} else if ((buttons & I2C_BUTTONS_MINUS) &&
			    !(buttons_state & I2C_BUTTONS_MINUS)) {
				if (target_press > 0) {
					target_press--;
				}
				plusminus_timer = millis();
				do_disp_up = 1;
			}
		}
		buttons_state = buttons;
	}
	if ((buttons_state & (I2C_BUTTONS_PLUS | I2C_BUTTONS_MINUS)) != 0 &&
	    (buttons_state & (I2C_BUTTONS_PLUS | I2C_BUTTONS_MINUS)) !=
	    (I2C_BUTTONS_PLUS | I2C_BUTTONS_MINUS)) {
		bt_time = millis() - plusminus_timer;
		if (bt_time > PLUSMINUS_FAST &&
		    (target_press % 5) == 0) {
			if (buttons_state & I2C_BUTTONS_PLUS) {
				if (target_press <= 120) {
					target_press+= 5;
					do_disp_up = 1;
				}
			} else {
				if (target_press >= 5) {
					target_press-= 5;
					do_disp_up = 1;
				}
			}
		} else if (bt_time > PLUSMINUS_SLOW) {
			if (buttons_state & I2C_BUTTONS_PLUS) {
				if (target_press < 125) {
					target_press++;
					do_disp_up = 1;
				}
			} else {
				if (target_press > 0) {
					target_press--;
					do_disp_up = 1;
				}
			}
		}
	}

	if (millis() - disp_up_last > DISP_UPDATE || do_disp_up) {
		if ((ret = i2c_read(I2C_R_AMP, v, (MY_PRES + 1))) != (MY_PRES + 1)) {
			LCDClear();
			sprintf(buf, "read pic %d", ret);
			Serial.println(buf);
			LCDStr(5, 2, buf, 0, 5); 
			delay(100);
			return;
		}
		press = v[MY_PRES];
		current = v[MY_AMP];

		if (press >= target_press) {
			do_motor(0);
		}

		sprintf(buf, "%3d", press * 2);
		LCDStr(0, 1, buf, do_press_inv, 10); 
		Serial.println(buf);

		sprintf(buf, "%3d", target_press * 2);
		LCDStr(42, 1, buf, do_press_inv, 10); 
		Serial.println(buf);

		sprintf(buf, "%2d.%dA", current / 10, current % 10);
		LCDStr(5, 5, buf, 0, 5); 
		Serial.println(buf);
		disp_up_last = millis();
	}
}