//
// main.cpp
//

// system headers
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

// user headers
#include "../lib/include/cpp_serial.hpp"
#include "../include/get_opt.hpp"
#include "../include/board.hpp"

#define BUFFER_END 0x0D

using namespace CppSerial;

int
main()
{
    // Message to write to serial port.
    char myMessage[2] = {'h', BUFFER_END};

    // Read buffer.
    std::string readBuffer;

    Board myBoard;

    myBoard.Open();

    myBoard.serial.Write(myMessage);

    myBoard.serial.Read(readBuffer);
    
    double pi = std::stod(readBuffer);

    std::cout << readBuffer << std::endl;

    // Close serial port.
    myBoard.serial.Close();

    return 0;
}
