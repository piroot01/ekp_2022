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
#define SERIAL_INIT "i"

using namespace CppSerial;

int
main(int argc, char** argv)
{
    // Period of checking arduino activity.
    time_t updatePer = 100;

    // Message to write to serial port.
    char myMessage[2] = {'h', BUFFER_END};

    // Read buffer.
    std::string readBuffer;
    
    // String that stores path to selected port.
    std::string port;

    // Create object getOpt.
    GetOpt getOpt(argc, argv);
    
    // Load the port path.
    getOpt.Opt(port);
    
    Board myBoard;

    // Set the parameters for serial communication.
    SerialPort mySerial(port, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);

    // Set timeout.
    mySerial.SetTimeout(-1);
    
    // Open serial port.
    mySerial.Open();

    // Flush serial buffer
    mySerial.FlushSerialBuff();
    
    // Wait until the board is ready for communication.
    myBoard.WaitForSerialInit(mySerial, readBuffer);

    // Send my message.
    mySerial.Write(myMessage);

    // Read the answer.
    mySerial.Read(readBuffer);

    // Print readBuffer on screen.
    std::cout << readBuffer << std::endl;

    // Close serial port.
    mySerial.Close();

    return 0;
}
