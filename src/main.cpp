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
main(int argc, char** argv)
{
    // Message to write to serial port.
    char myMessage[2] = {'h', BUFFER_END};

    // Read buffer.
    std::string readBuffer;

    Board myBoard;

    myBoard.Open();

    // Send my message.
    myBoard.serial.Write(myMessage);

    // Read the answer.
    myBoard.serial.Read(readBuffer);

    // Print readBuffer on screen.
    std::cout << readBuffer << std::endl;

    // Close serial port.
    myBoard.serial.Close();

    return 0;
}
