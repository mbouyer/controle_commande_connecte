/*
 * Copyright (c) 2019 Manuel Bouyer
 *
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
#include <pic18fregs.h>
#include <stdio.h>
#include <math.h>
#include <my_serial.h>

#define PIC_VERSIONM 0x00
#define PIC_VERSIONm 0x01

extern char stack;
extern char stack_end;
#pragma stack 0x100 256
void _reset (void) __naked __interrupt 0;
void _startup (void) __naked;
static char counter_1hz;	
static volatile short counter_10hz;	
static volatile unsigned char softintrs;
#define INT_10HZ	 (unsigned char)0x01
#define INT_AD		 (unsigned char)0x02
#define INT_I2CFL	 (unsigned char)0x04

#define TIMER0_5MS 192 /* 48 without PLL */

#define TIMER2_10HZ 200

#define CLRWDT __asm__("clrwdt")
#define SLEEP __asm__("sleep")

static unsigned short ad_value;
static unsigned short ad_sense;
static unsigned short ad_ref;
static unsigned char cur_amps;
static unsigned char cur_press;

volatile unsigned char ad_state;
#define ADS_TIMERSTART	(unsigned char)0x01
#define ADS_CURR_REF	(unsigned char)0x02
#define ADS_CURR_SENSE	(unsigned char)0x04
#define ADS_PRESS	(unsigned char)0x08

/* ADC channels */
#define ADC_CUR_REF	0x00
#define ADC_CUR_SENSE	0x02
#define ADC_PRESS	0x11
#define ADC_GND		0x3c  /* 11 1100 */

/*
 * number of samples for current. With a 2Khz timer we'll need 40 samples
 * to capture a full AC cycle. Lets capture 2 cycles. As we do 2 measures
 * per samble this has to be 160
 */
#define ADC_NSMPLSAC	160

/*
 * number of samples for pressures. The ADC is 10 bits, the accumulator
 * is 16, so we can to up to 2^6 = 64 samples.
 */
#define ADC_NSMPLSP	64

/* I2C slave definitions */
#include "i2c.h"
unsigned char i2c_curreg; /* register pointer */
unsigned char i2c_reg_data; /* are we receiving reg pointer or data */
unsigned char i2c_flags; /* current flags */
unsigned char i2c_buttons; /* buttons status */

unsigned char i2cs_a, i2cs_r, i2cs_w, i2cs_s;

#define BUT_START	PORTBbits.RB2
#define BUT_STOP	PORTBbits.RB3
#define BUT_PLUS	PORTBbits.RB5
#define BUT_MINUS	PORTBbits.RB4
unsigned char but_start;
unsigned char but_stop;
unsigned char but_plus;
unsigned char but_minus;

#define OUT_MOTOR	LATCbits.LATC7
#define OUT_DATAR	LATCbits.LATC2

#define PRINTHEX(v) \
	{ \
		unsigned char c = (v); \
		if (c < 10) { \
			putchar('0' + c); \
		} else { \
			putchar(('a' - 10) + c ); \
		} \
	}

void
main(void) __naked
{
	unsigned char c;
	softintrs = 0;
	counter_1hz = 10;	

	/* everything is low priority by default */
	IPR1 = 0;
	IPR2 = 0;
	IPR3 = 0;
	IPR4 = 0;
	IPR5 = 0;
	IPR6 = 0;
	IPR7 = 0;
	INTCON = 0;
	INTCONbits.IPEN=1; /* enable interrupt priority */
	
	/* setup ADC and analog inputs */
	ANSELB=0x00; /* port B all digital */
	ANSELC = 0x01; //Set RC1 to analog, others digital
	TRISCbits.TRISC1 = 1;
	ANSELA = 0x05; //Set RA0 & RA2 to analog, others digital
	TRISAbits.TRISA0 = 1;
	TRISAbits.TRISA2 = 1;

	ADCON0 = 0;
	ADCON1 = 0;
	ADCON2 = 0x01; /* accumulate mode */
	ADCON0bits.ADFM = 1; /* right justify */
	ADCON0bits.ADON = 1;
	ADCLK=0x2e; /* Fosc / 64, 1us */
	ADACQ=10; /* 10us aquisition */
	ADREF=0;
	PIR1bits.ADIF = 0;
	PIE1bits.ADIE = 0;

	FVRCON = 0x82; /* fvr on, ADC output 2.048v */

	/* configure timer0 as free-running counter at 62.5Khz */
	T0CON0 = 0x10; /* 16bits, 1:1 postscaler */
	T0CON1 = 0x48; /* F0sc/4, 1:256 prescaler */
	PIR0bits.TMR0IF = 0;
	PIE0bits.TMR0IE = 0; /* no interrupt */
	T0CON0bits.T0EN = 1;
	
	USART_INIT(0);
	stdout = STREAM_USER; /* Use the macro PUTCHAR with printf */

#if TIMER2_10HZ == 100
	/* configure timer2 for 1Khz interrupt */
	T2CON = 0x64; /* postscaller 1/5, prescaler 1/64 */
	PR2 = 200; /* 1khz output */
#elif TIMER2_10HZ == 200
	/* configure timer2 for 1Khz interrupt */
	T2CON = 0x64; /* postscaller 1/5, prescaler 1/64 */
	PR2 = 100; /* 2khz output */
#else
#error "unknown TIMER2_10HZ"
#endif
	T2CLK = 0x02; /* Fosc */
	counter_10hz = TIMER2_10HZ;
	T2CONbits.TMR2ON = 1;
	PIR4bits.TMR2IF = 0;
	IPR4bits.TMR2IP = 1; /* high priority interrupt */
	PIE4bits.TMR2IE = 1;


	/* configure i2c */
	SSP1CON1 = 0x16; /* enable i2c in slave mode, 7 bit adress, CKP */
	SSP1CON2 = 0x01; /* SEN */
	SSP1CON3 = 0x00;
	SSP1STAT = 0x80;
	SSP1ADD = (I2C_ADDRESS << 1) & 0xfe;
	// SSP1MSK = 0xfe;
	SSP1MSK = 0x00;
	TRISCbits.TRISC3 = 1;
	TRISCbits.TRISC4 = 1;
	RC3PPS=0x0D;
	RC4PPS=0x0E;
	SSP1CON1bits.SSPEN=1;
	PIR3bits.SSP1IF = 0; // waiting to transmit/receive
	PIE3bits.SSP1IE = 1; // synchronous serial port interrupt enable
	i2c_curreg = i2c_flags = i2c_buttons = 0;
	but_start = but_stop = but_plus = but_minus = 0;
	i2cs_a = i2cs_r = i2cs_w = i2cs_s = 0;

	ad_state = ADS_PRESS;
	cur_amps = cur_press = 0;

	INTCONbits.GIE_GIEH=1;  /* enable high-priority interrupts */
	INTCONbits.PEIE_GIEL=1; /* enable low-priority interrrupts */

	OUT_MOTOR = 0; 
	TRISCbits.TRISC7 = 0;

	/* 4 buttons */
	TRISBbits.TRISB2 = 1;
	TRISBbits.TRISB3 = 1;
	TRISBbits.TRISB4 = 1;
	TRISBbits.TRISB5 = 1;

	OUT_DATAR = 0;
	TRISCbits.TRISC2 = 0; /* data_ready = out */

	WDTCON0bits.WDTPS = 0x0b; /* 2s watchdog */
	WDTCON1 = 0x17; /* MFINTOSC, always open */
	WDTCON0bits.SWDTEN = 1;
	CPUDOZEbits.IDLEN = 1;

	printf("ready %d.%d\n", PIC_VERSIONM, PIC_VERSIONm);

again:
	while (1) {
		CLRWDT;
		if (softintrs & INT_I2CFL) {
			softintrs &= ~INT_I2CFL;
			if (i2c_flags & I2C_FLAGS_MOTOR)
				OUT_MOTOR = 1;
			else
				OUT_MOTOR = 0;
		}
		if (softintrs & INT_AD) {
			if (ad_state & ADS_PRESS) {
				ad_value = (ADACCH << 8) | ADACCL;
				cur_press = (float)ad_value * 0.4531398 /
				    (float)ADC_NSMPLSP;
			} else {
				cur_amps = (float)ad_value * 0.61666667 /
				    (float)(ADC_NSMPLSAC / 2);
			}
			softintrs &= ~INT_AD;
		}
		if (softintrs & INT_10HZ) {
			softintrs &= ~INT_10HZ;
			/* cleanup hardware, in case something didn't complete */
			ADCON0bits.ADGO = 0;
			PIE1bits.ADIE = 0;
			ADCON2bits.ADACLR = 1;
			while (ADCON2bits.ADACLR)
				; /* wait */
			if ((ad_state & ADS_PRESS) != 0) {
				ad_value = 0;
				ADPCH = ADC_GND;
				ADPCH = ADC_CUR_REF;
				ADREF = 0x03; /* FVR */
				ad_state = ADS_CURR_REF;
			} else {
				ADPCH = ADC_GND;
				ADPCH = ADC_PRESS;
				ADREF = 0x00; /* Vcc */
				ad_state = ADS_PRESS;
			}
			PIR1bits.ADIF = 0;
			PIE1bits.ADIE = 1;
			ad_state |= ADS_TIMERSTART;
			counter_1hz--;
			if (counter_1hz == 0) {
				counter_1hz = 10;
				printf("I %d P %d B %d\n", cur_amps, cur_press, i2c_buttons);
				printf("i2c a %d r %d w %d s %d\n",
				    i2cs_a, i2cs_r, i2cs_w, i2cs_s);
				i2cs_a = i2cs_r = i2cs_w = i2cs_s = 0;
			}
		}
		if (but_start == 0xff)
			i2c_buttons |= I2C_BUTTONS_START;
		else if (but_start == 0)
			i2c_buttons &= ~I2C_BUTTONS_START;
		if (but_stop == 0xff)
			i2c_buttons |= I2C_BUTTONS_STOP;
		else if (but_stop == 0)
			i2c_buttons &= ~I2C_BUTTONS_STOP;
		if (but_plus == 0xff)
			i2c_buttons |= I2C_BUTTONS_PLUS;
		else if (but_plus == 0)
			i2c_buttons &= ~I2C_BUTTONS_PLUS;
		if (but_minus == 0xff)
			i2c_buttons |= I2C_BUTTONS_MINUS;
		else if (but_minus == 0)
			i2c_buttons &= ~I2C_BUTTONS_MINUS;

		if (RCREG1 == 'r')
			break;
		SLEEP;
	}

end:

	while ((c = getchar()) != 'r') {
		printf("got %c\n", c);
		goto again;
	}
	printf("returning\n");
	while (PIE3bits.TX1IE); /* wait for transmit to complete */
	

	INTCONbits.PEIE=0; /* disable peripheral interrupts */
	INTCONbits.GIE=0;  /* disable interrrupts */
}
unsigned int timer0_read() __naked
{
	/* return TMR0L | (TMR0H << 8), reading TMR0L first */
	__asm
	movf    _TMR0L, w
	movff   _TMR0H, _PRODL
	return
	__endasm;
}

/* Vectors */
void _reset (void) __naked __interrupt 0
{
	__asm__("goto __startup");
}

void _startup (void) __naked
{
  __asm
    // Initialize the stack pointer
    lfsr 1, _stack_end
    lfsr 2, _stack_end
    clrf _TBLPTRU, 0    // 1st silicon doesn't do this on POR

    __endasm ;

  /* Call the user's main routine */
  main();
  __asm__("reset");
}

/*
 * high priority interrupt. Split in 2 parts; one for the entry point
 * where we'll deal with timer0, then jump to another address
 * as we don't have enough space before the low priority vector
 */
void _irqh (void) __naked __shadowregs __interrupt 1
{
	__asm
	goto _irqh_timer2
	__endasm ;

}

void irqh_timer2(void) __naked
{
	/*
	 * no sdcc registers are automatically saved,
	 * so we have to be carefull with C code !
	 */
	__asm
	MOVFF   r0x00, POSTDEC1
	__endasm;
	PIR4bits.TMR2IF = 0;
	counter_10hz--;
	if (counter_10hz == 0) {
		counter_10hz = TIMER2_10HZ;
		softintrs |= INT_10HZ;
	}

	if (ADCON0bits.ADGO == 0 && (ad_state & ADS_TIMERSTART)) {
		ADCON0bits.ADGO = 1;
		ad_state &= ~ADS_TIMERSTART;
	}

	if (BUT_START) {
		if (but_start == 0x7f)
			OUT_DATAR = 1;
		but_start = but_start << 1;
		but_start |= (unsigned char)0x01;
	} else {
		if (but_start == 0x80)
			OUT_DATAR = 1;
		but_start = but_start << 1;
	}

	if (BUT_STOP) {
		if (but_stop == 0x7f)
			OUT_DATAR = 1;
		but_stop = but_stop << 1;
		but_stop |= (unsigned char)0x01;
	} else {
		if (but_stop == 0x80)
			OUT_DATAR = 1;
		but_stop = but_stop << 1;
	}

	if (BUT_PLUS) {
		if (but_plus == 0x7f)
			OUT_DATAR = 1;
		but_plus = but_plus << 1;
		but_plus |= (unsigned char)0x01;
	} else {
		if (but_plus == 0x80)
			OUT_DATAR = 1;
		but_plus = but_plus << 1;
	}

	if (BUT_MINUS) {
		if (but_minus == 0x7f)
			OUT_DATAR = 1;
		but_minus = but_minus << 1;
		but_minus |= (unsigned char)0x01;
	} else {
		if (but_minus == 0x80)
			OUT_DATAR = 1;
		but_minus = but_minus << 1;
	}

	__asm
	MOVFF   PREINC1, r0x00
	retfie 1
	nop
	__endasm;
}

void _irq (void) __interrupt 2 /* low priority */
{
	USART_INTR;

	if (PIR1bits.ADIF && PIE1bits.ADIE) {
		PIR1bits.ADIF = 0;
		if (ad_state & ADS_PRESS) {
			if (ADCNT == ADC_NSMPLSP) {
				softintrs |= INT_AD;
				PIE1bits.ADIE = 0;
			} else {
				ad_state |= ADS_TIMERSTART;
			}
		} else {
			if (ADCNT == ADC_NSMPLSAC) {
				softintrs |= INT_AD;
				PIE1bits.ADIE = 0;
			} else {
				if (ad_state & ADS_CURR_REF) {
					ad_ref = (ADRESH << 8) | ADRESL;
					ad_state = ADS_CURR_SENSE;
					ADPCH = ADC_GND;
					ADPCH = ADC_CUR_SENSE;
					ADCON0bits.ADGO = 1;
				} else {
					ad_sense = (ADRESH << 8) | ADRESL;
					if (ad_sense < ad_ref) {
						ad_value+= (ad_ref - ad_sense);
					} else {
						ad_value+= (ad_sense - ad_ref);
					}
					ad_state = ADS_CURR_REF;
					ADPCH = ADC_GND;
					ADPCH = ADC_CUR_REF;
					ad_state |= ADS_TIMERSTART;
				}
			}
		}
	}

	if (PIR3bits.SSP1IF == 1) {
		PIR3bits.SSP1IF = 0;
		if (!SSP1CON3bits.ACKTIM) {
			if ((SSP1CON1bits.SSPOV) || (SSP1CON1bits.WCOL)) {
				printf("i2c o %d\n", SSP1CON1);
				SSP1CON1bits.SSPOV = 0;
				SSP1CON1bits.WCOL = 0;
				SSP1CON1bits.CKP = 1;
				(void)SSP1BUF; /* clear buffer */
			}

			if (!SSP1STATbits.D_NOT_A && SSP1STATbits.BF) {
				// printf("i2c a %d\n", SSP1BUF);
				i2cs_a++;
				(void)SSP1BUF;
				i2c_reg_data = 1;
			}  else if (!SSP1STATbits.R_NOT_W && SSP1STATbits.BF) {
				if (i2c_reg_data) {
					i2c_curreg = SSP1BUF;
					//printf("i2c s %d\n", i2c_curreg);
					i2c_reg_data = 0;
					i2cs_s++;
				} else {
					// printf("i2c w %d\n", i2c_curreg);
					i2cs_w++;
					switch(i2c_curreg) {
					case I2C_R_FLAGS:
						i2c_flags = SSP1BUF;
						softintrs |= INT_I2CFL;
						break;
					default:
						(void)SSP1BUF;
						break;
					}
					i2c_curreg++;
				}
			}

			if (SSP1STATbits.R_NOT_W) {
				(void)SSP1BUF;
				// printf("i2c r %d\n", i2c_curreg);
				i2cs_r++;
				switch(i2c_curreg) {
				case I2C_R_VERSM:
					SSP1BUF = PIC_VERSIONM;
					break;
				case I2C_R_VERSm:
					SSP1BUF = PIC_VERSIONm;
					break;
				case I2C_R_FLAGS:
					SSP1BUF = i2c_flags;
					break;
				case I2C_R_BUTTONS:
					SSP1BUF = i2c_buttons;
					OUT_DATAR = 0;
					break;
				case I2C_R_AMP:
					SSP1BUF = cur_amps;
					break;
				case I2C_R_PRES:
					SSP1BUF = cur_press;
					break;
				default:
					SSP1BUF = 0;
					break;
				}
				i2c_curreg++;
			}
		}
		SSP1CON1bits.CKP = 1;
	}
}
