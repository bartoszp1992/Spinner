EESchema Schematic File Version 4
LIBS:synchro2-cache
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
L MCU_ST_STM32F0:STM32F030F4Px U2
U 1 1 5D5DBD75
P 6100 3550
F 0 "U2" H 6250 2800 50  0000 C CNN
F 1 "STM32F041F6Px" H 6500 2700 50  0000 C CNN
F 2 "Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm" H 5700 2850 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00088500.pdf" H 6100 3550 50  0001 C CNN
	1    6100 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal Y1
U 1 1 5D5DC690
P 4900 4000
F 0 "Y1" V 4854 4131 50  0000 L CNN
F 1 "32.768" V 4945 4131 50  0000 L CNN
F 2 "Crystal:Crystal_DS26_D2.0mm_L6.0mm_Horizontal" H 4900 4000 50  0001 C CNN
F 3 "~" H 4900 4000 50  0001 C CNN
	1    4900 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 3850 5600 3850
Wire Wire Line
	4900 4150 5450 4150
Wire Wire Line
	5450 4150 5450 3950
Wire Wire Line
	5450 3950 5600 3950
$Comp
L Device:C C3
U 1 1 5D5DD4B0
P 4450 3850
F 0 "C3" V 4198 3850 50  0000 C CNN
F 1 "10p" V 4289 3850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4488 3700 50  0001 C CNN
F 3 "~" H 4450 3850 50  0001 C CNN
	1    4450 3850
	0    1    1    0   
$EndComp
$Comp
L Device:C C4
U 1 1 5D5DD8E7
P 4450 4150
F 0 "C4" V 4650 4150 50  0000 C CNN
F 1 "10p" V 4750 4150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4488 4000 50  0001 C CNN
F 3 "~" H 4450 4150 50  0001 C CNN
	1    4450 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	4600 3850 4900 3850
Connection ~ 4900 3850
Wire Wire Line
	4600 4150 4900 4150
Connection ~ 4900 4150
$Comp
L power:GND #PWR0101
U 1 1 5D5DECA4
P 4150 4200
F 0 "#PWR0101" H 4150 3950 50  0001 C CNN
F 1 "GND" H 4155 4027 50  0000 C CNN
F 2 "" H 4150 4200 50  0001 C CNN
F 3 "" H 4150 4200 50  0001 C CNN
	1    4150 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 3850 4150 3850
Wire Wire Line
	4150 3850 4150 4150
Wire Wire Line
	4300 4150 4150 4150
Connection ~ 4150 4150
Wire Wire Line
	4150 4150 4150 4200
$Comp
L power:GND #PWR0102
U 1 1 5D5DF843
P 6100 4350
F 0 "#PWR0102" H 6100 4100 50  0001 C CNN
F 1 "GND" H 5950 4300 50  0000 C CNN
F 2 "" H 6100 4350 50  0001 C CNN
F 3 "" H 6100 4350 50  0001 C CNN
	1    6100 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5D5E07D5
P 5400 2900
F 0 "R1" H 5470 2946 50  0000 L CNN
F 1 "10k" H 5470 2855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5330 2900 50  0001 C CNN
F 3 "~" H 5400 2900 50  0001 C CNN
	1    5400 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5D5E0BFF
P 5400 3400
F 0 "R2" H 5470 3446 50  0000 L CNN
F 1 "10k" H 5470 3355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5330 3400 50  0001 C CNN
F 3 "~" H 5400 3400 50  0001 C CNN
	1    5400 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 3050 5400 3050
Wire Wire Line
	5600 3250 5400 3250
$Comp
L power:GND #PWR0103
U 1 1 5D5E132B
P 5400 3550
F 0 "#PWR0103" H 5400 3300 50  0001 C CNN
F 1 "GND" H 5405 3377 50  0000 C CNN
F 2 "" H 5400 3550 50  0001 C CNN
F 3 "" H 5400 3550 50  0001 C CNN
	1    5400 3550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0104
U 1 1 5D5E15FD
P 5200 2650
F 0 "#PWR0104" H 5200 2500 50  0001 C CNN
F 1 "+3.3V" V 5215 2778 50  0000 L CNN
F 2 "" H 5200 2650 50  0001 C CNN
F 3 "" H 5200 2650 50  0001 C CNN
	1    5200 2650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5200 2650 5400 2650
Wire Wire Line
	5400 2650 5400 2750
Wire Wire Line
	5400 2650 6100 2650
Wire Wire Line
	6100 2650 6100 2850
Connection ~ 5400 2650
Wire Wire Line
	6100 2650 6200 2650
Wire Wire Line
	6200 2650 6200 2850
Connection ~ 6100 2650
Wire Wire Line
	6600 3050 6650 3050
$Comp
L Switch:SW_SPST SW2
U 1 1 5D5F190F
P 6800 3450
F 0 "SW2" H 6950 3350 50  0000 C CNN
F 1 "SET" H 7150 3350 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_CK_RS282G05A3" H 6800 3450 50  0001 C CNN
F 3 "~" H 6800 3450 50  0001 C CNN
	1    6800 3450
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW1
U 1 1 5D5F14F3
P 6800 3350
F 0 "SW1" H 6950 3400 50  0000 C CNN
F 1 "WAKE" H 7100 3400 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_CK_RS282G05A3" H 6800 3350 50  0001 C CNN
F 3 "~" H 6800 3350 50  0001 C CNN
	1    6800 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5D5F4234
P 7350 3450
F 0 "#PWR0106" H 7350 3200 50  0001 C CNN
F 1 "GND" H 7355 3277 50  0000 C CNN
F 2 "" H 7350 3450 50  0001 C CNN
F 3 "" H 7350 3450 50  0001 C CNN
	1    7350 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 3150 6750 3150
Wire Wire Line
	7350 3350 7350 3450
Wire Wire Line
	7000 3350 7350 3350
Wire Wire Line
	7000 3450 7350 3450
Connection ~ 7350 3450
$Comp
L Device:LED D1
U 1 1 5D603600
P 7950 4250
F 0 "D1" H 7550 4050 50  0000 C CNN
F 1 "LED0" H 7550 4150 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 7950 4250 50  0001 C CNN
F 3 "~" H 7950 4250 50  0001 C CNN
	1    7950 4250
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D2
U 1 1 5D603E47
P 7950 4400
F 0 "D2" H 7550 4250 50  0000 C CNN
F 1 "LED1" H 7550 4350 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 7950 4400 50  0001 C CNN
F 3 "~" H 7950 4400 50  0001 C CNN
	1    7950 4400
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D3
U 1 1 5D6042BF
P 7950 4550
F 0 "D3" H 7550 4450 50  0000 C CNN
F 1 "LED2" H 7550 4550 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 7950 4550 50  0001 C CNN
F 3 "~" H 7950 4550 50  0001 C CNN
	1    7950 4550
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D4
U 1 1 5D60484A
P 7950 4700
F 0 "D4" H 7550 4650 50  0000 C CNN
F 1 "LED3" H 7550 4750 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 7950 4700 50  0001 C CNN
F 3 "~" H 7950 4700 50  0001 C CNN
	1    7950 4700
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D5
U 1 1 5D604BF8
P 7950 4850
F 0 "D5" H 7550 4850 50  0000 C CNN
F 1 "LED4" H 7550 4950 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 7950 4850 50  0001 C CNN
F 3 "~" H 7950 4850 50  0001 C CNN
	1    7950 4850
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D6
U 1 1 5D604DB4
P 7950 5000
F 0 "D6" H 7550 5050 50  0000 C CNN
F 1 "LED5" H 7550 5150 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 7950 5000 50  0001 C CNN
F 3 "~" H 7950 5000 50  0001 C CNN
	1    7950 5000
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D7
U 1 1 5D604F84
P 7950 5150
F 0 "D7" H 7550 5250 50  0000 C CNN
F 1 "LED6" H 7550 5350 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 7950 5150 50  0001 C CNN
F 3 "~" H 7950 5150 50  0001 C CNN
	1    7950 5150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5D611A16
P 8200 5450
F 0 "#PWR0107" H 8200 5200 50  0001 C CNN
F 1 "GND" H 8205 5277 50  0000 C CNN
F 2 "" H 8200 5450 50  0001 C CNN
F 3 "" H 8200 5450 50  0001 C CNN
	1    8200 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 4250 8200 4250
Wire Wire Line
	8200 4250 8200 4400
Wire Wire Line
	8100 4400 8200 4400
Connection ~ 8200 4400
Wire Wire Line
	8200 4400 8200 4550
Wire Wire Line
	8100 4550 8200 4550
Connection ~ 8200 4550
Wire Wire Line
	8200 4550 8200 4700
Wire Wire Line
	8100 4700 8200 4700
Connection ~ 8200 4700
Wire Wire Line
	8200 4700 8200 4850
Wire Wire Line
	8100 4850 8200 4850
Connection ~ 8200 4850
Wire Wire Line
	8200 4850 8200 5000
Wire Wire Line
	8100 5000 8200 5000
Connection ~ 8200 5000
Wire Wire Line
	8200 5000 8200 5150
Wire Wire Line
	8100 5150 8200 5150
Connection ~ 8200 5150
Wire Wire Line
	8200 5150 8200 5450
$Comp
L Device:R R4
U 1 1 5D61728B
P 7650 4250
F 0 "R4" V 7550 4450 50  0000 C CNN
F 1 "1k" V 7550 4250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7580 4250 50  0001 C CNN
F 3 "~" H 7650 4250 50  0001 C CNN
	1    7650 4250
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 5D619D31
P 7650 4400
F 0 "R5" V 7550 4600 50  0000 C CNN
F 1 "1k" V 7550 4400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7580 4400 50  0001 C CNN
F 3 "~" H 7650 4400 50  0001 C CNN
	1    7650 4400
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 5D61A6B6
P 7650 4550
F 0 "R6" V 7550 4750 50  0000 C CNN
F 1 "1k" V 7550 4550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7580 4550 50  0001 C CNN
F 3 "~" H 7650 4550 50  0001 C CNN
	1    7650 4550
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 5D61B052
P 7650 4700
F 0 "R7" V 7550 4900 50  0000 C CNN
F 1 "1k" V 7550 4700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7580 4700 50  0001 C CNN
F 3 "~" H 7650 4700 50  0001 C CNN
	1    7650 4700
	0    1    1    0   
$EndComp
$Comp
L Device:R R8
U 1 1 5D61B9DA
P 7650 4850
F 0 "R8" V 7550 5050 50  0000 C CNN
F 1 "1k" V 7550 4850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7580 4850 50  0001 C CNN
F 3 "~" H 7650 4850 50  0001 C CNN
	1    7650 4850
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 5D61C420
P 7650 5000
F 0 "R9" V 7550 5200 50  0000 C CNN
F 1 "1k" V 7550 5000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7580 5000 50  0001 C CNN
F 3 "~" H 7650 5000 50  0001 C CNN
	1    7650 5000
	0    1    1    0   
$EndComp
$Comp
L Device:R R10
U 1 1 5D61CE91
P 7650 5150
F 0 "R10" V 7550 5350 50  0000 C CNN
F 1 "1k" V 7550 5150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7580 5150 50  0001 C CNN
F 3 "~" H 7650 5150 50  0001 C CNN
	1    7650 5150
	0    1    1    0   
$EndComp
Wire Wire Line
	6600 3650 7100 3650
Wire Wire Line
	7100 3650 7100 4250
Wire Wire Line
	7100 4250 7500 4250
Wire Wire Line
	6600 3750 7050 3750
Wire Wire Line
	7050 3750 7050 4400
Wire Wire Line
	7050 4400 7500 4400
Wire Wire Line
	5600 4150 5600 4550
Wire Wire Line
	5600 4550 7500 4550
Wire Wire Line
	6600 3850 7000 3850
Wire Wire Line
	7000 3850 7000 4700
Wire Wire Line
	7000 4700 7500 4700
Wire Wire Line
	6600 3950 6950 3950
Wire Wire Line
	6950 3950 6950 4850
Wire Wire Line
	6950 4850 7500 4850
Wire Wire Line
	6600 4050 6900 4050
Wire Wire Line
	6900 4050 6900 5000
Wire Wire Line
	6900 5000 7500 5000
Wire Wire Line
	6600 4150 6850 4150
Wire Wire Line
	6850 4150 6850 5150
Wire Wire Line
	6850 5150 7500 5150
$Comp
L Device:Battery_Cell BT1
U 1 1 5D63567B
P 1700 2500
F 0 "BT1" H 1818 2596 50  0000 L CNN
F 1 "Battery_Cell" H 1818 2505 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_1060_1x2032" V 1700 2560 50  0001 C CNN
F 3 "~" V 1700 2560 50  0001 C CNN
	1    1700 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5D637B5E
P 1700 2600
F 0 "#PWR0108" H 1700 2350 50  0001 C CNN
F 1 "GND" H 1705 2427 50  0000 C CNN
F 2 "" H 1700 2600 50  0001 C CNN
F 3 "" H 1700 2600 50  0001 C CNN
	1    1700 2600
	1    0    0    -1  
$EndComp
Text GLabel 5250 3050 0    50   Input ~ 0
RST
Wire Wire Line
	5250 3050 5400 3050
Connection ~ 5400 3050
Text GLabel 5250 2400 0    50   Input ~ 0
Vcc
Wire Wire Line
	5250 2400 5400 2400
Wire Wire Line
	5400 2400 5400 2650
Text GLabel 5250 2250 0    50   Input ~ 0
CLK
Wire Wire Line
	5250 2250 6650 2250
Wire Wire Line
	6650 2250 6650 3050
Connection ~ 6650 3050
Text GLabel 5250 2100 0    50   Input ~ 0
DIO
Wire Wire Line
	5250 2100 6750 2100
Wire Wire Line
	6750 2100 6750 3150
Text GLabel 5250 3200 0    50   Input ~ 0
GND
$Comp
L power:GND #PWR0109
U 1 1 5D657C6E
P 5250 3300
F 0 "#PWR0109" H 5250 3050 50  0001 C CNN
F 1 "GND" H 5255 3127 50  0000 C CNN
F 2 "" H 5250 3300 50  0001 C CNN
F 3 "" H 5250 3300 50  0001 C CNN
	1    5250 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3200 5250 3300
$Comp
L Regulator_Linear:TC1186 U1
U 1 1 5D6B1217
P 3550 2400
F 0 "U1" H 3550 2725 50  0000 C CNN
F 1 "TC1185-3.3VCT8" H 3550 2634 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 3550 2675 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21350E.pdf" H 3250 2600 50  0001 C CNN
	1    3550 2400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0110
U 1 1 5D6C8206
P 1700 2300
F 0 "#PWR0110" H 1700 2150 50  0001 C CNN
F 1 "+5V" H 1715 2473 50  0000 C CNN
F 2 "" H 1700 2300 50  0001 C CNN
F 3 "" H 1700 2300 50  0001 C CNN
	1    1700 2300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J1
U 1 1 5D6C8721
P 1000 2500
F 0 "J1" H 892 2175 50  0000 C CNN
F 1 "Charging port" H 892 2266 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 1000 2500 50  0001 C CNN
F 3 "~" H 1000 2500 50  0001 C CNN
	1    1000 2500
	-1   0    0    1   
$EndComp
Wire Wire Line
	1200 2400 1500 2400
Wire Wire Line
	1500 2400 1500 2300
Wire Wire Line
	1500 2300 1700 2300
Connection ~ 1700 2300
Wire Wire Line
	1200 2500 1500 2500
Wire Wire Line
	1500 2500 1500 2600
Wire Wire Line
	1500 2600 1700 2600
Connection ~ 1700 2600
Wire Wire Line
	3150 2400 2900 2400
Wire Wire Line
	2900 2400 2900 2300
Connection ~ 2900 2300
Wire Wire Line
	2900 2300 3150 2300
$Comp
L Device:C C1
U 1 1 5D6DA98F
P 2550 2450
F 0 "C1" H 2665 2496 50  0000 L CNN
F 1 "100n" H 2665 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2588 2300 50  0001 C CNN
F 3 "~" H 2550 2450 50  0001 C CNN
	1    2550 2450
	1    0    0    -1  
$EndComp
Connection ~ 2550 2300
Wire Wire Line
	2550 2300 2900 2300
Wire Wire Line
	2550 2600 2550 2750
Wire Wire Line
	2550 2750 3550 2750
Wire Wire Line
	3550 2750 3550 2700
$Comp
L power:GND #PWR0111
U 1 1 5D6DD730
P 2550 2750
F 0 "#PWR0111" H 2550 2500 50  0001 C CNN
F 1 "GND" H 2555 2577 50  0000 C CNN
F 2 "" H 2550 2750 50  0001 C CNN
F 3 "" H 2550 2750 50  0001 C CNN
	1    2550 2750
	1    0    0    -1  
$EndComp
Connection ~ 2550 2750
NoConn ~ 3950 2400
$Comp
L power:+3.3V #PWR0112
U 1 1 5D6E03DB
P 4250 2300
F 0 "#PWR0112" H 4250 2150 50  0001 C CNN
F 1 "+3.3V" H 4265 2473 50  0000 C CNN
F 2 "" H 4250 2300 50  0001 C CNN
F 3 "" H 4250 2300 50  0001 C CNN
	1    4250 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 2300 4150 2300
$Comp
L Device:C C2
U 1 1 5D6E34A0
P 4150 2450
F 0 "C2" H 4265 2496 50  0000 L CNN
F 1 "100n" H 4265 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4188 2300 50  0001 C CNN
F 3 "~" H 4150 2450 50  0001 C CNN
	1    4150 2450
	1    0    0    -1  
$EndComp
Connection ~ 4150 2300
Wire Wire Line
	4150 2300 4250 2300
Wire Wire Line
	3550 2750 4150 2750
Wire Wire Line
	4150 2750 4150 2600
Connection ~ 3550 2750
$Comp
L Transistor_FET:BS170F Q1
U 1 1 5D6E790C
P 10000 4050
F 0 "Q1" H 10206 4096 50  0000 L CNN
F 1 "IRLML0030TR" H 10206 4005 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 10200 3975 50  0001 L CIN
F 3 "http://www.diodes.com/assets/Datasheets/BS170F.pdf" H 10000 4050 50  0001 L CNN
	1    10000 4050
	1    0    0    -1  
$EndComp
Text GLabel 9050 4050 0    50   Input ~ 0
MOTOR
$Comp
L Device:R R11
U 1 1 5D6EACFF
P 9750 4350
F 0 "R11" H 9820 4396 50  0000 L CNN
F 1 "15k" H 9820 4305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9680 4350 50  0001 C CNN
F 3 "~" H 9750 4350 50  0001 C CNN
	1    9750 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5D6ED7E2
P 9750 4500
F 0 "#PWR0113" H 9750 4250 50  0001 C CNN
F 1 "GND" H 9755 4327 50  0000 C CNN
F 2 "" H 9750 4500 50  0001 C CNN
F 3 "" H 9750 4500 50  0001 C CNN
	1    9750 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 4200 9750 4050
Wire Wire Line
	9750 4050 9800 4050
Wire Wire Line
	9750 4500 10100 4500
Wire Wire Line
	10100 4500 10100 4250
Connection ~ 9750 4500
$Comp
L Motor:Motor_DC M1
U 1 1 5D70604F
P 10100 3550
F 0 "M1" H 10258 3546 50  0000 L CNN
F 1 "Motor_DC" H 10258 3455 50  0000 L CNN
F 2 "LED_SMD:LED_2816_7142Metric" H 10100 3460 50  0001 C CNN
F 3 "~" H 10100 3460 50  0001 C CNN
	1    10100 3550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0114
U 1 1 5D706B73
P 10100 3350
F 0 "#PWR0114" H 10100 3200 50  0001 C CNN
F 1 "+5V" H 10115 3523 50  0000 C CNN
F 2 "" H 10100 3350 50  0001 C CNN
F 3 "" H 10100 3350 50  0001 C CNN
	1    10100 3350
	1    0    0    -1  
$EndComp
Text GLabel 7250 2650 2    50   Input ~ 0
MOTOR
Wire Wire Line
	6650 3050 7150 3050
Wire Wire Line
	7250 2650 7150 2650
Wire Wire Line
	7150 2650 7150 3050
Connection ~ 7150 3050
NoConn ~ 6600 3250
Wire Wire Line
	1700 2600 2000 2600
Wire Wire Line
	1700 2300 2100 2300
$Comp
L Connector:Conn_01x02_Female J2
U 1 1 5D75A7C0
P 2100 2800
F 0 "J2" V 2150 2650 50  0000 L CNN
F 1 "Cell pad" V 2250 2650 50  0000 L CNN
F 2 "LED_SMD:LED_2512_6332Metric_Pad1.52x3.35mm_HandSolder" H 2100 2800 50  0001 C CNN
F 3 "~" H 2100 2800 50  0001 C CNN
	1    2100 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	2100 2600 2100 2300
Connection ~ 2100 2300
Wire Wire Line
	2100 2300 2550 2300
$Comp
L Sensor_Magnetic:A1104LLHL U4
U 1 1 5D84C99C
P 8300 3450
F 0 "U4" H 8070 3496 50  0000 R CNN
F 1 "SS311PT" H 8070 3405 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8300 3100 50  0001 L CIN
F 3 "http://www.allegromicro.com/en/Products/Part_Numbers/1101/1101.pdf" H 8300 4100 50  0001 C CNN
	1    8300 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5D86D800
P 9500 4050
F 0 "R3" V 9293 4050 50  0000 C CNN
F 1 "220R" V 9384 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9430 4050 50  0001 C CNN
F 3 "~" H 9500 4050 50  0001 C CNN
	1    9500 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	9650 4050 9750 4050
Connection ~ 9750 4050
Wire Wire Line
	9050 4050 9350 4050
Wire Wire Line
	8200 3850 8200 4250
Connection ~ 8200 4250
Wire Wire Line
	7150 3050 8200 3050
Wire Wire Line
	8600 3450 8600 2100
Wire Wire Line
	8600 2100 6750 2100
Connection ~ 6750 2100
Text GLabel 6600 3550 2    50   Input ~ 0
VBAT
$Comp
L Device:R R12
U 1 1 5D886213
P 2450 3650
F 0 "R12" H 2520 3696 50  0000 L CNN
F 1 "47k" H 2520 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2380 3650 50  0001 C CNN
F 3 "~" H 2450 3650 50  0001 C CNN
	1    2450 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R13
U 1 1 5D8864F7
P 2450 4100
F 0 "R13" H 2520 4146 50  0000 L CNN
F 1 "47k" H 2520 4055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2380 4100 50  0001 C CNN
F 3 "~" H 2450 4100 50  0001 C CNN
	1    2450 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5D887AC4
P 2850 4100
F 0 "C5" H 2965 4146 50  0000 L CNN
F 1 "2.2u" H 2965 4055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2888 3950 50  0001 C CNN
F 3 "~" H 2850 4100 50  0001 C CNN
	1    2850 4100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 5D8901AD
P 2450 3500
F 0 "#PWR01" H 2450 3350 50  0001 C CNN
F 1 "+5V" H 2465 3673 50  0000 C CNN
F 2 "" H 2450 3500 50  0001 C CNN
F 3 "" H 2450 3500 50  0001 C CNN
	1    2450 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5D8910CD
P 2450 4250
F 0 "#PWR02" H 2450 4000 50  0001 C CNN
F 1 "GND" H 2455 4077 50  0000 C CNN
F 2 "" H 2450 4250 50  0001 C CNN
F 3 "" H 2450 4250 50  0001 C CNN
	1    2450 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 4250 2450 4250
Connection ~ 2450 4250
Wire Wire Line
	2450 3800 2450 3900
Wire Wire Line
	2450 3900 2850 3900
Wire Wire Line
	2850 3900 2850 3950
Connection ~ 2450 3900
Wire Wire Line
	2450 3900 2450 3950
Text GLabel 3250 3900 2    50   Input ~ 0
VBAT
Wire Wire Line
	3250 3900 2850 3900
Connection ~ 2850 3900
$EndSCHEMATC
