//==================================================================
//  
//  File: Serial.hpp
//  Description: Definition of Serial class.
//  Author: Tomas Machacek
//  Date: 24 Dec 2022
//  Notes: N/A
//
//==================================================================

#ifndef SERIAL_H
#define SERIAL_H

// system headers
#include <string>
#include <asm/termbits.h>
#include <vector>

// user headers
#include "EnumClasses.hpp"

class _Serial {
public:
    
    // Default constructor
    _Serial();

    // Virtual destructor.
    virtual ~_Serial();

    void SetDevice(const std::string& device);

    // Method for setting the baud rate.
    void SetBaudRate(const speed_t& baudRate);

    // Method for setting number of data bits in one packet.
    void SetNumDataBits(const NumDataBits& numDataBits);

    // Method for setting the parity/
    void SetParity(const Parity& parity);

    // Method for setting the number of stop bits.
    void SetNumStopBits(const NumStopBits& numStopBits);

    // Method for setting the read timeout (in milliseconds)/blocking mode.
    void SetTimeout(const int32_t& timeout_ms);

    // Enables/disables echo.
    void SetEcho(bool& value);

    // Open the COM port for use.
    void Open();

    // Close the COM port.
    void Close();

    // Flush receiving buffer
    void FlushReceiverBuffer();

    // Flush transmitting buffer.
    void FlushTransmitterBuffer();

    // Flush both buffers.
    void FlushSerialBuffers();
    
    // Method for writing to UART bus.
    void Write(const std::string& data);

    // Method for reading from UART buffer (single byte).
    void Read(char& data);

    // Method that returns number of bytes stored in read buffer.
    int32_t Available();
private:

    // Method for configuration of the tty device as serial port.
    void ConfigureTermios();

    // It returns populated termios2 structure for the serial port pointed to by the file descriptor.
    termios2 GetTermios2();

    // Method for assigning the provided tty settings to the srial port pointed to by the file descriptor.
    void SetTermios2(termios2 tty);

    // Variable that stores the state of the serial port.
    State state_;

    // Path to the port.
    std::string device_;
    
    // Default serial port variables.
    speed_t baudRate_;
    NumDataBits numDataBits_;
    Parity parity_;
    NumStopBits numStopBits_;

    // The file descriptor for the open file. This gets written to when Open() is called.
    int fileDesc_;

    // Additional options for the serial port.
    bool echo_;
    int32_t timeout_ms_;

    // Default serial port timeout and read buffer size;
    static constexpr int32_t defaultTimeout_ms_ = -1;
    static constexpr unsigned char defaultReadBufferSize_B_ = 2;
};

#endif
