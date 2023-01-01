// Code for testing the communication initialization.

#define CR '\r'

const char init_ = 'i';
unsigned long prevTime_ms;
const unsigned int period_ms = 1;
bool readyToSend = false;
float count;

void setup() {
    Serial.begin(115200, SERIAL_8N1);
    if (Serial) {
        Serial.print(init_);
        count = 3.1415926585;
        delay(100);

    }
}

void loop() {
    if (millis() - prevTime_ms >= period_ms) {
        prevTime_ms = millis();
        Serial.print(count, 5);
        Serial.print(CR);
        count += 2.7182;
    }
}
