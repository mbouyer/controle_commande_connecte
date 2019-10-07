EESchema Schematic File Version 4
LIBS:connected_sensor-cache
EELAYER 30 0
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
L connected_sensor-rescue:ESP8266-DEV M1
U 1 1 5BCDF2A3
P 5950 3300
F 0 "M1" H 5950 3750 60  0000 C CNN
F 1 "ESP8266-DEV" H 5950 2500 60  0000 C CNN
F 2 "local:ESP8266-DEV" H 5950 3300 60  0001 C CNN
F 3 "" H 5950 3300 60  0001 C CNN
	1    5950 3300
	1    0    0    -1  
$EndComp
Text Label 5150 3150 0    60   ~ 0
TXD
Text Label 5150 3250 0    60   ~ 0
RXD
Text Label 6600 2950 0    60   ~ 0
SCL
Text Label 6600 3150 0    60   ~ 0
SDA
Text Label 6600 3250 0    60   ~ 0
CS
Text Label 6600 3350 0    60   ~ 0
MOSI
Text Label 6600 3450 0    60   ~ 0
CLK
Text Label 6600 3550 0    60   ~ 0
MISO
$Comp
L connected_sensor-rescue:+3.3V #PWR01
U 1 1 5BCE05F9
P 5350 2750
F 0 "#PWR01" H 5350 2600 50  0001 C CNN
F 1 "+3.3V" H 5350 2890 50  0000 C CNN
F 2 "" H 5350 2750 50  0001 C CNN
F 3 "" H 5350 2750 50  0001 C CNN
	1    5350 2750
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:+3.3V #PWR02
U 1 1 5BCE0669
P 7700 2650
F 0 "#PWR02" H 7700 2500 50  0001 C CNN
F 1 "+3.3V" H 7700 2790 50  0000 C CNN
F 2 "" H 7700 2650 50  0001 C CNN
F 3 "" H 7700 2650 50  0001 C CNN
	1    7700 2650
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:GND #PWR03
U 1 1 5BCE08FA
P 5100 2750
F 0 "#PWR03" H 5100 2500 50  0001 C CNN
F 1 "GND" H 5100 2600 50  0000 C CNN
F 2 "" H 5100 2750 50  0001 C CNN
F 3 "" H 5100 2750 50  0001 C CNN
	1    5100 2750
	-1   0    0    1   
$EndComp
$Comp
L connected_sensor-rescue:GND #PWR04
U 1 1 5BCE0AB4
P 8300 2650
F 0 "#PWR04" H 8300 2400 50  0001 C CNN
F 1 "GND" H 8300 2500 50  0000 C CNN
F 2 "" H 8300 2650 50  0001 C CNN
F 3 "" H 8300 2650 50  0001 C CNN
	1    8300 2650
	-1   0    0    1   
$EndComp
$Comp
L connected_sensor-rescue:Conn_02x05_Odd_Even J8
U 1 1 5BCE0CD8
P 7950 3200
F 0 "J8" H 8000 3500 50  0000 C CNN
F 1 "UEXT" H 8000 2900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x05_Pitch2.54mm" H 7950 3200 50  0001 C CNN
F 3 "" H 7950 3200 50  0001 C CNN
	1    7950 3200
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:R_Small R13
U 1 1 5BCE1BE4
P 3750 5050
F 0 "R13" H 3780 5070 50  0000 L CNN
F 1 "2.2K" H 3780 5010 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" H 3750 5050 50  0001 C CNN
F 3 "" H 3750 5050 50  0001 C CNN
	1    3750 5050
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:R_Small R12
U 1 1 5BCE1F86
P 4000 5050
F 0 "R12" H 4030 5070 50  0000 L CNN
F 1 "NA" H 4030 5010 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" H 4000 5050 50  0001 C CNN
F 3 "" H 4000 5050 50  0001 C CNN
	1    4000 5050
	1    0    0    -1  
$EndComp
NoConn ~ 7750 3100
NoConn ~ 8250 3100
$Comp
L connected_sensor-rescue:Conn_01x03 J5
U 1 1 5BCE5500
P 4800 3150
F 0 "J5" H 4800 3350 50  0000 C CNN
F 1 "Conn_01x03" H 4800 2950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 4800 3150 50  0001 C CNN
F 3 "" H 4800 3150 50  0001 C CNN
	1    4800 3150
	-1   0    0    1   
$EndComp
$Comp
L connected_sensor-rescue:RM50-xx21 K1
U 1 1 5BCE7397
P 5950 5000
F 0 "K1" H 6300 5150 50  0000 L CNN
F 1 "G2RL-1A-E 5DC " H 6300 5050 50  0000 L CNN
F 2 "Relays_THT:Relay_SPST_Schrack-RT1-16A-FormA_RM5mm" H 7200 4950 50  0001 C CNN
F 3 "" H 5950 5000 50  0001 C CNN
	1    5950 5000
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:D_Small D1
U 1 1 5BCE8142
P 5200 4950
F 0 "D1" H 5150 5030 50  0000 L CNN
F 1 "1N4004" H 5050 4870 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5200 4950 50  0001 C CNN
F 3 "" V 5200 4950 50  0001 C CNN
	1    5200 4950
	0    1    -1   0   
$EndComp
$Comp
L connected_sensor-rescue:+5V #PWR05
U 1 1 5BCE89C5
P 5750 5400
F 0 "#PWR05" H 5750 5250 50  0001 C CNN
F 1 "+5V" H 5750 5540 50  0000 C CNN
F 2 "" H 5750 5400 50  0001 C CNN
F 3 "" H 5750 5400 50  0001 C CNN
	1    5750 5400
	-1   0    0    1   
$EndComp
$Comp
L connected_sensor-rescue:GND #PWR06
U 1 1 5BCE9E4E
P 5100 4500
F 0 "#PWR06" H 5100 4250 50  0001 C CNN
F 1 "GND" H 5100 4350 50  0000 C CNN
F 2 "" H 5100 4500 50  0001 C CNN
F 3 "" H 5100 4500 50  0001 C CNN
	1    5100 4500
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:R_Small R8
U 1 1 5BCEA562
P 5200 4300
F 0 "R8" H 5230 4320 50  0000 L CNN
F 1 "10K" H 5230 4260 50  0000 L CNN
F 2 "Resistors_SMD:R_1210_HandSoldering" H 5200 4300 50  0001 C CNN
F 3 "" H 5200 4300 50  0001 C CNN
	1    5200 4300
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:Q_NMOS_GSD Q1
U 1 1 5BCE9635
P 5450 4350
F 0 "Q1" H 5650 4400 50  0000 L CNN
F 1 "ZXMN3A01FTA " H 5650 4300 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 5650 4450 50  0001 C CNN
F 3 "" H 5450 4350 50  0001 C CNN
	1    5450 4350
	0    1    1    0   
$EndComp
$Comp
L connected_sensor-rescue:Conn_01x02 J6
U 1 1 5BCEED9D
P 6750 4500
F 0 "J6" H 6750 4600 50  0000 C CNN
F 1 "AC_IN" H 6750 4300 50  0000 C CNN
F 2 "phoenix-local:1017491" H 6750 4500 50  0001 C CNN
F 3 "" H 6750 4500 50  0001 C CNN
	1    6750 4500
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:Conn_01x02 J7
U 1 1 5BCEF216
P 6750 4300
F 0 "J7" H 6750 4400 50  0000 C CNN
F 1 "LOAD" H 6750 4100 50  0000 C CNN
F 2 "phoenix-local:1017491" H 6750 4300 50  0001 C CNN
F 3 "" H 6750 4300 50  0001 C CNN
	1    6750 4300
	1    0    0    1   
$EndComp
$Comp
L connected_sensor-rescue:PIC18F25Q10 U2
U 1 1 5BCF46C6
P 2850 4400
F 0 "U2" H 2150 5350 50  0000 L CNN
F 1 "PIC18F25Q10" H 3550 5350 50  0000 R CNN
F 2 "Housings_DIP:DIP-28_W7.62mm_LongPads" H 2350 3900 50  0001 C CNN
F 3 "" H 2850 4350 50  0000 C CNN
	1    2850 4400
	1    0    0    -1  
$EndComp
Text GLabel 6800 2950 2    60   Input ~ 0
SCL
Text GLabel 3900 4800 2    60   Input ~ 0
SCL
Text GLabel 6800 3150 2    60   Input ~ 0
SDA
Text GLabel 4200 4900 2    60   Input ~ 0
SDA
$Comp
L connected_sensor-rescue:+3.3V #PWR07
U 1 1 5BCF4E8C
P 2550 3250
F 0 "#PWR07" H 2550 3100 50  0001 C CNN
F 1 "+3.3V" H 2550 3390 50  0000 C CNN
F 2 "" H 2550 3250 50  0001 C CNN
F 3 "" H 2550 3250 50  0001 C CNN
	1    2550 3250
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:GND #PWR08
U 1 1 5BCF5467
P 2800 3250
F 0 "#PWR08" H 2800 3000 50  0001 C CNN
F 1 "GND" H 2800 3100 50  0000 C CNN
F 2 "" H 2800 3250 50  0001 C CNN
F 3 "" H 2800 3250 50  0001 C CNN
	1    2800 3250
	-1   0    0    1   
$EndComp
$Comp
L connected_sensor-rescue:GND #PWR09
U 1 1 5BCF70BE
P 2600 5600
F 0 "#PWR09" H 2600 5350 50  0001 C CNN
F 1 "GND" H 2600 5450 50  0000 C CNN
F 2 "" H 2600 5600 50  0001 C CNN
F 3 "" H 2600 5600 50  0001 C CNN
	1    2600 5600
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:C_Small C4
U 1 1 5BCF7E03
P 2700 3300
F 0 "C4" H 2710 3370 50  0000 L CNN
F 1 "100nF" H 2710 3220 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2700 3300 50  0001 C CNN
F 3 "" H 2700 3300 50  0001 C CNN
	1    2700 3300
	0    1    1    0   
$EndComp
$Comp
L connected_sensor-rescue:GND #PWR010
U 1 1 5BCFE7C7
P 4550 4100
F 0 "#PWR010" H 4550 3850 50  0001 C CNN
F 1 "GND" H 4550 3950 50  0000 C CNN
F 2 "" H 4550 4100 50  0001 C CNN
F 3 "" H 4550 4100 50  0001 C CNN
	1    4550 4100
	0    -1   -1   0   
$EndComp
$Comp
L connected_sensor-rescue:R_Small R1
U 1 1 5BD01774
P 1550 4850
F 0 "R1" H 1580 4870 50  0000 L CNN
F 1 "10K" H 1580 4810 50  0000 L CNN
F 2 "Resistors_SMD:R_1210_HandSoldering" H 1550 4850 50  0001 C CNN
F 3 "" H 1550 4850 50  0001 C CNN
	1    1550 4850
	0    1    1    0   
$EndComp
$Comp
L connected_sensor-rescue:+3.3V #PWR011
U 1 1 5BD0271C
P 1300 4850
F 0 "#PWR011" H 1300 4700 50  0001 C CNN
F 1 "+3.3V" H 1300 4990 50  0000 C CNN
F 2 "" H 1300 4850 50  0001 C CNN
F 3 "" H 1300 4850 50  0001 C CNN
	1    1300 4850
	0    -1   -1   0   
$EndComp
$Comp
L connected_sensor-rescue:C_Small C2
U 1 1 5BD043F6
P 1800 5050
F 0 "C2" H 1810 5120 50  0000 L CNN
F 1 "100nF" H 1810 4970 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1800 5050 50  0001 C CNN
F 3 "" H 1800 5050 50  0001 C CNN
	1    1800 5050
	-1   0    0    1   
$EndComp
$Comp
L connected_sensor-rescue:Transformer_1P_1S T1
U 1 1 5BD1482F
P 6350 5950
F 0 "T1" H 6350 6200 50  0000 C CNN
F 1 "Transformer_1P_1S" H 6350 5650 50  0000 C CNN
F 2 "local:CSE187-LP" H 6350 5950 50  0001 C CNN
F 3 "" H 6350 5950 50  0001 C CNN
	1    6350 5950
	0    1    1    0   
$EndComp
$Comp
L connected_sensor-rescue:R_Small R11
U 1 1 5BD19B61
P 6350 6450
F 0 "R11" H 6380 6470 50  0000 L CNN
F 1 "18" H 6380 6410 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" H 6350 6450 50  0001 C CNN
F 3 "" H 6350 6450 50  0001 C CNN
	1    6350 6450
	0    1    1    0   
$EndComp
$Comp
L connected_sensor-rescue:R_Small R10
U 1 1 5BD1AC20
P 6550 7000
F 0 "R10" H 6580 7020 50  0000 L CNN
F 1 "10k" H 6580 6960 50  0000 L CNN
F 2 "Resistors_SMD:R_1210_HandSoldering" H 6550 7000 50  0001 C CNN
F 3 "" H 6550 7000 50  0001 C CNN
	1    6550 7000
	0    1    1    0   
$EndComp
$Comp
L connected_sensor-rescue:R_Small R9
U 1 1 5BD1B4DA
P 6200 7000
F 0 "R9" H 6230 7020 50  0000 L CNN
F 1 "4.7k" H 6230 6960 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" H 6200 7000 50  0001 C CNN
F 3 "" H 6200 7000 50  0001 C CNN
	1    6200 7000
	0    1    1    0   
$EndComp
$Comp
L connected_sensor-rescue:+3.3V #PWR012
U 1 1 5BD1F7E9
P 6750 7000
F 0 "#PWR012" H 6750 6850 50  0001 C CNN
F 1 "+3.3V" H 6750 7140 50  0000 C CNN
F 2 "" H 6750 7000 50  0001 C CNN
F 3 "" H 6750 7000 50  0001 C CNN
	1    6750 7000
	0    1    1    0   
$EndComp
$Comp
L connected_sensor-rescue:GND #PWR013
U 1 1 5BD2295E
P 5950 7000
F 0 "#PWR013" H 5950 6750 50  0001 C CNN
F 1 "GND" H 5950 6850 50  0000 C CNN
F 2 "" H 5950 7000 50  0001 C CNN
F 3 "" H 5950 7000 50  0001 C CNN
	1    5950 7000
	0    1    1    0   
$EndComp
Text GLabel 6650 6450 2    60   Input ~ 0
CUR_REF
Text GLabel 6000 6450 0    60   Input ~ 0
CUR_SENSE
Text GLabel 1650 3750 0    60   Input ~ 0
CUR_REF
Text GLabel 1750 3950 0    60   Input ~ 0
CUR_SENSE
Text GLabel 6800 3850 2    60   Input ~ 0
DATA_READY
Text GLabel 4150 4700 2    60   Input ~ 0
DATA_READY
Text GLabel 1600 4700 0    60   Input ~ 0
MCLR
Text GLabel 4450 4500 2    60   Input ~ 0
MCLR
$Comp
L connected_sensor-rescue:Conn_01x05 J3
U 1 1 5BD53C80
P 4150 4300
F 0 "J3" H 4150 4600 50  0000 C CNN
F 1 "Conn_01x05" H 4150 4000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 4150 4300 50  0001 C CNN
F 3 "" H 4150 4300 50  0001 C CNN
	1    4150 4300
	-1   0    0    1   
$EndComp
$Comp
L connected_sensor-rescue:+3.3V #PWR014
U 1 1 5BD5A861
P 4550 4350
F 0 "#PWR014" H 4550 4200 50  0001 C CNN
F 1 "+3.3V" H 4550 4490 50  0000 C CNN
F 2 "" H 4550 4350 50  0001 C CNN
F 3 "" H 4550 4350 50  0001 C CNN
	1    4550 4350
	0    1    1    0   
$EndComp
$Comp
L connected_sensor-rescue:Conn_01x04 J1
U 1 1 5BD69704
P 850 1850
F 0 "J1" H 850 2050 50  0000 C CNN
F 1 "Conn_01x04" H 850 1550 50  0000 C CNN
F 2 "Connectors_Phoenix:PhoenixContact_MCV-G_04x3.50mm_Vertical" H 850 1850 50  0001 C CNN
F 3 "" H 850 1850 50  0001 C CNN
	1    850  1850
	0    -1   -1   0   
$EndComp
$Comp
L connected_sensor-rescue:Conn_01x04 J2
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
L connected_sensor-rescue:+3.3V #PWR015
U 1 1 5BD6CDE8
P 700 2500
F 0 "#PWR015" H 700 2350 50  0001 C CNN
F 1 "+3.3V" H 700 2640 50  0000 C CNN
F 2 "" H 700 2500 50  0001 C CNN
F 3 "" H 700 2500 50  0001 C CNN
	1    700  2500
	-1   0    0    1   
$EndComp
$Comp
L connected_sensor-rescue:GND #PWR016
U 1 1 5BD72044
P 850 2500
F 0 "#PWR016" H 850 2250 50  0001 C CNN
F 1 "GND" H 850 2350 50  0000 C CNN
F 2 "" H 850 2500 50  0001 C CNN
F 3 "" H 850 2500 50  0001 C CNN
	1    850  2500
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:MAX4460ESA U1
U 1 1 5BD7E5D2
P 2200 2400
F 0 "U1" H 2200 2650 50  0000 L CNN
F 1 "MAX4460ESA" H 2200 2550 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6" H 2200 2400 50  0001 C CNN
F 3 "" H 2350 2550 50  0001 C CNN
	1    2200 2400
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:C_Small C1
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
L connected_sensor-rescue:+3.3V #PWR017
U 1 1 5BD849C7
P 2100 2000
F 0 "#PWR017" H 2100 1850 50  0001 C CNN
F 1 "+3.3V" H 2100 2140 50  0000 C CNN
F 2 "" H 2100 2000 50  0001 C CNN
F 3 "" H 2100 2000 50  0001 C CNN
	1    2100 2000
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:GND #PWR018
U 1 1 5BD86952
P 1700 2750
F 0 "#PWR018" H 1700 2500 50  0001 C CNN
F 1 "GND" H 1700 2600 50  0000 C CNN
F 2 "" H 1700 2750 50  0001 C CNN
F 3 "" H 1700 2750 50  0001 C CNN
	1    1700 2750
	0    1    1    0   
$EndComp
$Comp
L connected_sensor-rescue:C_Small C3
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
L connected_sensor-rescue:GND #PWR019
U 1 1 5BD89803
P 2400 2000
F 0 "#PWR019" H 2400 1750 50  0001 C CNN
F 1 "GND" H 2400 1850 50  0000 C CNN
F 2 "" H 2400 2000 50  0001 C CNN
F 3 "" H 2400 2000 50  0001 C CNN
	1    2400 2000
	-1   0    0    1   
$EndComp
$Comp
L connected_sensor-rescue:R_Small R2
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
L connected_sensor-rescue:R_Small R3
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
L connected_sensor-rescue:MIC5205-3.3 U4
U 1 1 5BDA7230
P 9700 4700
F 0 "U4" H 9550 4925 50  0000 C CNN
F 1 "MIC5504-3.3" H 9700 4925 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5" H 9700 5025 50  0001 C CNN
F 3 "" H 9700 4700 50  0001 C CNN
	1    9700 4700
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:+5V #PWR020
U 1 1 5BDAB4D2
P 9000 4600
F 0 "#PWR020" H 9000 4450 50  0001 C CNN
F 1 "+5V" H 9000 4740 50  0000 C CNN
F 2 "" H 9000 4600 50  0001 C CNN
F 3 "" H 9000 4600 50  0001 C CNN
	1    9000 4600
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:IRM-03 U3
U 1 1 5BDB94A6
P 8350 4600
F 0 "U3" H 8350 4900 60  0000 C CNN
F 1 "IRM-03-5" H 8350 4350 60  0000 C CNN
F 2 "local:ACDC-Conv_THTMeanWell-IRM-03-XX" H 8350 4600 60  0001 C CNN
F 3 "" H 8350 4600 60  0001 C CNN
	1    8350 4600
	1    0    0    1   
$EndComp
NoConn ~ 10000 4700
$Comp
L connected_sensor-rescue:C_Small C5
U 1 1 5BDCFE68
P 9000 4800
F 0 "C5" H 9010 4870 50  0000 L CNN
F 1 "1µ" H 9010 4720 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9000 4800 50  0001 C CNN
F 3 "" H 9000 4800 50  0001 C CNN
	1    9000 4800
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:C_Small C6
U 1 1 5BDD250E
P 10150 4800
F 0 "C6" H 10160 4870 50  0000 L CNN
F 1 "1µ" H 10160 4720 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 10150 4800 50  0001 C CNN
F 3 "" H 10150 4800 50  0001 C CNN
	1    10150 4800
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:+3.3V #PWR021
U 1 1 5BDD6118
P 10300 4600
F 0 "#PWR021" H 10300 4450 50  0001 C CNN
F 1 "+3.3V" H 10300 4740 50  0000 C CNN
F 2 "" H 10300 4600 50  0001 C CNN
F 3 "" H 10300 4600 50  0001 C CNN
	1    10300 4600
	0    1    1    0   
$EndComp
$Comp
L connected_sensor-rescue:PWR_FLAG #FLG022
U 1 1 5BDE46FE
P 7550 4350
F 0 "#FLG022" H 7550 4425 50  0001 C CNN
F 1 "PWR_FLAG" H 7550 4500 50  0000 C CNN
F 2 "" H 7550 4350 50  0001 C CNN
F 3 "" H 7550 4350 50  0001 C CNN
	1    7550 4350
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:PWR_FLAG #FLG023
U 1 1 5BDE59D5
P 7550 4750
F 0 "#FLG023" H 7550 4825 50  0001 C CNN
F 1 "PWR_FLAG" H 7550 4900 50  0000 C CNN
F 2 "" H 7550 4750 50  0001 C CNN
F 3 "" H 7550 4750 50  0001 C CNN
	1    7550 4750
	-1   0    0    1   
$EndComp
NoConn ~ 5400 3350
NoConn ~ 5400 3450
NoConn ~ 5400 3550
NoConn ~ 5400 3650
NoConn ~ 5400 3750
NoConn ~ 5400 3850
NoConn ~ 6500 3750
NoConn ~ 6500 3950
Text Label 3700 3800 0    60   ~ 0
BT1
Text Label 3700 3900 0    60   ~ 0
BT2
Text Label 3700 4000 0    60   ~ 0
BT3
Text Label 3700 4100 0    60   ~ 0
BT4
$Comp
L connected_sensor-rescue:Conn_01x05 J4
U 1 1 5BE22569
P 4250 6500
F 0 "J4" H 4250 6800 50  0000 C CNN
F 1 "Conn_01x05" H 4250 6200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 4250 6500 50  0001 C CNN
F 3 "" H 4250 6500 50  0001 C CNN
	1    4250 6500
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:SW_Push SW1
U 1 1 5BE242E4
P 2100 6150
F 0 "SW1" H 2150 6250 50  0000 L CNN
F 1 "SW_Push" H 2100 6090 50  0000 C CNN
F 2 "" H 2100 6350 50  0001 C CNN
F 3 "" H 2100 6350 50  0001 C CNN
	1    2100 6150
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:SW_Push SW2
U 1 1 5BE2B1EE
P 2100 6600
F 0 "SW2" H 2150 6700 50  0000 L CNN
F 1 "SW_Push" H 2100 6540 50  0000 C CNN
F 2 "" H 2100 6800 50  0001 C CNN
F 3 "" H 2100 6800 50  0001 C CNN
	1    2100 6600
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:SW_Push SW4
U 1 1 5BE2C086
P 3000 6600
F 0 "SW4" H 3050 6700 50  0000 L CNN
F 1 "SW_Push" H 3000 6540 50  0000 C CNN
F 2 "" H 3000 6800 50  0001 C CNN
F 3 "" H 3000 6800 50  0001 C CNN
	1    3000 6600
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:SW_Push SW3
U 1 1 5BE2C7AF
P 3000 6150
F 0 "SW3" H 3050 6250 50  0000 L CNN
F 1 "SW_Push" H 3000 6090 50  0000 C CNN
F 2 "" H 3000 6350 50  0001 C CNN
F 3 "" H 3000 6350 50  0001 C CNN
	1    3000 6150
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:+3.3V #PWR024
U 1 1 5BE2EC19
P 2500 6000
F 0 "#PWR024" H 2500 5850 50  0001 C CNN
F 1 "+3.3V" H 2500 6140 50  0000 C CNN
F 2 "" H 2500 6000 50  0001 C CNN
F 3 "" H 2500 6000 50  0001 C CNN
	1    2500 6000
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:GND #PWR025
U 1 1 5BE3D28D
P 3550 7200
F 0 "#PWR025" H 3550 6950 50  0001 C CNN
F 1 "GND" H 3550 7050 50  0000 C CNN
F 2 "" H 3550 7200 50  0001 C CNN
F 3 "" H 3550 7200 50  0001 C CNN
	1    3550 7200
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:R_Small R7
U 1 1 5BE4337C
P 3850 6850
F 0 "R7" H 3880 6870 50  0000 L CNN
F 1 "10K" H 3880 6810 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" H 3850 6850 50  0001 C CNN
F 3 "" H 3850 6850 50  0001 C CNN
	1    3850 6850
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:R_Small R6
U 1 1 5BE45D58
P 3700 6850
F 0 "R6" H 3730 6870 50  0000 L CNN
F 1 "10K" H 3730 6810 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" H 3700 6850 50  0001 C CNN
F 3 "" H 3700 6850 50  0001 C CNN
	1    3700 6850
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:R_Small R5
U 1 1 5BE464B0
P 3550 6850
F 0 "R5" H 3580 6870 50  0000 L CNN
F 1 "10K" H 3580 6810 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" H 3550 6850 50  0001 C CNN
F 3 "" H 3550 6850 50  0001 C CNN
	1    3550 6850
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:R_Small R4
U 1 1 5BE46537
P 3400 6850
F 0 "R4" H 3430 6870 50  0000 L CNN
F 1 "10K" H 3430 6810 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" H 3400 6850 50  0001 C CNN
F 3 "" H 3400 6850 50  0001 C CNN
	1    3400 6850
	1    0    0    -1  
$EndComp
Text Label 3900 6400 0    60   ~ 0
BT1
Text Label 3900 6500 0    60   ~ 0
BT2
Text Label 3900 6600 0    60   ~ 0
BT3
Text Label 3900 6700 0    60   ~ 0
BT4
NoConn ~ 1900 3850
NoConn ~ 1900 4050
NoConn ~ 1900 4450
NoConn ~ 3650 4500
NoConn ~ 3650 5100
$Comp
L connected_sensor-rescue:GND #PWR026
U 1 1 5C00D55B
P 9700 5100
F 0 "#PWR026" H 9700 4850 50  0001 C CNN
F 1 "GND" H 9700 4950 50  0000 C CNN
F 2 "" H 9700 5100 50  0001 C CNN
F 3 "" H 9700 5100 50  0001 C CNN
	1    9700 5100
	1    0    0    -1  
$EndComp
Text Label 7150 4500 0    60   ~ 0
AC1
Text Label 7150 4600 0    60   ~ 0
AC2
Text Label 6300 4200 0    60   ~ 0
ACL
Text Label 6150 5550 1    60   ~ 0
ACm
$Comp
L connected_sensor-rescue:GND #PWR027
U 1 1 5C0194D5
P 1450 2100
F 0 "#PWR027" H 1450 1850 50  0001 C CNN
F 1 "GND" H 1450 1950 50  0000 C CNN
F 2 "" H 1450 2100 50  0001 C CNN
F 3 "" H 1450 2100 50  0001 C CNN
	1    1450 2100
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:+3.3V #PWR028
U 1 1 5C019580
P 1350 2200
F 0 "#PWR028" H 1350 2050 50  0001 C CNN
F 1 "+3.3V" H 1350 2340 50  0000 C CNN
F 2 "" H 1350 2200 50  0001 C CNN
F 3 "" H 1350 2200 50  0001 C CNN
	1    1350 2200
	-1   0    0    1   
$EndComp
NoConn ~ 6500 3850
NoConn ~ 3650 5000
NoConn ~ 3650 3600
NoConn ~ 3650 3700
NoConn ~ 1900 4350
Wire Wire Line
	5000 3150 5400 3150
Wire Wire Line
	5000 3250 5400 3250
Wire Wire Line
	6500 3250 6900 3250
Wire Wire Line
	6500 3350 6800 3350
Wire Wire Line
	6500 3450 7750 3450
Wire Wire Line
	6500 3550 7450 3550
Wire Wire Line
	5350 2750 5350 2950
Wire Wire Line
	5350 2950 5400 2950
Wire Wire Line
	5100 2750 5100 3050
Wire Wire Line
	5000 3050 5100 3050
Wire Wire Line
	7700 2650 7700 2700
Wire Wire Line
	7700 3000 7750 3000
Wire Wire Line
	8300 2650 8300 3000
Wire Wire Line
	8300 3000 8250 3000
Wire Wire Line
	7150 2700 7700 2700
Connection ~ 7700 2700
Wire Wire Line
	7450 3550 7450 3300
Wire Wire Line
	7450 3300 7750 3300
Wire Wire Line
	7750 3450 7750 3400
Wire Wire Line
	6800 3350 6800 3700
Wire Wire Line
	6800 3700 8450 3700
Wire Wire Line
	8450 3700 8450 3300
Wire Wire Line
	8450 3300 8250 3300
Wire Wire Line
	6900 3250 6900 3650
Wire Wire Line
	6900 3650 7150 3650
Wire Wire Line
	8350 3650 8350 3400
Wire Wire Line
	8350 3400 8250 3400
Connection ~ 5100 3050
Wire Wire Line
	5750 5300 5750 5350
Wire Wire Line
	5750 5350 5200 5350
Wire Wire Line
	5200 5350 5200 5050
Connection ~ 5750 5350
Wire Wire Line
	5750 4450 5750 4600
Wire Wire Line
	5750 4600 5200 4600
Wire Wire Line
	5200 4600 5200 4850
Connection ~ 5750 4600
Wire Wire Line
	6550 4600 7550 4600
Wire Wire Line
	6150 5300 6150 5550
Wire Wire Line
	3650 4800 3750 4800
Wire Wire Line
	3650 4900 4000 4900
Wire Wire Line
	2500 5400 2500 5500
Wire Wire Line
	1800 5500 2500 5500
Wire Wire Line
	2600 5400 2600 5500
Connection ~ 2600 5500
Wire Wire Line
	2550 3250 2550 3300
Wire Wire Line
	2600 3300 2550 3300
Connection ~ 2550 3300
Wire Wire Line
	2800 3300 2800 3250
Wire Wire Line
	3650 4200 4350 4200
Wire Wire Line
	3650 4300 4350 4300
Wire Wire Line
	1300 4850 1450 4850
Wire Wire Line
	1650 4850 1800 4850
Wire Wire Line
	1800 4700 1800 4850
Connection ~ 1800 4850
Wire Wire Line
	1800 5150 1800 5500
Connection ~ 2500 5500
Connection ~ 6550 4500
Connection ~ 6550 4600
Wire Wire Line
	6300 7000 6400 7000
Connection ~ 6400 7000
Wire Wire Line
	6100 7000 5950 7000
Wire Wire Line
	6650 7000 6750 7000
Wire Wire Line
	6550 6350 6550 6450
Wire Wire Line
	6450 6450 6550 6450
Connection ~ 6550 6450
Wire Wire Line
	6000 6450 6150 6450
Connection ~ 6150 6450
Wire Wire Line
	4550 4100 4350 4100
Wire Wire Line
	4450 4500 4350 4500
Wire Wire Line
	4550 4350 4350 4350
Wire Wire Line
	4350 4350 4350 4400
Wire Wire Line
	1600 4700 1800 4700
Wire Wire Line
	750  2050 700  2050
Wire Wire Line
	700  2050 700  2500
Wire Wire Line
	1650 2050 1650 2300
Wire Wire Line
	1650 2300 1750 2300
Wire Wire Line
	1550 2050 1550 2500
Wire Wire Line
	1550 2500 1750 2500
Connection ~ 1750 2300
Connection ~ 1750 2500
Wire Wire Line
	2400 2000 2400 2050
Wire Wire Line
	2200 2050 2100 2050
Wire Wire Line
	2100 2000 2100 2050
Connection ~ 2100 2050
Wire Wire Line
	2100 2750 2100 2700
Wire Wire Line
	2500 2400 2800 2400
Wire Wire Line
	1700 2750 1850 2750
Wire Wire Line
	2200 2700 2200 2850
Wire Wire Line
	2100 2850 2200 2850
Connection ~ 2200 2850
Wire Wire Line
	2500 2850 2800 2850
Connection ~ 2800 2850
Wire Wire Line
	1900 2850 1850 2850
Wire Wire Line
	1850 2850 1850 2750
Connection ~ 1850 2750
Wire Wire Line
	8800 4600 9000 4600
Wire Wire Line
	9400 4600 9400 4700
Wire Wire Line
	9700 5000 9700 5050
Connection ~ 9400 4600
Connection ~ 9000 4600
Wire Wire Line
	8800 5050 9000 5050
Wire Wire Line
	9000 4600 9000 4700
Wire Wire Line
	9000 4900 9000 5050
Connection ~ 9000 5050
Wire Wire Line
	10150 5050 10150 4900
Connection ~ 9700 5050
Wire Wire Line
	10150 4700 10150 4600
Wire Wire Line
	10000 4600 10150 4600
Connection ~ 10150 4600
Wire Wire Line
	7900 4600 7900 4700
Wire Wire Line
	7550 4500 7550 4350
Connection ~ 7550 4500
Wire Wire Line
	7550 4600 7550 4750
Connection ~ 7550 4600
Wire Wire Line
	6800 3850 6700 3850
Wire Wire Line
	3650 5200 4950 5200
Wire Wire Line
	3650 3800 3900 3800
Wire Wire Line
	3650 3900 3900 3900
Wire Wire Line
	3650 4000 3900 4000
Wire Wire Line
	3650 4100 3900 4100
Wire Wire Line
	1900 6000 2500 6000
Wire Wire Line
	2800 6000 2800 6150
Connection ~ 2800 6150
Wire Wire Line
	1900 6000 1900 6150
Connection ~ 2500 6000
Connection ~ 1900 6150
Wire Wire Line
	4050 6000 4050 6300
Connection ~ 2800 6000
Wire Wire Line
	2300 6400 3850 6400
Wire Wire Line
	2300 6400 2300 6150
Wire Wire Line
	2300 6500 3700 6500
Wire Wire Line
	2300 6500 2300 6600
Wire Wire Line
	3200 6150 3550 6150
Wire Wire Line
	3550 6150 3550 6600
Wire Wire Line
	3550 6600 4050 6600
Wire Wire Line
	3200 6600 3400 6600
Wire Wire Line
	3400 6600 3400 6700
Wire Wire Line
	3400 6700 4050 6700
Wire Wire Line
	3850 6750 3850 6400
Connection ~ 3850 6400
Wire Wire Line
	3700 6750 3700 6500
Connection ~ 3700 6500
Connection ~ 3550 6600
Connection ~ 3400 6700
Wire Wire Line
	3400 6950 3400 7050
Wire Wire Line
	3400 7050 3550 7050
Wire Wire Line
	3550 6950 3550 7050
Connection ~ 3550 7050
Wire Wire Line
	3700 7050 3700 6950
Wire Wire Line
	3850 7050 3850 6950
Connection ~ 3700 7050
Wire Wire Line
	8800 4700 8800 5050
Wire Wire Line
	6550 4500 7550 4500
Wire Wire Line
	6550 4600 6550 5550
Wire Wire Line
	6250 4700 6250 4200
Wire Wire Line
	6250 4200 6550 4200
Wire Wire Line
	6550 4300 6550 4500
Wire Wire Line
	1350 2050 1350 2200
Wire Wire Line
	1450 2100 1450 2050
Wire Wire Line
	850  2050 850  2500
Wire Wire Line
	1050 4150 1050 2050
Wire Wire Line
	5650 4450 5750 4450
Wire Wire Line
	5100 4450 5200 4450
Wire Wire Line
	5100 4450 5100 4500
Wire Wire Line
	5200 4450 5200 4400
Connection ~ 5200 4450
Wire Wire Line
	4950 4150 5200 4150
Connection ~ 5200 4150
Wire Wire Line
	6700 3850 6700 3650
Wire Wire Line
	6700 3650 6500 3650
Wire Wire Line
	4150 4700 3650 4700
Wire Wire Line
	2800 2400 2800 2850
Wire Wire Line
	4000 2850 4000 4600
Wire Wire Line
	4000 4600 3650 4600
Wire Wire Line
	1650 3750 1900 3750
Wire Wire Line
	1900 3950 1750 3950
Wire Wire Line
	950  2050 950  4250
Wire Wire Line
	1050 4150 1900 4150
Wire Wire Line
	950  4250 1900 4250
Wire Wire Line
	6150 6350 6150 6450
Wire Wire Line
	6550 6750 6400 6750
Wire Wire Line
	6400 6750 6400 7000
$Comp
L connected_sensor-rescue:R_Small R14
U 1 1 5C0FE343
P 7150 2850
F 0 "R14" H 7180 2870 50  0000 L CNN
F 1 "47K" H 7180 2810 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" H 7150 2850 50  0001 C CNN
F 3 "" H 7150 2850 50  0001 C CNN
	1    7150 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 2700 7150 2750
Wire Wire Line
	7150 2950 7150 3650
Connection ~ 7150 3650
$Comp
L connected_sensor-rescue:5G SW5
U 1 1 5C11014E
P 6350 2450
F 0 "SW5" H 6400 2550 50  0000 L CNN
F 1 "SW_Push" H 6350 2390 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_TH_Tactile_Omron_B3F-10xx" H 6350 2650 50  0001 C CNN
F 3 "" H 6350 2650 50  0001 C CNN
	1    6350 2450
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:R_Small R15
U 1 1 5C1102AB
P 6700 2700
F 0 "R15" H 6730 2720 50  0000 L CNN
F 1 "220" H 6730 2660 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Vertical" H 6700 2700 50  0001 C CNN
F 3 "" H 6700 2700 50  0001 C CNN
	1    6700 2700
	1    0    0    -1  
$EndComp
$Comp
L connected_sensor-rescue:GND #PWR029
U 1 1 5C11038E
P 6050 2300
F 0 "#PWR029" H 6050 2050 50  0001 C CNN
F 1 "GND" H 6050 2150 50  0000 C CNN
F 2 "" H 6050 2300 50  0001 C CNN
F 3 "" H 6050 2300 50  0001 C CNN
	1    6050 2300
	-1   0    0    1   
$EndComp
Wire Wire Line
	6500 3050 6700 3050
Wire Wire Line
	6050 2300 6050 2450
Connection ~ 6050 2450
Wire Wire Line
	6700 2450 6700 2600
Wire Wire Line
	6700 3050 6700 2800
Wire Wire Line
	6700 2450 6650 2450
NoConn ~ 6650 2550
Wire Wire Line
	4000 4950 4000 4900
Connection ~ 4000 4900
Wire Wire Line
	3750 4950 3750 4800
Connection ~ 3750 4800
Wire Wire Line
	3750 5150 3850 5150
$Comp
L connected_sensor-rescue:+3.3V #PWR030
U 1 1 5CED4E1A
P 3850 5250
F 0 "#PWR030" H 3850 5100 50  0001 C CNN
F 1 "+3.3V" H 3850 5390 50  0000 C CNN
F 2 "" H 3850 5250 50  0001 C CNN
F 3 "" H 3850 5250 50  0001 C CNN
	1    3850 5250
	-1   0    0    1   
$EndComp
Wire Wire Line
	3850 5150 3850 5250
Connection ~ 3850 5150
Wire Wire Line
	6500 2950 6800 2950
Wire Wire Line
	6500 3150 6800 3150
Wire Wire Line
	5200 4200 5200 4150
Wire Wire Line
	7500 3050 7500 2900
Wire Wire Line
	7500 2900 8400 2900
Wire Wire Line
	8400 2900 8400 3200
Wire Wire Line
	8400 3200 8250 3200
Connection ~ 6700 3050
Text Label 7300 3050 0    60   ~ 0
C_D
Wire Wire Line
	7750 3200 7600 3200
Wire Wire Line
	7600 3200 7600 4050
Wire Wire Line
	7600 4050 5400 4050
Wire Wire Line
	5400 4050 5400 3950
Text Label 7000 4050 0    60   ~ 0
LCD_RST
Wire Wire Line
	4950 5200 4950 4150
Text Label 4250 5200 0    60   ~ 0
REL
Wire Wire Line
	7700 2700 7700 3000
Wire Wire Line
	5100 3050 5400 3050
Wire Wire Line
	5750 5350 5750 5400
Wire Wire Line
	5750 4600 5750 4700
Wire Wire Line
	2600 5500 2600 5600
Wire Wire Line
	2550 3300 2550 3400
Wire Wire Line
	1800 4850 1900 4850
Wire Wire Line
	1800 4850 1800 4950
Wire Wire Line
	2500 5500 2600 5500
Wire Wire Line
	6400 7000 6450 7000
Wire Wire Line
	6550 6450 6550 6750
Wire Wire Line
	6550 6450 6650 6450
Wire Wire Line
	6150 6450 6250 6450
Wire Wire Line
	1750 2300 1900 2300
Wire Wire Line
	1750 2500 1900 2500
Wire Wire Line
	2100 2050 2100 2100
Wire Wire Line
	2200 2850 2300 2850
Wire Wire Line
	2800 2850 4000 2850
Wire Wire Line
	1850 2750 2100 2750
Wire Wire Line
	9000 4600 9400 4600
Wire Wire Line
	9000 5050 9700 5050
Wire Wire Line
	9700 5050 9700 5100
Wire Wire Line
	9700 5050 10150 5050
Wire Wire Line
	10150 4600 10300 4600
Wire Wire Line
	7550 4500 7900 4500
Wire Wire Line
	7550 4600 7900 4600
Wire Wire Line
	2800 6150 2800 6600
Wire Wire Line
	2500 6000 2800 6000
Wire Wire Line
	1900 6150 1900 6600
Wire Wire Line
	2800 6000 4050 6000
Wire Wire Line
	3850 6400 4050 6400
Wire Wire Line
	3700 6500 4050 6500
Wire Wire Line
	3550 6600 3550 6750
Wire Wire Line
	3400 6700 3400 6750
Wire Wire Line
	3550 7050 3700 7050
Wire Wire Line
	3550 7050 3550 7200
Wire Wire Line
	3700 7050 3850 7050
Wire Wire Line
	5200 4450 5250 4450
Wire Wire Line
	5200 4150 5450 4150
Wire Wire Line
	7150 3650 8350 3650
Wire Wire Line
	6050 2450 6050 2550
Wire Wire Line
	4000 4900 4200 4900
Wire Wire Line
	3750 4800 3900 4800
Wire Wire Line
	3850 5150 4000 5150
Wire Wire Line
	6700 3050 7500 3050
$EndSCHEMATC
