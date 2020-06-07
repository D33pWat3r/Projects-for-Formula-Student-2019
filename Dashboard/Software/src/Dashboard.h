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
float batt = 12.6f; //Battery voltage;
float tps; //Throttle position;
uint8_t gear; //Current gear selected
uint16_t fuelcons; //Average fuel consumption;
uint16_t fuelflow; //Average fuel flow;
bool shift; //Shift light indicator;

// Declerations ******************************************************************************************
void updateProgress(uint8_t _state, uint8_t colorValue);

// Debugging ******************************************************************************************
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

// Demo Mode ******************************************************************************************
struct tDemo{
  uint8_t demoIs;
  uint8_t demoTarget;
  bool demoUp : 1;
  bool isDemoMode :1;
  bool isDemoMode_Button :1;
  uint32_t lastDemoCalc;
} demo = {0,100,true,true,false,0};

void resetDemoValue(){
  rpm =0;
  clt =0.0f;
  batt = 0.0f;
  gear = 0;
}

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

// Input Mode ******************************************************************************************
volatile uint8_t displayMode = 0;
volatile bool pushButtonIsSet = true;

void ISR_Button(){
  static uint32_t lastPushTime = 0;
  uint32_t currentPushTime = millis();
  
  if(currentPushTime - lastPushTime >= BUTTON_BOUNCE_TIME){
    pushButtonIsSet = true;
    displayMode = (displayMode +1) % (DISPLAY_NUMBER_OF_SCREENS+1);
    demo.isDemoMode_Button = false;
  }
  lastPushTime = currentPushTime;
}

void initInput(void){
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),ISR_Button,FALLING);
}

// 7-Segment ******************************************************************************************
// see http://www.fakoo.de/siekoo.html for 7-Segment Alphabet
#include "TM1637Display.h" //7-Segment Library by avishorp

TM1637Display display(DISPLAY_CLK, DISPLAY_DIO);
uint32_t lastDisplayFlash;
bool displayShow;
const uint8_t display_blank[] = { 0x00, 0x00, 0x00, 0x00 };
const uint8_t display_umd[] =  { 0b00111110, 0b00110011, 0b00100111, 0b00111111 }; //UMD
const uint8_t display_fs19[] = { 0b01110001, 0b01101101, 0b00000110, 0b01101111 }; //FS19

const uint8_t screen[][4] ={
  { 0b01101101, 0b01111000, 0b01011100, 0b01111000 }, // Stat; must be on the first position!
  { 0b10000110, 0b01111001, 0b01010100, 0b01011110 }, // 1.End
  { 0b11011011, 0b01110111, 0b01011000, 0b01011000 }, // 2.Acc 
//{ 0b11001111, 0b01111111, 0b01111111, 0b01111111 }, // 3.888     
  { 0b01011110, 0b01111001, 0b01010101, 0b00111111 }  // dEMO; must be the last entry in this array!       
};

const uint8_t state[][4] ={
  { 0b01111100, 0b01011100, 0b01111000, 0b01111000 }, //batt -> Batterie Voltage
  { 0b00111101, 0b01111001, 0b01011100, 0b01010000 }, //GEar -> current Gear
  //{ 0b00111001, 0b00110000, 0b01111000, 0b00000000 }, //Clt -> Engine Temperature
  { 0b01111000, 0b01111001, 0b01010101, 0b01110011 }, //tEMP -> Engine Temperature      
};

void initDisplay(void){
    display.setBrightness(DISPLAY_BRIGHTNESS);
    display.setSegments(display_fs19);
    lastDisplayFlash = millis();
}

static uint8_t stateCount = 0;
static uint8_t lastTimeCount = 0;
static bool showState = true;
void refreshDisplay(){
  if(!pushButtonIsSet){
    switch(displayMode){ // the max. number of screens must be set in the "config.h"
      case(0): //different States
        if(lastTimeCount == 1) updateProgress(stateCount, (uint8_t) showState);
        switch (stateCount){
        case (0)://Batterie Voltage
          if (showState) display.setSegments(state[stateCount]);
          else{
            display.showNumberDecEx((int) (batt*10), 0b01000000, false, 3, 1);
            display.setSegments(display_blank,1,0);
          }
          break;
        case (1)://current Gear
          if (showState) display.setSegments(state[stateCount]);
          else{
            display.showNumberDec(gear, false, 1, 3);           
            display.setSegments(display_blank,3,0);
          }
          break;
        case (2)://Engine Temperature
          if (showState) display.setSegments(state[stateCount]);
          else{
            display.setSegments(display_blank,1,0);
            display.showNumberDecEx((int) (clt*10), 0b00100000, false, 4, 0);            
          }          
          break;
        }
        if(lastTimeCount == DISPLAY_DELAY_MULTIPLIER){
          lastTimeCount = 0;
          if(!showState) {stateCount=(stateCount+1)%DISPLAY_NUMBER_OF_STATES;}
          showState=!showState;
        }
        lastTimeCount++;
        
        break;    
      case(1): //Gear and Temperature -> endurance
        //display.setSegments(displayBlank, 1, 1);
        display.showNumberDecEx(gear, 0x80, false, 1, 0); //x.yyy -> x= Gear; y=Temperature
        display.showNumberDec(clt, false, 3, 1);        
        break;
      case(2): //Gear and RPM -> acceleration
        //display.setSegments(displayBlank, 1, 1);        
        display.showNumberDecEx(gear, 0x80, false, 1, 0); //x.yyy -> x= Gear; y=RPM
        display.showNumberDec((int) (rpm/100), false, 3, 1);
        break;
    }
  } else {
    static uint8_t localDelay = 0;
      if(localDelay == 0){
        localDelay = (uint8_t) (DISPLAY_DELAY_BY_SCREEN_CHANGE / DISPLAY_REFRESH_RATE);
        if(!demo.isDemoMode_Button) display.setSegments(screen[displayMode], 4, 0);
          else display.setSegments(screen[DISPLAY_NUMBER_OF_SCREENS], 4, 0);
      }     
      if(localDelay == 1) pushButtonIsSet = false; 
      localDelay--;
      //display.setSegments(displayBlank);
  }
}


// CAN ******************************************************************************************
#include "mcp_can.h" //CAN Library by Seeed-Studio
#include "ConvertCanData.h"

MCP_CAN CAN(CAN_SPI_CS_PIN);
tCAN_Data CanData; //CAN "Stack"

void MCP2515_ISR() {
  CanData.flagCanRecv = 1;
    if(demo.isDemoMode == 1){ //disable DemoMode add first CAN-Data recive and reset all demo values
      demo.isDemoMode = 0;
      resetDemoValue();
    }     
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


// Neopixel ******************************************************************************************
#include "Adafruit_NeoPixel.h" //WS2812b Library by Adafruit

Adafruit_NeoPixel neoPixels(NEOPIXEL_NUMBER_OF_LEDS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
uint32_t lastNeoFlash;
bool speedBarFlush = 0;

const uint32_t red = neoPixels.Color(255, 0, 0); // Red
const uint32_t green = neoPixels.Color( 0, 255, 0); // Green
const uint32_t yellow = neoPixels.Color( 255, 255, 0); // Yellow
const uint32_t blue = neoPixels.Color( 0, 0, 255); // Blue
const uint32_t orange = neoPixels.Color( 255, 50, 0); // UMD orange

void initNeopixel(void){
  neoPixels.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  neoPixels.setBrightness(NEOPIXEL_BRIGHTNESS); // Set BRIGHTNESS
  neoPixels.fill(orange);
  neoPixels.show(); 
  lastNeoFlash = millis();
}

const uint32_t* progressColor[] = {&yellow, &red};
void updateProgress(uint8_t _state, uint8_t colorValue){
    const uint8_t progress = (uint8_t)(NEOPIXEL_NUMBER_OF_LEDS / DISPLAY_NUMBER_OF_STATES);
    const uint8_t halfOfRest = (NEOPIXEL_NUMBER_OF_LEDS % DISPLAY_NUMBER_OF_STATES)/2;
    neoPixels.clear();
    for(uint8_t i=(stateCount*progress)+halfOfRest;i<((stateCount*progress)+progress+halfOfRest);i++){
      neoPixels.setPixelColor(NEOPIXEL_NUMBER_OF_LEDS-i-1, *(progressColor[colorValue]));
    }
    //delay(400);
    neoPixels.show();
}


void updateSpeedBar() {
  if(displayMode > 0){
    int speedLeds = NEOPIXEL_NUMBER_OF_LEDS * (rpm/(UMD_MAX_ENGINE_SPEED/100)) / 100;

    if(speedLeds < NEOPIXEL_NUMBER_OF_LEDS*0.69 || speedLeds > NEOPIXEL_NUMBER_OF_LEDS*0.85) {
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
      if(a < NEOPIXEL_NUMBER_OF_LEDS*0.23)
        neoPixels.setPixelColor(NEOPIXEL_NUMBER_OF_LEDS-1-a, blue);
      else if (a < NEOPIXEL_NUMBER_OF_LEDS*0.69) 
        neoPixels.setPixelColor(NEOPIXEL_NUMBER_OF_LEDS-1-a, green); // Set pixel 'c' to value 'color'
      else if (a < NEOPIXEL_NUMBER_OF_LEDS*0.85) 
        neoPixels.setPixelColor(NEOPIXEL_NUMBER_OF_LEDS-1-a, yellow); // Set pixel 'c' to value 'color'
      else
        neoPixels.setPixelColor(NEOPIXEL_NUMBER_OF_LEDS-1-a, red); // Set pixel 'c' to value 'color'
    }
    neoPixels.show();
    lastNeoFlash = millis();
  }
}

#endif
