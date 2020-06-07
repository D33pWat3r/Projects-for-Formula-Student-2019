#ifndef CONVERT_CAN_DATA_H
#define CONVERT_CAN_DATA_H

#include <stdint.h>

// CAN IDs
#define CAN_ID_RPM 1000
#define CAN_ID_SECONDS 1000
#define CAN_ID_WEATHER 1002
#define CAN_ID_BATTERY 1003
#define CAN_ID_THROTTLE 1003
#define CAN_ID_GEAR 1033
#define CAN_ID_FUEL_DATA 1052
#define CAN_ID_CANOUT 1052

struct tCAN_Data{
    bool flagCanRecv = false;
    uint8_t canLen = 0;
    uint8_t canBuf[8];
    uint16_t canId = 0;
};

void get_CAN_RPM(tCAN_Data* CAN_data, uint16_t* returnValue); //Engine RPM
void get_CAN_Sec(tCAN_Data* CAN_data, uint16_t* returnValue); //Seconds ECU has been on
void get_CAN_ClT(tCAN_Data* CAN_data, float* returnValue); //Coolant temperature CAN in degF saved in degC
void get_CAN_MAT(tCAN_Data* CAN_data, float* returnValue); //Manifold air temperature CAN in degF saved in degC
void get_CAN_MAP(tCAN_Data* CAN_data, float* returnValue); //Manifold air pressure
void get_CAN_Baro(tCAN_Data* CAN_data, float* returnValue); //Barometric pressure
void get_CAN_Batt(tCAN_Data* CAN_data, float* returnValue); //Battery voltage
void get_CAN_TPS(tCAN_Data* CAN_data, float* returnValue); //Throttle position
void get_CAN_Gear(tCAN_Data* CAN_data, uint8_t* returnValue); //Current gear selected
void get_CAN_FuelCons(tCAN_Data* CAN_data, uint16_t* returnValue); //Average fuel consumption
void get_CAN_FuelFlow(tCAN_Data* CAN_data, uint16_t* returnValue); //Average fuel flow
void get_CAN_CanOut(tCAN_Data* CAN_data, uint16_t* returnValue); //Return CanOut1 & CanOut2; Byte-Structure: HighByte->[CanOut2 | CanOut1]<-LowByte



#endif