//
// main.cpp
//

// system headers
#include <chrono>
#include <thread>
#include <string>

// user headers
#include "../lib/include/cpp_serial.hpp"

#define WAIT_FOR_SERIAL_INIT 2000

using namespace CppSerial;

int
main()
{
    char myMessage[2] = {'i', '\r'};
    std::string readBuffer;

    // Set the parameters for serial communication.
    SerialPort mySerial("/dev/ttyACM0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
    
    // Set timeout.
    mySerial.SetTimeout(-1);
    
    // Open serial port.
    mySerial.Open();

    // Wait for 2 seconds to establish serial communication.
    std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_FOR_SERIAL_INIT));
    
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
