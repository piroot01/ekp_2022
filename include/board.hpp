//
// The board header.
//

#ifndef BOARD_H
#define BOARD_H

// system headers
#include <string>

// user headers
#include "../lib/include/cpp_serial.hpp"

class Board {
public:

    // Default constructor.
    Board();

    // Constructor with update period selection.
    Board(time_t& updatePer);

    // Wait for board to initialize serial communication.
    void WaitForSerialInit(CppSerial::SerialPort& serial, std::string& readBuffer);

    // Set custom update period of checking if board is ready.
    void SetUpdatePer(time_t& updatePer);
private:

    // Default update period.
    const time_t defaultUpdatePer_ = 50;

    time_t updatePer_;

    struct Bytes {
        std::string serialInit = "i";
    };
    
    struct Bytes bytes_;
};

#endif
