# 1 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
//
// board.ino
//

char inputChar;
bool bufferComplete = false;

void
setup()
{
    // Initialize serial communication.
    Serial.begin(9600);
}

void
loop()
{
    // Check if the buffer is complete.
    if (bufferComplete) {

        // Printed only if the correct char is received.
        if (inputChar == 'i') Serial.print('a');

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
