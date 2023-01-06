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
#include <Wire.h>

// Adress of the sensor.
#define MPU9250_ADDRESS 0x68

// Terminal symbols.
#define CR '\r'
#define FF '\f'

#define GYRO_FULL_SCALE_250_DPS 0x00 
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18
 
#define ACC_FULL_SCALE_2_G 0x00 
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

// Init message, use with arduino boards.
//#define __INIT__ 'i'

// Function for reading Nbytes from imu.
void Read(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {

    // Set register address
    Wire.beginTransmission(Address);
    Wire.write(Register);
    Wire.endTransmission();

    // Read Nbytes
    Wire.requestFrom(Address, Nbytes); 
    uint8_t index=0;
    while (Wire.available())
        Data[index++] = Wire.read();
}

// Function for write a byto to register.
void WriteByte(uint8_t Address, uint8_t Register, uint8_t Data) {

    // Set register address
    Wire.beginTransmission(Address);
    Wire.write(Register);
    Wire.write(Data);
    Wire.endTransmission();
}

// Timing variables.
unsigned long prevTime_ms = 0;
const unsigned int period_us = 5000;

// Setup loop.
void setup() {

    // Initialize Wire. 
    Wire.begin();

    // Start serial communication.
    Serial.begin(115200, SERIAL_8N1);

    // Use for arduino boards.
//    if(Serial) {
//        Serial.print(__INIT__);
//        delay(100);
//    }

    WriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_250_DPS);
    WriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_2_G);
}

void loop() {

    // Every period_ms send imu data.
    if (micros() - prevTime_ms >= period_us) {
        prevTime_ms = micros();

        // Read accelerometer and gyroscope data.
        uint8_t buffer[14];
        Read(MPU9250_ADDRESS, 0x3B, 14, buffer);

        // Create 16 bits values from 8 bits data.
        int16_t ax = -(buffer[0] << 8 | buffer[1]);
        int16_t ay = -(buffer[2] << 8 | buffer[3]);
        int16_t az = buffer[4] << 8 | buffer[5];
        int16_t gx = -(buffer[8]<<8 | buffer[9]);
        int16_t gy = -(buffer[10]<<8 | buffer[11]);
        int16_t gz = buffer[12]<<8 | buffer[13];

        // Send the data.
        Serial.print(FF);
        Serial.print(micros());
        Serial.print(CR);
        Serial.print(ax, DEC);
        Serial.print(CR);
        Serial.print(ay, DEC);
        Serial.print(CR);
        Serial.print(az, DEC);
        Serial.print(CR);
        Serial.print(gx, DEC);
        Serial.print(CR);
        Serial.print(gy, DEC);
        Serial.print(CR);
        Serial.print(gz, DEC);
    }
}
