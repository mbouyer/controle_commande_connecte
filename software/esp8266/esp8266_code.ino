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
#include <ESP_EEPROM.h>
#include "../pic_controle/i2c.h"
#include "wifi_params.h"

#define SDA_PIN 2
#define SCL_PIN 4
#define DATA_READY  16

#define VERSIONM 0
#define VERSIONm 3

#define EEPROM_VERSION 0x01
#define EEPROM_SIZE 16 // overkill but minimum is 16

// #define NO_PIC 1 // emulation mode

#ifdef NO_PIC
unsigned long no_pic_emultime = 0;
#define NO_PIC_UPDATE 20000 // 20s
float no_pic_press;
#endif

unsigned short runtime;
unsigned int milliruntime;
unsigned long runtime_last;

#define DISP_UPDATE 500 //ms
unsigned long disp_up_last = 0;

// motor status
bool motor_on = 0;

// sensors
unsigned char press;
unsigned char target_press = 115;
unsigned int current;

// ETA compute
#define ETA_SAMPLES 5
unsigned char previous_press[ETA_SAMPLES];
unsigned long eta_millis;
short etatime;


// buttons
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

#ifndef NO_PIC
	while ((ret = i2c_write(I2C_W_FLAGS, flags)) != 0) {
		LCDClear();
		sprintf(buf, "write pic %d", ret);
		Serial.println(buf);
		LCDStr(5, 2, buf, 0, 5); 
		delay(500);
	}
#endif
}

static void
time2str(char *buf, int time) {
	sprintf(buf, "%dh%02d", time / 60, time % 60);
}

static void
etatime2str(char *buf) {
	if (etatime == 0) {
	    sprintf(buf, "----");
	} else if (etatime >= 60 * 10) {
	    sprintf(buf, "++++");
	} else {
	    time2str(buf, etatime);
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

static String
getContentType(String filename) {
	if(filename.endsWith(".html")) return "text/html";
	else if(filename.endsWith(".css")) return "text/css";
	else if(filename.endsWith(".js")) return "application/javascript";
	else if(filename.endsWith(".png")) return "image/png";
	else if(filename.endsWith(".gif")) return "image/gif";
	else if(filename.endsWith(".jpg")) return "image/jpeg";
	else if(filename.endsWith(".ico")) return "image/x-icon";
	else if(filename.endsWith(".xml")) return "text/xml";
	return "text/plain";
}



static void
handleNotFound(AsyncWebServerRequest *request)
{
	String filename = "/http" + request->url();

	if(SPIFFS.exists(filename)) {
		request->send(SPIFFS, filename, getContentType(filename));
		return;
	}
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
	char ee_version;

	delay(1000);
	Serial.begin(57600);
	Serial.println();
	Serial.println("Configuring access point...");
	WiFi.softAP(WIFI_SSID, WIFI_PASS, 1, false, 8);
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
#ifndef NO_PIC
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
#endif
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

	EEPROM.begin(EEPROM_SIZE);
	EEPROM.get(0, ee_version);
	if (ee_version != EEPROM_VERSION) {
		sprintf(buf, "bad eeprom %d", ee_version);
		LCDStr(0, 4, buf, 1, 5); 
		Serial.println(buf);
		ee_version = EEPROM_VERSION;
		EEPROM.put(0, ee_version);
		runtime = 0;
		EEPROM.put(1, runtime);
		while (!digitalRead(DATA_READY)) {
			delay(100);
		}
		if (!EEPROM.commit()) {
			sprintf(buf, "ee commit fail");
			LCDStr(0, 4, buf, 1, 5); 
			Serial.println(buf);
			while (!digitalRead(DATA_READY)) {
				delay(100);
			}
		}
	} else {
		sprintf(buf, "eeprom version %d, runtime ", ee_version);
		Serial.print(buf);
		EEPROM.get(1, runtime);
		time2str(buf, runtime * 10);
		LCDStr(5, 4, buf, 0, 5); 
		Serial.println(buf);
	}
	milliruntime = 0;
	etatime = 0;

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
			  
		// handle stop request
		server.on("/stop", HTTP_POST, [](AsyncWebServerRequest *request){
		  do_motor(0);
		  request->redirect(String("http://") + toStringIp(local_IP));
		  });
		// get plain sensors values
		server.on("/sensors", HTTP_GET, [](AsyncWebServerRequest *request){
		    char buf[80];
		    char buf_horam[10];
		    char buf_eta[10];

		    time2str(buf_horam, runtime * 10);
		    etatime2str(buf_eta);
		    sprintf(buf, "%3d:%3d:%2d.%d:%d:%s:%s:%d:", press*2,
			target_press*2, current / 10, current % 10, motor_on,
			buf_horam, buf_eta, WiFi.softAPgetStationNum());
		    request->send(200, "text/plain", buf);
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
	int i;

	dnsServer.processNextRequest();

#define MY_AMP    0
#define MY_PRES    (I2C_R_PRES - I2C_R_AMP)

#ifdef NO_PIC
	if ((millis() - no_pic_emultime) > NO_PIC_UPDATE) {
		no_pic_emultime = millis();
		buttons_state = 0;
		if (press < target_press) {
			if (!motor_on) {
				no_pic_press = 10;
				do_motor(1);
				do_disp_up = 1;
				eta_millis = runtime_last = millis();
				previous_press[0] = press;
				for (i = 1; i < ETA_SAMPLES; i++)
					previous_press[i] = 0xff;
				etatime = 0;
				LCDClear();
				LCDUpdate();
			} else {
				no_pic_press += (target_press - no_pic_press) * (NO_PIC_UPDATE / 1000) / 3600.0;
				press = no_pic_press;
				current = 98;
			}
		}
	}
#else // NO_PIC
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
			if (motor_on && !(buttons_state & I2C_BUTTONS_STOP)) {
				do_motor(0);
				do_disp_up = 1;
				LCDClear();
				LCDUpdate();
				etatime = 0;
			}
		} else if (!motor_on && (buttons & I2C_BUTTONS_START) &&
		    !(buttons_state & I2C_BUTTONS_START)) {
			if (press < target_press) {
				do_motor(1);
				do_disp_up = 1;
				eta_millis = runtime_last = millis();
				previous_press[0] = press;
				for (i = 1; i < ETA_SAMPLES; i++)
					previous_press[i] = 0xff;
				etatime = 0;
				LCDClear();
				LCDUpdate();
			} else {
				do_press_inv = do_disp_up = 1;
			}
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
#endif // NO_PIC
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

		sprintf(buf, "%d", WiFi.softAPgetStationNum());
		LCDStr(0, 0, buf, 0, 5);

#ifndef NO_PIC
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
#endif

		if (press >= target_press) {
			do_motor(0);
		}

		sprintf(buf, "%3d", press * 2);
		LCDStr(0, 1, buf, do_press_inv, 10); 
		Serial.println(buf);

		sprintf(buf, "%3d", target_press * 2);
		LCDStr(42, 1, buf, do_press_inv, 10); 
		Serial.println(buf);

		if (motor_on) {
			int old_milliruntime = milliruntime;
			sprintf(buf, "%2d.%dA", current / 10, current % 10);
			LCDStr(5, 5, buf, 0, 5); 
			Serial.println(buf);
			milliruntime += (millis() - runtime_last);
			runtime_last = millis();
			/* update runtime every 10mn, with proper rounding */
			if (old_milliruntime < 300000 && 
			    milliruntime > 300000) {
				runtime += 1;
				EEPROM.put(1, runtime);
				EEPROM.commit();
			} else if (milliruntime > 600000) {
				milliruntime -= 600000;
			}

			if ((millis() - eta_millis) >= 60000) {
				eta_millis = millis();
				/* find first valid sample */
				for (i = ETA_SAMPLES - 1; i >= 0; i--) {
					if (previous_press[i] != 0xff)
						break;
				}
				int delta_xs = ((int)press - (int)previous_press[i]);
				if (delta_xs <= 0) {
					etatime = 32767;
				} else {
					float barspermin = 
					    (float)delta_xs / ((float)i + 1);
					etatime = ((float)target_press - (float)press) / barspermin + 0.5;
				}
				for (i = ETA_SAMPLES - 1; i > 0; i--) {
					previous_press[i] = previous_press[i-1];
				}
				previous_press[0] = press;

			}
			etatime2str(buf);
			LCDStr(40, 3, buf, 0, 10);
			Serial.println(buf);
		} else {
			time2str(buf, runtime * 10);
			LCDStr(5, 5, buf, 0, 5);
			Serial.println(buf);
		}
		disp_up_last = millis();
	}
}
