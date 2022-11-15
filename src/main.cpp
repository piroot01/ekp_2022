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

#define BUFFER_END 0x0D
#define SERIAL_INIT "i"

using namespace CppSerial;

// Check the read buffer in some period.
void
wait_for_board(SerialPort& Serial, std::string& buffer, time_t& sleep)
{
    while (1) {
        Serial.Read(buffer);
        if (buffer.compare(SERIAL_INIT) == 0)
            break;
        else
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    }
}

int
main(int argc, char** argv)
{
    // Period of checking arduino activity.
    time_t initPer = 100;

    // Message to write to serial port.
    char myMessage[2] = {'h', BUFFER_END};

    // Read buffer.
    std::string readBuffer;

    GetOpt getOpt(argc, argv);

getOpt.Opt()

    // Set the parameters for serial communication.
    SerialPort mySerial("/dev/ttyACM0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);

    // Set timeout.
    mySerial.SetTimeout(-1);

    // Open serial port.
    mySerial.Open();

    // Wait until the board is ready for communication.
    wait_for_board(mySerial, readBuffer, initPer);

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
