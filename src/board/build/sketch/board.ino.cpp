#include <Arduino.h>
#line 1 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
//
// board.ino
//

#define SERIAL_READY 'i'

char inputChar;
bool bufferComplete = false;
#line 9 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
void setup();
#line 20 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
void loop();
#line 33 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
void serialEvent();
#line 9 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"

void
setup() 
{
    // Initialize serial communication.
    Serial.begin(9600, SERIAL_8N1);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    if (Serial)
        Serial.print(SERIAL_READY);
}

void
loop() 
{
    // Check if the buffer is complete.
    if (bufferComplete) {

        // Printed only if the correct char is received.
        if (inputChar == 'h') Serial.print('a');

        bufferComplete = false;
    }
}

void
serialEvent()
{
    while (Serial.available()) {
        
        // Store one byte from buffer.
        char tmpChar = (char)Serial.read();

        if (tmpChar == '\r') bufferComplete = true;
        else inputChar = tmpChar;
    }
}

