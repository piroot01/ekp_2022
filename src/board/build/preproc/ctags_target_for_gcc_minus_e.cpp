# 1 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino"
//
// board.ino
//

# 6 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/board.ino" 2

char tmpChar;
bool bufferComplete = false;
int interval = 100;
unsigned long prevTime;
char* test = "111111,222222,333333,444444,555555,666666,777777,888888,999999x";
int i = 0;

_Serial mySerial;

void
setup()
{
    // Initialize serial communication.
    Serial.begin(115200, 0x06);
    if (Serial)
        Serial.print(mySerial.GetSerialReadyChar());
}

void
loop()
{

    // Check if the buffer is complete.
    if (bufferComplete) {
        while (i <= 100) {
            if (millis() - prevTime >= interval) {
                prevTime = millis();
                Serial.print(test);
                i++;
            }
        }
        bufferComplete = false;
    }
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
