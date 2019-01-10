EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:olimex_esp8266-dev
LIBS:MCU_Microchip_PIC18
LIBS:microchip-local
LIBS:max-local
LIBS:regul-local
LIBS:switches-local
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Conn_01x04 J1
U 1 1 5BD69704
P 1450 1500
F 0 "J1" H 1450 1700 50  0000 C CNN
F 1 "Conn_01x04" H 1450 1200 50  0000 C CNN
F 2 "Connectors_Phoenix:PhoenixContact_MCV-G_04x3.50mm_Vertical" H 1450 1500 50  0001 C CNN
F 3 "" H 1450 1500 50  0001 C CNN
	1    1450 1500
	0    -1   -1   0   
$EndComp
$Comp
L Conn_01x04 J2
U 1 1 5BD6A6CC
P 1450 1850
F 0 "J2" H 1450 2050 50  0000 C CNN
F 1 "Conn_01x04" H 1450 1550 50  0000 C CNN
F 2 "Connectors_Phoenix:PhoenixContact_MCV-G_04x3.50mm_Vertical" H 1450 1850 50  0001 C CNN
F 3 "" H 1450 1850 50  0001 C CNN
	1    1450 1850
	0    -1   -1   0   
$EndComp
$Comp
L MAX4460ESA U1
U 1 1 5BD7E5D2
P 2200 2400
F 0 "U1" H 2200 2650 50  0000 L CNN
F 1 "MAX4460ESA" H 2200 2550 50  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 2200 2400 50  0001 C CNN
F 3 "" H 2350 2550 50  0001 C CNN
	1    2200 2400
	1    0    0    -1  
$EndComp
$Comp
L C_Small C1
U 1 1 5BD81967
P 1750 2400
F 0 "C1" H 1760 2470 50  0000 L CNN
F 1 "100nF" H 1760 2320 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1750 2400 50  0001 C CNN
F 3 "" H 1750 2400 50  0001 C CNN
	1    1750 2400
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR01
U 1 1 5BD849C7
P 2100 2000
F 0 "#PWR01" H 2100 1850 50  0001 C CNN
F 1 "+3.3V" H 2100 2140 50  0000 C CNN
F 2 "" H 2100 2000 50  0001 C CNN
F 3 "" H 2100 2000 50  0001 C CNN
	1    2100 2000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5BD86952
P 1700 2750
F 0 "#PWR02" H 1700 2500 50  0001 C CNN
F 1 "GND" H 1700 2600 50  0000 C CNN
F 2 "" H 1700 2750 50  0001 C CNN
F 3 "" H 1700 2750 50  0001 C CNN
	1    1700 2750
	0    1    1    0   
$EndComp
$Comp
L C_Small C3
U 1 1 5BD87F7D
P 2300 2050
F 0 "C3" H 2310 2120 50  0000 L CNN
F 1 "100nF" H 2310 1970 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2300 2050 50  0001 C CNN
F 3 "" H 2300 2050 50  0001 C CNN
	1    2300 2050
	0    1    1    0   
$EndComp
$Comp
L GND #PWR03
U 1 1 5BD89803
P 2400 2000
F 0 "#PWR03" H 2400 1750 50  0001 C CNN
F 1 "GND" H 2400 1850 50  0000 C CNN
F 2 "" H 2400 2000 50  0001 C CNN
F 3 "" H 2400 2000 50  0001 C CNN
	1    2400 2000
	-1   0    0    1   
$EndComp
$Comp
L R_Small R2
U 1 1 5BD97A4B
P 2000 2850
F 0 "R2" H 2030 2870 50  0000 L CNN
F 1 "5.6K" H 2030 2810 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" H 2000 2850 50  0001 C CNN
F 3 "" H 2000 2850 50  0001 C CNN
	1    2000 2850
	0    1    1    0   
$EndComp
$Comp
L R_Small R3
U 1 1 5BD986E5
P 2400 2850
F 0 "R3" H 2430 2870 50  0000 L CNN
F 1 "100K" H 2430 2810 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" H 2400 2850 50  0001 C CNN
F 3 "" H 2400 2850 50  0001 C CNN
	1    2400 2850
	0    1    1    0   
$EndComp
$Comp
L GND #PWR04
U 1 1 5C0194D5
P 1450 2100
F 0 "#PWR04" H 1450 1850 50  0001 C CNN
F 1 "GND" H 1450 1950 50  0000 C CNN
F 2 "" H 1450 2100 50  0001 C CNN
F 3 "" H 1450 2100 50  0001 C CNN
	1    1450 2100
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR05
U 1 1 5C019580
P 1350 2200
F 0 "#PWR05" H 1350 2050 50  0001 C CNN
F 1 "+3.3V" H 1350 2340 50  0000 C CNN
F 2 "" H 1350 2200 50  0001 C CNN
F 3 "" H 1350 2200 50  0001 C CNN
	1    1350 2200
	-1   0    0    1   
$EndComp
Wire Wire Line
	750  2050 700  2050
Wire Wire Line
	1650 1700 1650 2300
Wire Wire Line
	1650 2300 1900 2300
Wire Wire Line
	1550 1700 1550 2500
Wire Wire Line
	1550 2500 1900 2500
Connection ~ 1750 2300
Connection ~ 1750 2500
Wire Wire Line
	2400 2000 2400 2050
Wire Wire Line
	2200 2050 2100 2050
Wire Wire Line
	2100 2000 2100 2100
Connection ~ 2100 2050
Wire Wire Line
	2100 2750 2100 2700
Wire Wire Line
	2500 2400 2800 2400
Wire Wire Line
	1700 2750 2100 2750
Wire Wire Line
	2200 2700 2200 2850
Wire Wire Line
	2100 2850 2300 2850
Connection ~ 2200 2850
Wire Wire Line
	2500 2850 4000 2850
Connection ~ 2800 2850
Wire Wire Line
	1900 2850 1850 2850
Wire Wire Line
	1850 2850 1850 2750
Connection ~ 1850 2750
Wire Wire Line
	1350 1700 1350 2200
Wire Wire Line
	1450 1700 1450 2100
Wire Wire Line
	2800 2400 2800 2850
Connection ~ 1350 2050
Connection ~ 1450 2050
Connection ~ 1550 2050
Connection ~ 1650 2050
$Comp
L Conn_01x01 J3
U 1 1 5C361195
P 4200 2850
F 0 "J3" H 4200 2950 50  0000 C CNN
F 1 "Conn_01x01" H 4200 2750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 4200 2850 50  0001 C CNN
F 3 "" H 4200 2850 50  0001 C CNN
	1    4200 2850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
