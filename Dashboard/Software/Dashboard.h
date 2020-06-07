#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "config.h" //Hardware Configuration

#include <Arduino.h> //Arduino Framework
#include <SPI.h>  //Arduino SPI Library

#define UMD_MAX_ENGINE_SPEED 13000

uint16_t rpm = 0;     //Engine RPM
uint16_t seconds = 0; //Seconds ECU has been on
float clt; //Coolant temperature CAN in degF saved in degC
float mat; //Manifold air temperature CAN in degF saved in degC
float map1; //Manifold air pressure;
float baro; //Barometric pressure;
float batt; //Battery voltage;
float tps; //Throttle position;
uint8_t gear; //Current gear selected
uint16_t fuelcons; //Average fuel consumption;
uint16_t fuelflow; //Average fuel flow;


// Debugging *********************************************
void initDebugging(uint32_t baud){
#if DEBUG
    Serial.begin(baud);
    #define DEBUG_PRINT_F(s)   { Serial.print(F(s)); }
    #define DEBUG_PRINT2_F(s,v) { Serial.print(F(s)); Serial.print(v); }
    #define DEBUG_PRINT(s)    { Serial.print(s); }
    #define DEBUG_PRINTLN(s)  { Serial.println(s); }
    #define DEBUG_PRINT2(x,y) { Serial.print(x,y);}
#else
    #define DEBUG_PRINT_F(s)
    #define DEBUG_PRINT2_F(s,v)
    #define DEBUG_PRINT(s)
    #define DEBUG_PRINTLN(s) 
    #define DEBUG_PRINT2(x,y)
#endif
}

// Demo Mode *********************************************
struct tDemo{
  uint8_t demoIs;
  uint8_t demoTarget;
  bool demoUp : 1;
  bool isDemoMode :1;
  uint32_t lastDemoCalc;
} demo = {0,100,true,true,0};

void demoCalcSpeed() {
  if(demo.demoUp) {
    demo.demoIs++;
    
    if(demo.demoIs == demo.demoTarget) {
      demo.demoTarget = random(0, demo.demoIs - 5);
      demo.demoUp = 0;                   //fallende Drehzahl
      clt = random(60, 100);
    }

  } else {  
    demo.demoIs--;
    
    if(demo.demoIs == demo.demoTarget) {
      demo.demoTarget = random(demo.demoIs + 5, 100);
      demo.demoUp = 1;                   //steigende Drehzahl
      gear = random(gear-1, gear+2);
      if(gear < 0)
        gear = 0;
        
      if(gear > 6)
        gear = 6;
    }
  }

  rpm = UMD_MAX_ENGINE_SPEED / 100 * demo.demoIs ;
  demo.lastDemoCalc = millis();
}


// 7-Segment *********************************************
#include "TM1637Display.h" //7-Segment Library by avishorp

TM1637Display display(DISPLAY_CLK, DISPLAY_DIO);
uint32_t lastDisplayFlash;
bool displayShow;
const uint8_t displayBlank[] = { 0x00, 0x00, 0x00, 0x00 };
const uint8_t umd[] = { 0b00111110, 0b00110011, 0b00100111, 0b00111111 };

void initDisplay(void){
    display.setBrightness(0x0f);
    display.setSegments(umd);
    lastDisplayFlash = millis();
}

void refreshDisplay(){
    display.setSegments(displayBlank, 1, 1);
    display.showNumberDec(clt, false, 3, 1);
    display.showNumberDec(gear, true, 1, 0);
}


// CAN *********************************************
#include "mcp_can.h" //CAN Library by Seed-Studio
#include "ConvertCanData.h"

MCP_CAN CAN(CAN_SPI_CS_PIN);
tCAN_Data CanData; //CAN "Stack"

void MCP2515_ISR() {
    CanData.flagCanRecv = 1;
    demo.isDemoMode = 0;   //disable DemoMode add first CAN-Data recive.
}

void initCAN(void){
while (CAN_OK != CAN.begin(CAN_500KBPS, MCP_16MHz))// init can bus : baudrate = 500k; 16MHz
{
    DEBUG_PRINTLN("CAN BUS Shield init fail");
    DEBUG_PRINTLN(" Init CAN BUS Shield again");
    delay(100);
}
    DEBUG_PRINTLN("CAN BUS Shield init ok!");
    attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), MCP2515_ISR, FALLING);
}


// Neopixel *********************************************
#include "Adafruit_NeoPixel.h" //WS2812b Library by Adafruit

Adafruit_NeoPixel neoPixels(NEOPIXEL_NUMBER_OF_LEDS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
uint32_t lastNeoFlash;
bool speedBarFlush = 0;

void initNeopixel(void){
    neoPixels.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
    neoPixels.show();            // Turn OFF all pixels ASAP
    neoPixels.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
    lastNeoFlash = millis();
}

const uint32_t red = neoPixels.Color(255, 0, 0); // Red
const uint32_t green = neoPixels.Color( 0, 255, 0); // Green
const uint32_t yellow = neoPixels.Color( 255, 255, 0); // Yellow
const uint32_t blue = neoPixels.Color( 0, 0, 255); // Blue

void updateSpeedBar(int percent) {
  uint8_t numNeoPixels = NEOPIXEL_NUMBER_OF_LEDS;
  const int speedLeds = numNeoPixels * percent / 100;

  if(speedLeds < numNeoPixels*0.69 || speedLeds > numNeoPixels*0.85) {
    speedBarFlush = 0;
    
  } else {
    if(speedBarFlush == 1) {
      speedBarFlush = 0;
      neoPixels.clear();
      neoPixels.show();
      lastNeoFlash = millis();
      return;
    }
    speedBarFlush = 1;
  }
  
  neoPixels.clear();
  for(int a=0; a < speedLeds; a++) {
    if(a < numNeoPixels*0.23)
      neoPixels.setPixelColor(a, blue);
    else if (a < numNeoPixels*0.69) 
      neoPixels.setPixelColor(a, green); // Set pixel 'c' to value 'color'
    else if (a < numNeoPixels*0.85) 
      neoPixels.setPixelColor(a, yellow); // Set pixel 'c' to value 'color'
    else
      neoPixels.setPixelColor(a, red); // Set pixel 'c' to value 'color'
  }
  neoPixels.show();
  lastNeoFlash = millis();
}

#endif