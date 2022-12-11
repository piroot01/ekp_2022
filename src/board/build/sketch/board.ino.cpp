#include <Arduino.h>
#line 1 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
//
// board.ino
//

#include "app.hpp"

char tmpChar;
bool bufferComplete = false;
int interval = 10000;
unsigned long prevTime;
char* test = "111111,222222,333333,444444,555555,666666,777777,888888,999999x";
int i = 0;

_Serial mySerial;
#line 15 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
void setup();
#line 24 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
void loop();
#line 48 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
void serialEvent();
#line 15 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"

void
setup() 
{
    // Initialize serial communication.
    Serial.begin(115200, SERIAL_8N1);
    if (Serial)
        Serial.print(mySerial.GetSerialReadyChar());
}

void
loop() 
{
    if (i == 0 && bufferComplete) {
        //Serial.print('3');
        i++;
    }

    // Check if the buffer is complete.
    /*
    if (bufferComplete) {
        while (i <= 100) {
            if (micros() - prevTime >= interval) {
                prevTime = micros();
                Serial.print(3);
                i++;
            }
            if (i == 100)
                bufferComplete = false;
        }
    }
    */
}

void
serialEvent()
{
    while (Serial.available()) {
        
        // Store one byte from buffer.
        tmpChar = (char)Serial.read();

        if (tmpChar == '\r') 
            bufferComplete = true;
        else 
            mySerial.StoreChar(tmpChar);
    }
}

