/*

  Clock.ino
  
  Demonstrates a clock-like display with a very huge font.
  Also shows usage of u8x8_u8toa().

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/

#include <Arduino.h>
#include <U8g2lib.h>

#include <Wire.h>
#define digit 9
// Arduino-Pin verbunden mit SH_CP des 74HC595
int shiftPin = D7;
// Arduino-Pin verbunden mit ST_CP des 74HC595
int storePin = D6;
// Arduino-Pin verbunden mit DS des 74HC595
int dataPin = D5;
 
int digits[10][8] = { {1,1,1,0,1,1,1,0}, //0
                      {1,0,0,0,0,0,1,0}, //1
                      {1,0,1,1,1,1,0,0}, //2
                      {1,0,1,1,1,0,1,0}, //3
                      {1,1,0,1,0,0,1,0}, //4
                      {0,1,1,1,1,0,1,0}, //5
                      {0,1,1,1,1,1,1,0}, //6
                      {1,0,1,0,0,0,1,0}, //7
                      {1,1,1,1,1,1,1,0}, //8
                      {1,1,1,1,1,0,1,0}  //9
};

/*
  U8glib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
  This is a page buffer example.    
*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C Display1(U8G2_R3, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ D3, /* data=*/ D4);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C Display2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ D3, /* data=*/ D4);
//U8G2_SSD1306_128X64_NONAME_2_SW_I2C Display1(U8G2_R3, /* clock=*/ D3, /* data=*/ D4, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_2_SW_I2C Display2(U8G2_R2, /* clock=*/ D3, /* data=*/ D4, /* reset=*/ U8X8_PIN_NONE);


// End of constructor list

void segmentDigit(int a){
   digitalWrite(storePin, LOW); 

 for (int i=0; i<8; i++) {
 // Zuerst immer alle 3 Pins auf LOW
 // Aktion passiert bei Wechsel von LOW auf HIGH
 digitalWrite(shiftPin, LOW);
 // Jetzt den Wert der aktuellen Stelle ans Datenpin DS anlegen 
 digitalWrite(dataPin, digits[a][i]);
 // Dann ShiftPin SHCP von LOW auf HIGH, damit wird der Wert
 // am Datenpin ins Register geschoben. 
 digitalWrite(shiftPin, HIGH);
 }

 digitalWrite(storePin, HIGH);
}

void setup(void) {
  u8g2_SetI2CAddress(Display1.getU8g2(), 0x3d*2);
  Display1.begin();  

  u8g2_SetI2CAddress(Display2.getU8g2(), 0x3c*2);
  Display2.begin();

  // Pins 8,9,10 auf Ausgabe
 pinMode(storePin, OUTPUT);
 pinMode(shiftPin, OUTPUT);
 pinMode(dataPin, OUTPUT);
  // storePin sicherheitshalber auf LOW


}

uint8_t m = 0;

void loop(void) {
  segmentDigit(m%10);
  
  char m_str[3];
  
  Display1.firstPage();
  do {
    Display1.setFont(u8g2_font_logisoso92_tn);
    strcpy(m_str, u8x8_u8toa(m, 1));    /* convert m to a string with two digits */
    Display1.drawStr(0,110,m_str);
  } while ( Display1.nextPage() );

    Display2.firstPage();
  do {
    Display2.setFont(u8g2_font_logisoso62_tn);
    strcpy(m_str, u8x8_u8toa(m, 2));    /* convert m to a string with two digits */
    Display2.drawStr(30,63,m_str);
  } while ( Display2.nextPage() );
  delay(300);
  m++;
  m%=100;
}
