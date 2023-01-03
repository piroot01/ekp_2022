//==================================================================
//  
//  File: board.ino
//  Description: Code for the board.
//  Author: Tomas Machacek
//  Date: 2 Jan 2023
//  Notes: N/A
//
//==================================================================

// sustem headers
#include <MPU9250_WE.h>
#include <Wire.h>

// Adress of the sensor.
#define MPU9240_ADDRESS 0x68

// Terminal symbols.
#define CR '\r'
#define FF '\f'

// Init message.
#define __INIT__ 'i'

// Create new imu.
MPU9250_WE imu = MPU9250_WE(MPU9240_ADDRESS);

// Timing variables.
unsigned long prevTime_ms = 0;
unsigned long initTime_ms;
const unsigned int period_ms = 10;
bool first = true;

// Setup loop.
void setup() {
    
    // Initialize Wire. 
    Wire.begin();

    // Auto offset the sensor.
    imu.autoOffsets();

    // Set parameters for the imu.
    imu.setSampleRateDivider(4);
    imu.setGyrRange(MPU9250_GYRO_RANGE_250);
    imu.setAccRange(MPU9250_ACC_RANGE_2G);

    // Start serial communication.
    Serial.begin(115200, SERIAL_8N1);

    // If the serial initialization was successfull than send __INIT__.
    if (Serial) {
        Serial.print(__INIT__);
        delay(100);
    }
}

void loop() {

    // Every period_ms send imu data.
    if (micros() - prevTime_ms >= period_ms * 1000) {
        prevTime_ms = micros();
        PrintData();
    }
}

void PrintData() {
    
    // Get values from imu.
    xyzFloat acc = imu.getGValues();
    xyzFloat gyr = imu.getGyrValues();
    
    // Register time slip.
    if (first) {
        first = false;
        initTime_ms = micros();
    }

    // Print message containing the values from accelerometer and gyroscope.
    Serial.print(FF);
    Serial.print(micros() - initTime_ms);
    Serial.print(CR);
    Serial.print(acc.x, 6);
    Serial.print(CR);
    Serial.print(acc.y, 6);
    Serial.print(CR);
    Serial.print(acc.z, 6);
    Serial.print(CR);
    Serial.print(gyr.x, 6);
    Serial.print(CR);
    Serial.print(gyr.y, 6);
    Serial.print(CR);
    Serial.print(gyr.z, 6);
}
