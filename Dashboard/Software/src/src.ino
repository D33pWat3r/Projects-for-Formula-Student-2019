#include "Dashboard.h"
#include "ConvertCanData.h"

void printData();
void printCAN();

void setup() {
  initDebugging(115200); //Starte Seriellen Port für debugging Ausgaben
  initDisplay(); //Start Display
  initNeopixel(); //Start NeoPixel
  initCAN(); // Start CAN-BUS
  initInput(); //Set Button to Input
}

void loop() {
  //Read CAN if new incoming Datas
  if(CanData.flagCanRecv) readCAN(); 
  
  //Refreshing Display
  if(millis() - lastDisplayFlash > DISPLAY_REFRESH_RATE) {
    lastDisplayFlash = millis();
    refreshDisplay();
  }

  //Refreshing LED Band
  if(millis() - lastNeoFlash > NEOPIXEL_REFRESH_RATE) {
    int dec = rpm/(UMD_MAX_ENGINE_SPEED/100);
    updateSpeedBar(dec);
  }

  //Refreshing and Recalc Demovalues
  if((millis() - demo.lastDemoCalc > DEMO_CALC_SPEED) && (demo.isDemoMode || demo.isDemoMode_Button) ) {
    demoCalcSpeed();
  }
}


void readCAN() {
  CanData.flagCanRecv = false;
  while (CAN_MSGAVAIL == CAN.checkReceive()) 
  {
    // read data,  canLen: data length, canBuf: data buf
    CAN.readMsgBuf(&(CanData.canLen), CanData.canBuf);
    CanData.canId = CAN.getCanId();

    printCAN(); // Debug only

    if(CanData.canId == CAN_ID_RPM) get_CAN_RPM(&CanData, &rpm);
    if(CanData.canId == CAN_ID_SECONDS) get_CAN_Sec(&CanData, &seconds);
    if(CanData.canId == CAN_ID_WEATHER){
      get_CAN_ClT(&CanData, &clt);
      get_CAN_MAT(&CanData, &mat);
      get_CAN_MAP(&CanData, &map1);
      get_CAN_Baro(&CanData, &baro);
    };
    if(CanData.canId == CAN_ID_BATTERY) get_CAN_Batt(&CanData, &batt);
    if(CanData.canId == CAN_ID_RPM) get_CAN_RPM(&CanData, &rpm);
    if(CanData.canId == CAN_ID_THROTTLE) get_CAN_TPS(&CanData, &tps);
    if(CanData.canId == CAN_ID_GEAR) get_CAN_Gear(&CanData, &gear);
    if(CanData.canId == CAN_ID_FUEL_DATA) {
      get_CAN_FuelCons(&CanData, &fuelcons);
      get_CAN_FuelFlow(&CanData, &fuelflow);
      };

      printData(); // Debug only
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
  DEBUG_PRINT(CanData.canId);DEBUG_PRINT("\t");
  
  // print the data
  for(int i = 0; i<CanData.canLen; i++)
  {
      DEBUG_PRINT(CanData.canBuf[i]);DEBUG_PRINT("\t");
  }
  DEBUG_PRINTLN();
}
