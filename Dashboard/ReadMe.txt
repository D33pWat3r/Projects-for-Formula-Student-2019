Creator: Rick Hollinski
Date: 2019-06-05

Version: 1.1

Tech Specs:
 - Spannungsversorgung: 6V - 30V
 - Leistungsverbrauch: max. 10W
 - Neopixel Strom Output: max. 2A (max. 33Leds bei 100% Weiß)
 - Mikrocontroller: Atmega328p (5V; 16MHz)
 - Programmierung: über ISP Header
 - PinOut (Arduino Labels): 4x 5V, 4x Gnd, A0-A3, 3x A4(SDA), 3x A5(SCL), 0(Rx), 1(Tx), 3, 5, 6, 7, 8, 9, 11(MoSi), 12(MiSo), 13 (SCK)
 

Fehler in Version 1.0:
 - Kondensator C19 darf nicht verlötet werden
 - die Ground Plane auf der Rückseite unter dem Buck Converter (MP1584), welche
	auch als Kühlkörper und als Wärmekapazität dient, war fehlerhaft eingezeichnet und ist deshalb nicht vorhanden
	
Mögliche Verbesserungen für nächste Revision (1.2):
 - 	die Pins, welche an den TM1637 angeschlossen sind, sollten gegen andere freie Pins getauscht werden.
	Somit wären die I2C Pins auch verfügbar, wenn das 7-Segment Display genutzt wird.
 
Funktionen der Platine:
  - die Platine ist Grundlegend ein Arduino Board (Atmega328p) [1]
  - für die Kommunikation mit dem CAN Bus wird der IC MCP2515 [2] genutzt und als Tranceiver MCP2551 [3]
  - die Verschaltung für CAN wurde größtenteils vom "SparkFun CAN-Bus Shield" [4] übernommen
  - für die 5V Spannungsversorgung wurde sich für einen Buck Converter [5] entschieden, da ein
	max. Strom von max. 2A benötigt wird. Ein Linear Regler würde nur heiß laufen.
  - Als Ausgabe kann ein 7-Segment Display (4 Zeichen + Punkte; gemeinsamer Plus Connector) [6] genutzt werden. Als Treiber wurde der TM1637 [7] genutzt.
  - Zudem besteht die Möglichkeit alternativ zum 7 Segment Display 2x OLED Displays (0,96 Zoll) über I2C zu benutzten.
  - Als weitere Ausgabe, kann ein LED-RGB-Stripe (basierend auf WS2812) angeschlossen werden.
  
Software Bibliotheken:
  - zur Programmierung wird das C++ Framework "Arduino Core" ab Version 1.8 empfohlen
  - bei der Auswahl des Mikrocontrollers / Entwicklerboards in der Arduino IDE kann der "Arduino UNO" ausgewählt werden
  - zur Kommunikation per CAN wird die Bibliothek von "Seeed-Studio" [8] genutzt.
  - für die Ausgabe per 7-Segment Anzeige kann die Bibliothken von "avishorp" [9] genommen werden
  - die Ausgabe per LED Stripe wird über die Adafruit Bibliothek [10] realisiert
  - für die alternative Ausgabe per OLED Displays kann die Bibliothek von "olikraus" genutzt werden [11]
  
  
  
  Quellverzeichnis:
[1]  Arduino-Pro-Mini_3v3.pdf
[2]  MCP2515.pdf
[3]  MCP2551.pdf
[4]  SparkFun_CAN-Bus_Shield_v13a.pdf
[5]  MP1584_r1.0.pdf
[6]  Datasheet CL5642BH.pdf
[7]  Datasheet_TM1637.pdf

[8]  https://github.com/Seeed-Studio/CAN_BUS_Shield
[9]  https://github.com/avishorp/TM1637
[10]  https://github.com/adafruit/Adafruit_NeoPixel
[11] https://github.com/olikraus/U8g2_Arduino