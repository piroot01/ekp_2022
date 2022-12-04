#include <Arduino.h>
#line 1 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
//
// board.ino
//

#include "app.hpp"

char tmpChar;
bool bufferComplete = false;

_Serial mySerial;
#line 11 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
void setup();
#line 20 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
void loop();
#line 33 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
void serialEvent();
#line 11 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"

void
setup() 
{
    // Initialize serial communication.
    Serial.begin(115200, SERIAL_8N1);
    if (Serial)
        Serial.print((char)mySerial.GetSerialReadyChar());
}

void
loop() 
{
    // Check if the buffer is complete.
    if (bufferComplete) {

        // Printed only if the correct char is received.
        mySerial.Hello();

        bufferComplete = false;
    }
}

void
serialEvent()
{
    while (Serial.available()) {
        
        // Store one byte from buffer.
        tmpChar = (char)Serial.read();

        if (tmpChar == '\r') bufferComplete = true;
        else mySerial.StoreChar(tmpChar);
    }
}

