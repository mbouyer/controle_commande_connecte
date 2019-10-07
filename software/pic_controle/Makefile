.SUFFIXES: .o .hex

CC= sdcc  --use-non-free --Werror
ASM = gpasm
CFLAGS= -I${.CURDIR}
CFLAGS+= --fomit-frame-pointer --denable-peeps --optimize-cmp --optimize-df
OBJECTS= main.o serial.o
HEADERS= my_serial.h i2c.h

all: capteur.bin

capteur.bin: capteur.hex
	hex2bin1k ${.ALLSRC} ${.TARGET}
	@ls -lh ${.TARGET}

capteur.hex: ${OBJECTS}
	${CC} -V -Wl,-s${.CURDIR}/pic18f25q10.lkr --no-crt --ivt-loc=0x400 --obanksel=2 -mpic16 -p18f25q10 -Wl,libc18f.lib ${OBJECTS} -o capteur.hex -llibm18f.lib

${OBJECTS}: ${HEADERS} Makefile

.c.o:
	${CC} ${CFLAGS} -V --no-crt --ivt-loc=0x400 --obanksel=2 -mpic16 -p18f25q10 -c ${.IMPSRC} -o ${.TARGET}

clean:
	rm -f obj/*
