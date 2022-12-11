//
// main.cpp
//

// system headers
#include <iostream>
#include <chrono>
#include <ratio>
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

    std::string nums[100];

    Board myBoard;

    myBoard.Open();

    myBoard.serial.Write(myMessage);

    int i = 0;
    while (true) {
        std::cout << myBoard.serial.Available() << '\n';
        if (myBoard.serial.Available() >= 10)
            myBoard.serial.Read(readBuffer);
        std::this_thread::sleep_for(std::chrono::microseconds(10000));
    }

    // Close serial port.
    myBoard.serial.Close();

    return 0;
}
