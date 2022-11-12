#ifndef CPP_SERIAL_H
#define CPP_SERIAL_H

// System headers
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <asm/ioctl.h>
#include <asm/termbits.h>

// User headers

#include "exception.h"

namespace CppSerial {

    // STANDARD represents all the standards baud rates as provided by UNIX, CUSTOM represents a baud rate defined by arbitrary integer.

    enum class BaudRateType {
        STANDARD,
        CUSTOM,
    };

    enum class BaudRate {
        
    };
}

#endif
