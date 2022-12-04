#line 1 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/app.cpp"
//
// app.cpp
//

// system headers
#include <Arduino.h>

// user headers
# include "app.hpp"

_Serial::_Serial() {
    serialReady_ = defaultSerialReady_;
}
void _Serial::StoreChar(char &tmpChar) {
    readBuffer_ = tmpChar;
}

char& _Serial::GetStoredChar() {
    return readBuffer_;
}

void _Serial::Hello() {
    if (GetStoredChar() == 'h')
        Serial.print('h');
}
