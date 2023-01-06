//==================================================================
//  
//  File: board.ino
//  Description: Code for the board.
//  Author: Tomas Machacek
//  Date: 2 Jan 2023
//  Notes: Heavily based on 
//         https://github.com/wollewald/MPU9250_WE/
//         blob/main/examples/MPU6500_all_data/MPU6500_all_data.ino
//
//==================================================================

// sustem headers
#include <Wire.h>
#include <MPU6500_WE.h>

// Adress of the sensor.
#define MPU9250_ADDRESS 0x68

// Terminal symbols.
#define CR '\r'
#define FF '\f'

// Creating new instance of MPU6500_WE class.
MPU6500_WE imu = MPU6500_WE(MPU9250_ADDRESS);

// Init message, use with arduino boards.
//#define __INIT__ 'i'

unsigned long prevTime_ms = 0;

// Logging frequency set to 400Hz.
const unsigned int period_us = 1000000 / 400;

// Variables for storing accelerometer and gyroscope data.
xyzFloat acc;
xyzFloat gyr;

void setup() {

    // Initialize Wire. 
    Wire.begin();

    // Start serial communication.
    Serial.begin(460800, SERIAL_8N1);

    // Use for arduino boards.
//    if(Serial) {
//        Serial.print(__INIT__);
//        delay(100);
//    }

    // Initialize imu.
    imu.init();

    // Store actual offset of the accelerometer and gyroscope.
    imu.autoOffsets();

    // Enable low pass filter for gyroscope.
    imu.enableGyrDLPF();

    // Set the filter to max.
    imu.setGyrDLPF(MPU6500_DLPF_6);

    // Sample rate divider to 0.
    imu.setSampleRateDivider(0);

    // Set the gyroscope range to 250 deg/s.
    imu.setGyrRange(MPU6500_GYRO_RANGE_250);

    // Enable low pass filter for accelerometer.
    imu.enableAccDLPF(true);

    // Set the filter to max.
    imu.setAccDLPF(MPU6500_DLPF_6);

    // Set the accelerometer range to 4g.
    imu.setAccRange(MPU6500_ACC_RANGE_4G);
    delay(200);
}

void loop() {

    // Every period_ms send imu data.
    if (micros() - prevTime_ms >= period_us) {
        prevTime_ms = micros();

        // Get data from sensor.
        acc = imu.getGValues();
        gyr = imu.getGyrValues();

        // Send the data.
        SendData();
    }
}

// Function for sending formatted dato to serial.
// It sends timestamp along with accelerometer and gyroscope data.
void SendData() {
    Serial.print(FF);
    Serial.print(micros());
    Serial.print(CR);
    Serial.print(acc.x);
    Serial.print(CR);
    Serial.print(acc.y);
    Serial.print(CR);
    Serial.print(acc.z);
    Serial.print(CR);
    Serial.print(gyr.x);
    Serial.print(CR);
    Serial.print(gyr.y);
    Serial.print(CR);
    Serial.print(gyr.z);
}
