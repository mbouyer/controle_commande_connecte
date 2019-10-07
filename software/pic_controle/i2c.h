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
#define PIC_VERSIONM 0x00    
#define PIC_VERSIONm 0x01    


/* registers */

#define I2C_R_VERSM	0x01
#define I2C_R_VERSm	0x02
#define I2C_R_FLAGS	0x03
#define 	I2C_FLAGS_MOTOR (unsigned char)0x01
#define I2C_R_BUTTONS	0x04
#define 	I2C_BUTTONS_START (unsigned char)0x01
#define 	I2C_BUTTONS_STOP  (unsigned char)0x02
#define 	I2C_BUTTONS_PLUS ( unsigned char)0x04
#define 	I2C_BUTTONS_MINUS (unsigned char)0x08
#define I2C_R_AMP	0x05
#define I2C_R_PRES	0x06

#define I2C_W_FLAGS 	0x03

#define I2C_ADDRESS	0x12
