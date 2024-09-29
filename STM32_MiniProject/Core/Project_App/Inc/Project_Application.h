/*
 * Project_Application.h
 *
 *  Created on: Sep 29, 2024
 *      Author: Sumedh Lele
 * BITS ID 2024HT01137
 */

#ifndef PROJECT_APP_INC_PROJECT_APPLICATION_H_
#define PROJECT_APP_INC_PROJECT_APPLICATION_H_

/* Includes begin */
#include <stdint.h>
/* Includes end */

// Following is the structure to store the Sensor 
typedef struct
{
    char* cSensorName;
    uint8_t u8SensorAddress;
    char* cSendMethod;
} sensorStruct;


// Following is the global sensor configuration
sensorStruct SENSOR_CONFIG[] =  
{
    {"Sensor 1", 0x10, "http"},
    {"Sensor 2", 0x11, "http"},
    {"Sensor 3", 0x12, "http"},
    {"Sensor 4", 0x13, "http"},
    {"Sensor 5", 0x14, "http"},
    {"Sensor 6", 0x15, "mqtt"},
    {"Sensor 7", 0x16, "mqtt"},
    {"Sensor 8", 0x17, "mqtt"},
};

#endif /* PROJECT_APP_INC_PROJECT_APPLICATION_H_ */
