#include "ConvertCanData.h"

void get_CAN_RPM(tCAN_Data* CAN_data, uint16_t* returnValue){
    *returnValue = ((*CAN_data).canBuf[6]<<8) + (*CAN_data).canBuf[7];
    return;
}

void get_CAN_Sec(tCAN_Data* CAN_data, uint16_t* returnValue){
    *returnValue = ((*CAN_data).canBuf[0]<<8) + (*CAN_data).canBuf[1];    
}

void get_CAN_ClT(tCAN_Data* CAN_data, float* returnValue){
    *returnValue = (((*CAN_data).canBuf[6]<<8) + (*CAN_data).canBuf[7]) * 0.1;
    *returnValue = (*returnValue - 32) * 5 /9; //convert Fahrenheit to degree
    return;
}

void get_CAN_MAT(tCAN_Data* CAN_data, float* returnValue){
    *returnValue = (((*CAN_data).canBuf[4]<<8) + (*CAN_data).canBuf[5]) * 0.1;
    *returnValue = (*returnValue - 32) * 5 /9; //convert Fahrenheit to degree
    return;
}

void get_CAN_MAP(tCAN_Data* CAN_data, float* returnValue){
    *returnValue = (((*CAN_data).canBuf[2]<<8) + (*CAN_data).canBuf[3]) * 0.1;
    return;
}

void get_CAN_Baro(tCAN_Data* CAN_data, float* returnValue){
    *returnValue = (((*CAN_data).canBuf[0]<<8) + (*CAN_data).canBuf[1]) * 0.1;
    return;
}

void get_CAN_Batt(tCAN_Data* CAN_data, float* returnValue){
    *returnValue = (((*CAN_data).canBuf[2]<<8) + (*CAN_data).canBuf[3]) * 0.1;
    return;
}

void get_CAN_TPS(tCAN_Data* CAN_data, float* returnValue){
    *returnValue = (((*CAN_data).canBuf[0]<<8) + (*CAN_data).canBuf[1]) * 0.1;
    return;
}    

void get_CAN_Gear(tCAN_Data* CAN_data, uint8_t* returnValue){
    *returnValue = (*CAN_data).canBuf[6];
    return;
} 

void get_CAN_FuelCons(tCAN_Data* CAN_data, uint16_t* returnValue){
    *returnValue = ((*CAN_data).canBuf[6]<<8) + (*CAN_data).canBuf[7];
    return;
}

void get_CAN_FuelFlow(tCAN_Data* CAN_data, uint16_t* returnValue){
    *returnValue = ((*CAN_data).canBuf[4]<<8) + (*CAN_data).canBuf[5];
    return;
}
void get_CAN_CanOut(tCAN_Data* CAN_data, uint16_t* returnValue){
    *returnValue = ((*CAN_data).canBuf[4]<<8) + (*CAN_data).canBuf[5]; //the right Bytes!!!!!!????
    return;
} 