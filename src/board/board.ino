//
// board.ino
//

#include "app.hpp"

char tmpChar;
bool bufferComplete = false;

_Serial mySerial;

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
