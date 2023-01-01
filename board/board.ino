// Code for testing the communication initialization.

#define CR '\r'
#define FF '\f'

const char init_ = 'i';
unsigned long prevTime_ms;
const unsigned int period_ms = 10;
float randomNumber;

void setup() {
    Serial.begin(9600, SERIAL_8N1);
    randomSeed(analogRead(0));
    if (Serial) {
        Serial.print(init_);
        delay(100);
    }
}

void loop() {
    if (millis() - prevTime_ms >= period_ms) {
        prevTime_ms = millis();

        Serial.print(CR);
        Serial.print(micros() / 1000000.0, 10);

        randomNumber = random(1, 10) / 31.0;
        Serial.print(FF);
        Serial.print(randomNumber, 6);

        randomNumber = random(1, 10) / 31.0;
        Serial.print(FF);
        Serial.print(randomNumber, 6);

        randomNumber = random(1, 10) / 31.0;
        Serial.print(FF);
        Serial.print(randomNumber, 6);

        randomNumber = random(1, 10) / 31.0;
        Serial.print(FF);
        Serial.print(randomNumber, 6);

        randomNumber = random(1, 10) / 31.0;
        Serial.print(FF);
        Serial.print(randomNumber, 6);

        randomNumber = random(1, 10) / 31.0;
        Serial.print(FF);
        Serial.print(randomNumber, 6);
    }
}
