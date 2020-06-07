EESchema Schematic File Version 4
LIBS:circuit-cache
EELAYER 26 0
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
L power:GND #PWR0101
U 1 1 5BBB4335
P 1575 2775
F 0 "#PWR0101" H 1575 2525 50  0001 C CNN
F 1 "GND" H 1575 2625 50  0000 C CNN
F 2 "" H 1575 2775 50  0001 C CNN
F 3 "" H 1575 2775 50  0001 C CNN
	1    1575 2775
	1    0    0    -1  
$EndComp
Wire Wire Line
	1575 2275 1575 2375
Wire Wire Line
	1625 2475 1575 2475
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 5BDDDC52
P 1375 2475
F 0 "J1" H 1425 2675 50  0000 C CNN
F 1 "Power" V 1475 2425 50  0000 C CNN
F 2 "Connector_JST:JST_XH_S04B-XH-A-1_1x04_P2.50mm_Horizontal" H 1375 2475 50  0001 C CNN
F 3 "~" H 1375 2475 50  0001 C CNN
	1    1375 2475
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1575 2775 1575 2675
Wire Wire Line
	1625 2575 1575 2575
Text Notes 1250 1925 0    79   ~ 16
Connector
Text GLabel 7825 2350 0    50   Input ~ 0
a
Text GLabel 7825 2450 0    50   Input ~ 0
b
Text GLabel 7825 2550 0    50   Input ~ 0
c
Text GLabel 7825 2650 0    50   Input ~ 0
d
Text GLabel 7825 2750 0    50   Input ~ 0
e
Text GLabel 7825 2850 0    50   Input ~ 0
f
Text GLabel 7825 2950 0    50   Input ~ 0
g
Text GLabel 7825 3050 0    50   Input ~ 0
dot
Wire Wire Line
	7825 2350 7925 2350
Wire Wire Line
	7925 2450 7825 2450
Wire Wire Line
	7825 2550 7925 2550
Wire Wire Line
	7925 2650 7825 2650
Wire Wire Line
	7825 2750 7925 2750
Wire Wire Line
	7925 2850 7825 2850
Wire Wire Line
	7825 2950 7925 2950
Wire Wire Line
	7925 3050 7825 3050
Text GLabel 10225 2750 2    50   Input ~ 0
Seg1
Text GLabel 10225 2850 2    50   Input ~ 0
Seg2
Text GLabel 10225 2950 2    50   Input ~ 0
Seg3
Text GLabel 10225 3050 2    50   Input ~ 0
Seg4
Wire Wire Line
	10225 2750 10125 2750
Wire Wire Line
	10125 2850 10225 2850
Wire Wire Line
	10225 2950 10125 2950
Wire Wire Line
	10125 3050 10225 3050
$Comp
L Display_Character:CA56-12EWA U2
U 1 1 5CA9CD7B
P 9025 2650
F 0 "U2" H 9025 3317 50  0000 C CNN
F 1 "CA56-12EWA" H 9025 3226 50  0000 C CNN
F 2 "Display_7Segment:CA56-12EWA" H 9025 2050 50  0001 C CNN
F 3 "http://www.kingbrightusa.com/images/catalog/SPEC/CA56-12EWA.pdf" H 8595 2680 50  0001 C CNN
	1    9025 2650
	1    0    0    -1  
$EndComp
Text Notes 6525 1725 0    79   ~ 16
7 Segment Display & LED Driver
$Comp
L power:+5V #PWR0102
U 1 1 5CA39DC1
P 5050 2500
F 0 "#PWR0102" H 5050 2350 50  0001 C CNN
F 1 "+5V" H 5050 2640 50  0000 C CNN
F 2 "" H 5050 2500 50  0001 C CNN
F 3 "" H 5050 2500 50  0001 C CNN
	1    5050 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5CA39DBB
P 5050 3000
AR Path="/5CA39DBB" Ref="#PWR0103"  Part="1" 
AR Path="/5BE24A28/5CA39DBB" Ref="#PWR?"  Part="1" 
F 0 "#PWR0103" H 5050 2750 50  0001 C CNN
F 1 "GND" H 5050 2850 50  0000 C CNN
F 2 "" H 5050 3000 50  0001 C CNN
F 3 "" H 5050 3000 50  0001 C CNN
	1    5050 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 2600 5050 2500
Wire Wire Line
	5050 3000 5050 2900
$Comp
L Device:C C2
U 1 1 5CA39DB3
P 5050 2750
AR Path="/5CA39DB3" Ref="C2"  Part="1" 
AR Path="/5BE24A28/5CA39DB3" Ref="C?"  Part="1" 
F 0 "C2" H 5075 2850 50  0000 L CNN
F 1 "100n" H 5075 2650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5088 2600 50  0001 C CNN
F 3 "" H 5050 2750 50  0001 C CNN
	1    5050 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 5CA2D950
P 4700 2750
F 0 "C1" H 4725 2850 50  0000 L CNN
F 1 "100µ" H 4725 2650 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3216-10_Kemet-I_Pad1.58x1.35mm_HandSolder" H 4738 2600 50  0001 C CNN
F 3 "" H 4700 2750 50  0001 C CNN
	1    4700 2750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5CA2D94A
P 4700 2500
F 0 "#PWR0104" H 4700 2350 50  0001 C CNN
F 1 "+5V" H 4700 2640 50  0000 C CNN
F 2 "" H 4700 2500 50  0001 C CNN
F 3 "" H 4700 2500 50  0001 C CNN
	1    4700 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5CA2D944
P 4700 3000
F 0 "#PWR0105" H 4700 2750 50  0001 C CNN
F 1 "GND" H 4700 2850 50  0000 C CNN
F 2 "" H 4700 3000 50  0001 C CNN
F 3 "" H 4700 3000 50  0001 C CNN
	1    4700 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2600 4700 2500
Wire Wire Line
	4700 3000 4700 2900
Wire Wire Line
	7100 2450 7000 2450
Wire Wire Line
	7100 2550 7000 2550
Text GLabel 7100 2450 2    50   BiDi ~ 0
CLK
Text GLabel 7100 2550 2    50   BiDi ~ 0
DIO
Wire Wire Line
	5850 3050 5750 3050
Wire Wire Line
	5750 2950 5850 2950
Wire Wire Line
	5850 2850 5750 2850
Wire Wire Line
	5750 2750 5850 2750
Wire Wire Line
	5850 2650 5750 2650
Wire Wire Line
	5750 2550 5850 2550
Wire Wire Line
	5850 2450 5750 2450
Wire Wire Line
	5750 2350 5850 2350
Text GLabel 5750 3050 0    50   Output ~ 0
dot
Text GLabel 5750 2950 0    50   Output ~ 0
g
Text GLabel 5750 2850 0    50   Output ~ 0
f
Text GLabel 5750 2750 0    50   Output ~ 0
e
Text GLabel 5750 2650 0    50   Output ~ 0
d
Text GLabel 5750 2550 0    50   Output ~ 0
c
Text GLabel 5750 2450 0    50   Output ~ 0
b
Text GLabel 5750 2350 0    50   Output ~ 0
a
Wire Wire Line
	7000 3050 7100 3050
Wire Wire Line
	7100 2950 7000 2950
Wire Wire Line
	7000 2850 7100 2850
Wire Wire Line
	7100 2750 7000 2750
Text GLabel 7100 3050 2    50   Output ~ 0
Seg4
Text GLabel 7100 2950 2    50   Output ~ 0
Seg3
Text GLabel 7100 2850 2    50   Output ~ 0
Seg2
Text GLabel 7100 2750 2    50   Output ~ 0
Seg1
Wire Wire Line
	7450 2650 7000 2650
Wire Wire Line
	5500 2250 5850 2250
$Comp
L power:GND #PWR0106
U 1 1 5C93BECE
P 5500 2250
F 0 "#PWR0106" H 5500 2000 50  0001 C CNN
F 1 "GND" H 5500 2100 50  0000 C CNN
F 2 "" H 5500 2250 50  0001 C CNN
F 3 "" H 5500 2250 50  0001 C CNN
	1    5500 2250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0107
U 1 1 5C93BDEB
P 7450 2650
F 0 "#PWR0107" H 7450 2500 50  0001 C CNN
F 1 "+5V" H 7450 2790 50  0000 C CNN
F 2 "" H 7450 2650 50  0001 C CNN
F 3 "" H 7450 2650 50  0001 C CNN
	1    7450 2650
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:TM1637 U?
U 1 1 5C91D38F
P 6450 2550
AR Path="/5C915547/5C91D38F" Ref="U?"  Part="1" 
AR Path="/5C91D38F" Ref="U1"  Part="1" 
F 0 "U1" H 6425 3137 60  0000 C CNN
F 1 "TM1637" H 6425 3031 60  0000 C CNN
F 2 "Package_SO:SOIC-20W_7.5x12.8mm_P1.27mm" H 6450 2550 60  0001 C CNN
F 3 "" H 6450 2550 60  0000 C CNN
	1    6450 2550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0108
U 1 1 5D24DB82
P 1575 2275
F 0 "#PWR0108" H 1575 2125 50  0001 C CNN
F 1 "+5V" H 1575 2415 50  0000 C CNN
F 2 "" H 1575 2275 50  0001 C CNN
F 3 "" H 1575 2275 50  0001 C CNN
	1    1575 2275
	1    0    0    -1  
$EndComp
Text GLabel 1625 2475 2    50   BiDi ~ 0
CLK
Text GLabel 1625 2575 2    50   BiDi ~ 0
DIO
Text GLabel 3450 2750 2    50   BiDi ~ 0
CLK
Text GLabel 3450 2850 2    50   BiDi ~ 0
DIO
Text GLabel 3150 2750 0    50   BiDi ~ 0
CLK
Text GLabel 3150 2850 0    50   BiDi ~ 0
DIO
Wire Wire Line
	3150 2750 3225 2750
Wire Wire Line
	3450 2850 3375 2850
$Comp
L power:+5V #PWR0109
U 1 1 5D250A52
P 3300 2375
F 0 "#PWR0109" H 3300 2225 50  0001 C CNN
F 1 "+5V" H 3300 2515 50  0000 C CNN
F 2 "" H 3300 2375 50  0001 C CNN
F 3 "" H 3300 2375 50  0001 C CNN
	1    3300 2375
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5D250AC8
P 3375 2550
F 0 "R2" H 3445 2596 50  0000 L CNN
F 1 "10k" H 3445 2505 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3305 2550 50  0001 C CNN
F 3 "~" H 3375 2550 50  0001 C CNN
	1    3375 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5D250BAA
P 3225 2550
F 0 "R1" H 3375 2600 50  0000 R CNN
F 1 "10k" H 3425 2500 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3155 2550 50  0001 C CNN
F 3 "~" H 3225 2550 50  0001 C CNN
	1    3225 2550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3375 2400 3375 2375
Wire Wire Line
	3375 2375 3300 2375
Wire Wire Line
	3225 2400 3225 2375
Wire Wire Line
	3225 2375 3300 2375
Connection ~ 3300 2375
Wire Wire Line
	3225 2700 3225 2750
Connection ~ 3225 2750
Wire Wire Line
	3225 2750 3450 2750
Wire Wire Line
	3375 2700 3375 2850
Connection ~ 3375 2850
Wire Wire Line
	3375 2850 3150 2850
Text Notes 3025 2075 0    79   ~ 16
Pull-Ups
$EndSCHEMATC
