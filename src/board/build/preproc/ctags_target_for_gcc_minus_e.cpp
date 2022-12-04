# 1 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
//
// board.ino
//

# 6 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino" 2

char tmpChar;
bool bufferComplete = false;

_Serial mySerial;

void
setup()
{
    // Initialize serial communication.
    Serial.begin(115200, 0x06);
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
