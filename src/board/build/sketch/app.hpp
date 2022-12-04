#line 1 "/home/tomas/Documents/tomas/git/ekp_2022/src/board/app.hpp"
//
// app.hpp
//

#ifndef APP_H
#define APP_H

// system headers
#include <Arduino.h>

class _Serial {
public:
    _Serial();
    
    static char GetSerialReadyChar() {
        return defaultSerialReady_;
    }

    void StoreChar(char& tmpChar);

    char& GetStoredChar();

    void Hello();

private:
    char serialReady_;

    static const char defaultSerialReady_ = 'i';

    char readBuffer_;
};

#endif
