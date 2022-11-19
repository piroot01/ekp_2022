//
// board.ino
//

#define SERIAL_READY 'i'

char inputChar;
bool bufferComplete = false;

void
setup() 
{
    // Initialize serial communication.
    Serial.begin(115200, SERIAL_8N1);
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
