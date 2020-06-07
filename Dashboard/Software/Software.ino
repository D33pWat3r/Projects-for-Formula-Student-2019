#include <SPI.h>
#include "mcp_can.h"
#include <Arduino.h>
#include <TM1637Display.h>
#include <Adafruit_NeoPixel.h>

#define DEBUG

////////////////// Motor Werte //////////////////
#define UMD_MAX_ENGINE_SPEED 13000

////////////////// CAN-BUS Header //////////////////
const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN);

unsigned char flagCanRecv = 0;
unsigned char canLen = 0;
unsigned char canBuf[8];
unsigned int canId = 0;

unsigned int rpm = 0;     //Engine RPM
unsigned int seconds = 0; //Seconds ECU has been on

double clt; //Coolant temperature CAN in degF saved in degC
double mat; //Manifold air temperature CAN in degF saved in degC
double map1; //Manifold air pressure";
double baro; //Barometric pressure";

double batt; //Battery voltage";
double tps; //Throttle position";

int gear; //Current gear selected

unsigned int fuelcons; //Average fuel consumption";
unsigned int fuelflow; //Average fuel flow";

////////////////// Display Header //////////////////
const int pinCLK = A5;
const int pinDIO = A4;

TM1637Display display(pinCLK, pinDIO);

unsigned long lastDisplayFlash;
bool displayShow;
const uint8_t displayBlank[] = { 0x00, 0x00, 0x00, 0x00 };

////////////////// Neo-Pixel Header //////////////////
const int pinNEO = 4;
const int numNeoPixels = 32;
const int pixelFormat = NEO_GRB + NEO_KHZ800;

Adafruit_NeoPixel neoPixels(numNeoPixels, pinNEO, pixelFormat);

unsigned long lastNeoFlash;
bool speedBarFlush = 0;

////////////////// DemoMode Header //////////////////
int demoIs = 0;
int demoTarget = 100;
bool demoUp = 1;
bool isDemoMode = 1;
unsigned long lastDemoCalc;


void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  #define DEBUG_PRINT(x)    Serial.print (x)
  #define DEBUG_PRINT2(x,y) Serial.print (x,y)
  #define DEBUG_PRINTLN(x)  Serial.println (x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINT2(x,y)
  #define DEBUG_PRINTLN(x)
#endif

// Start Display
  uint8_t umd[] = { 0b00111110, 0b00110011, 0b00100111, 0b00111111 };
  display.setBrightness(0x0f);
  display.setSegments(umd);
  lastDisplayFlash = millis();
  
// Start NeoPixel
  neoPixels.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  neoPixels.show();            // Turn OFF all pixels ASAP
  neoPixels.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  lastNeoFlash = millis();

// Start CAN-BUS
  while (CAN_OK != CAN.begin(CAN_500KBPS, MCP_16MHz))              // init can bus : baudrate = 500k; 16MHz
  {
        DEBUG_PRINTLN("CAN BUS Shield init fail");
        DEBUG_PRINTLN(" Init CAN BUS Shield again");
        delay(100);
    }
    DEBUG_PRINTLN("CAN BUS Shield init ok!");
    attachInterrupt(0, MCP2515_ISR, FALLING);
    
}

void MCP2515_ISR() {
    flagCanRecv = 1;
    isDemoMode = 0;                 //disable DemoMode add first CAN-Data recive.
}

void loop() {
  if(flagCanRecv) 
  {
    flagCanRecv = 0;
    readCAN();
  }
  
  if(lastDisplayFlash + 500 < millis()) {
    lastDisplayFlash = millis();
    int dec = rpm/100;
    display.setSegments(displayBlank, 1, 1);
    display.showNumberDec(dec, false, 3, 1);
    display.showNumberDec(gear, true, 1, 0);
    displayShow = 1;
    
  } else if(lastDisplayFlash + 400 < millis()) {
    if(clt > 80 && displayShow == 1) {
      display.setSegments(displayBlank);
      displayShow = 0;
    }
  }

  if(lastNeoFlash + 20 < millis()) {
    int dec = rpm/(UMD_MAX_ENGINE_SPEED/100);
    updateSpeedBar(dec);
  }
  if(isDemoMode && lastDemoCalc + 20 < millis()) {
    demoCalcSpeed();
  }
}

void demoCalcSpeed() {
  if(demoUp) {
    demoIs++;
    
    if(demoIs == demoTarget) {
      demoTarget = random(0, demoIs - 5);
      demoUp = 0;                   //fallende Drehzahl
      clt = random(60, 100);
    }

  } else {  
    demoIs--;
    
    if(demoIs == demoTarget) {
      demoTarget = random(demoIs + 5, 100);
      demoUp = 1;                   //steigende Drehzahl
      gear = random(gear-1, gear+2);
      if(gear < 0)
        gear = 0;
        
      if(gear > 6)
        gear = 6;
    }
  }

  rpm = UMD_MAX_ENGINE_SPEED / 100 * demoIs ;
  lastDemoCalc = millis();
}

void updateSpeedBar(int percent) {
  const uint32_t red = neoPixels.Color(255, 0, 0); // Red
  const uint32_t green = neoPixels.Color( 0, 255, 0); // Green
  const uint32_t yellow = neoPixels.Color( 255, 255, 0); // Blue
  const uint32_t blue = neoPixels.Color( 0, 0, 255); // Blue
  
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

void readCAN() {
  while (CAN_MSGAVAIL == CAN.checkReceive()) 
  {
    // read data,  canLen: data length, canBuf: data buf
    CAN.readMsgBuf(&canLen, canBuf);
    canId = CAN.getCanId();

//    Debug only
    printCAN();

    if(canId == 1000) {
      rpm = canBuf[6]*256 + canBuf[7];
      seconds = canBuf[0]*256 + canBuf[1];

//      Debug only
      printData();
      
    } else if(canId == 1002) {
      clt = canBuf[6] * 14.22222 + canBuf[7] * 0.05555 - 17.77777; //CAN in degF saved in degC
      mat = canBuf[4] * 14.22222 + canBuf[5] * 0.05555 - 17.77777; //CAN in degF saved in degC
      map1 = canBuf[2] * 25.6 + canBuf[3] * 0.1;
      baro = canBuf[0] * 25.6 + canBuf[1] * 0.1;
      
    } else if(canId == 1003) {
      batt = canBuf[2] * 25.6 + canBuf[3] * 0.1;
      tps = canBuf[0] * 25.6 + canBuf[1] * 0.1;
      
    } else if(canId == 1033) {
      gear = canBuf[6];
      
    } else if(canId == 1052) {
      fuelcons = canBuf[6] * 256 + canBuf[7];
      fuelflow = canBuf[4] * 256 + canBuf[5];
    }
  }
}

void printData() {
  DEBUG_PRINT(rpm);DEBUG_PRINT(" rpm\t");
  DEBUG_PRINT(seconds);DEBUG_PRINT(" s\t");

  DEBUG_PRINT(clt);DEBUG_PRINT(" °C\t");
  DEBUG_PRINT(mat);DEBUG_PRINT(" °C\t");
  DEBUG_PRINT(map1);DEBUG_PRINT(" kpa\t");
  DEBUG_PRINT(baro);DEBUG_PRINT(" kpa\t");

  DEBUG_PRINT(batt);DEBUG_PRINT(" V\t");
  DEBUG_PRINT(tps);DEBUG_PRINT(" %\t");

  DEBUG_PRINT(gear);DEBUG_PRINT(" \t");
  
  DEBUG_PRINT2(fuelcons, DEC);DEBUG_PRINT(" l/km\t");
  DEBUG_PRINT2(fuelflow, DEC);DEBUG_PRINT(" cc/min\t");

  DEBUG_PRINTLN();
}

void printCAN() {
  DEBUG_PRINT(canId);DEBUG_PRINT("\t");
  
  // print the data
  for(int i = 0; i<canLen; i++)
  {
      DEBUG_PRINT(canBuf[i]);DEBUG_PRINT("\t");
  }
  DEBUG_PRINTLN();
}
