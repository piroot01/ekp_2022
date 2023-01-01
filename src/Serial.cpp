//==================================================================
//  
//  File: Serial.cpp
//  Description: _Serial class
//  Author: Tomas Machacek
//  Date: 25 Dec 2022
//  Notes: N/A
//
//==================================================================

// system headers
#include <asm/termbits.h>
#include <sys/ioctl.h>
#include <asm/ioctls.h>
#include <fcntl.h>
#include <unistd.h>

// user headers
#include "Serial.hpp"
#include "Exception.hpp"
#include "EnumClasses.hpp"

_Serial::_Serial() {
    echo_ = false;
    timeout_ms_ = defaultTimeout_ms_;
    state_ = State::CLOSED;
}

_Serial::~_Serial() {
    try {
        Close();
    } catch (...) {}
}

void _Serial::SetDevice(const std::string& device) {
    device_ = device;
    if (state_ == State::OPEN)
        ConfigureTermios();
}

void _Serial::SetBaudRate(const speed_t& baudRate) {
    baudRate_ = baudRate;
    if (state_ == State::OPEN)
        ConfigureTermios();
}

void _Serial::SetNumDataBits(const NumDataBits& numDataBits) {
    numDataBits_ = numDataBits;
    if(state_ == State::OPEN)
        ConfigureTermios();
}

void _Serial::SetParity(const Parity& parity) {
    parity_ = parity;
    if(state_ == State::OPEN)
        ConfigureTermios();
}

void _Serial::SetNumStopBits(const NumStopBits& numStopBits) {
    numStopBits_ = numStopBits;
    if(state_ == State::OPEN)
        ConfigureTermios();
}

void _Serial::SetEcho(bool& value) {
    echo_ = value;
    ConfigureTermios();
}

void _Serial::SetTimeout(const int32_t &timeout_ms) {

    // Check if the provided timeout is valid.
    if (timeout_ms < -1 || timeout_ms > 25500)
        THROW_EXCEPT("Provided timeout is invalid.");
    
    // Check if the port is opened.
    if (state_ == State::OPEN)
        THROW_EXCEPT("Called while the port is opened");

    timeout_ms_ = timeout_ms;
}

void _Serial::Open() {
    
    // Check if any device was configured.
    if (device_.empty())
        THROW_EXCEPT("Attempted to open file when the file path has not been assigned to.");

    // Attempt to open a file.
    fileDesc_ = open(device_.c_str(), O_RDWR);

    // Check if the opening was successful.
    if (fileDesc_ == -1)
        THROW_EXCEPT("Could not open device " + device_ + ".");
    
    // Configure the tty device as serial port.
    ConfigureTermios();
    state_ = State::OPEN;
}

void _Serial::ConfigureTermios() {
    termios2 tty = GetTermios2();

    // Set the number of data bits.
    tty.c_cflag &= ~CSIZE;
    switch (numDataBits_) {
        case NumDataBits::FIVE:
            tty.c_cflag |= CS5;
            break;
        case NumDataBits::SIX:
            tty.c_cflag |= CS6;
            break;
        case NumDataBits::SEVEN:
            tty.c_cflag |= CS7;
            break;
        case NumDataBits::EIGHT:
                tty.c_cflag |= CS8;
        break;
        default:
            THROW_EXCEPT("numDataBits_ value not supported!");
    }

    // Set the parity.
    switch (parity_) {
        case Parity::NONE:
            tty.c_cflag &= ~PARENB;
            break;
        case Parity::EVEN:	
            tty.c_cflag |= PARENB;
            tty.c_cflag	&= ~PARODD;
            break;
        case Parity::ODD:
            tty.c_cflag |= PARENB;
            tty.c_cflag	|= PARODD;
            break;
        default:
            THROW_EXCEPT("parity_ value not supported!");
    }

    // Set the number of stop bits.
    switch (numStopBits_) {
        case NumStopBits::ONE:
            tty.c_cflag &= ~CSTOPB;
            break;
        case NumStopBits::TWO:
            tty.c_cflag |= CSTOPB;
            break;
        default:
            THROW_EXCEPT("numStopBits_ value not supported!");
    }

    // Disable RTS/CTS hardware flow control.
    tty.c_cflag &= ~CRTSCTS;

    // Turn on READ & ignore ctrl lines.
    tty.c_cflag |= CREAD | CLOCAL;
    
    // Set the baud rate (custom).
    tty.c_cflag &= ~CBAUD;
    tty.c_cflag |= CBAUDEX;
    tty.c_ispeed = baudRate_;
    tty.c_ospeed = baudRate_;

    // Prevent special interpretation of output bytes.
    tty.c_oflag     =   0;
    tty.c_oflag     &=  ~OPOST;

    // Set the timeout.
    if (timeout_ms_ == -1) {

        // Read is blocked until 1 byte is available.
        tty.c_cc[VTIME] = 0;
        tty.c_cc[VMIN] = 1;
    } else if (timeout_ms_ == 0) {

        // Read immediately from rx buffer.
        tty.c_cc[VTIME] = 0;
        tty.c_cc[VMIN] = 0;
    } else if (timeout_ms_ > 0) {

        // Read with timeout.
        tty.c_cc[VTIME] = (cc_t)(timeout_ms_/100);
        tty.c_cc[VMIN] = 0;
    }

    // Disable software flow control.
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);

    // Disable any special handling of received bytes.
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

    // Disable canonical mode.
    tty.c_lflag	&= ~ICANON;

    // Disable or enable echo.
    if (echo_) {
        tty.c_lflag |= ECHO;
    } else {
        tty.c_lflag &= ~(ECHO);
    }

    // Disable erasure.
    tty.c_lflag	&= ~ECHOE;

    // Disable new-line echo.
    tty.c_lflag	&= ~ECHONL;

    // Disable interpretation of INTR, QUIT and SUSP.
    tty.c_lflag	&= ~ISIG;
		
    this->SetTermios2(tty);
}

void _Serial::FlushReceiverBuffer() {
    ioctl(fileDesc_, TCFLSH, 0);
}

void _Serial::FlushTransmitterBuffer() {
    ioctl(fileDesc_, TCFLSH, 1);
}

void _Serial::FlushSerialBuffers() {
    ioctl(fileDesc_, TCFLSH, 2);
}

void _Serial::Write(const std::string& data) {

    // Check if the port is opened.
    if (state_ != State::OPEN)
        THROW_EXCEPT("The serial port is not open.");

    // Check if the file is valid.
    if (fileDesc_ == 0)
        THROW_EXCEPT("File has not been opened.");

    int writeResult = write(fileDesc_, data.c_str(), data.size());

    // Check if the write was successful.
    if (writeResult == -1)
        THROW_EXCEPT("Write to the serial port was not successful.");
}

void _Serial::Read(char& data) {

    // Check if the file is valid.
    if (fileDesc_ == 0)
        THROW_EXCEPT("The file has not been opened.");

    // Read and check if the read from the buffer was successful.
    if (read(fileDesc_, &data, 1) != 1)
        THROW_EXCEPT("Read from the file was not successful.");
}

int32_t _Serial::Available() {

    // Check if the port is opened.
    if (state_ != State::OPEN)
        THROW_EXCEPT("The serial port is not open.");
    
    int32_t ret = 0;
    ioctl(fileDesc_, FIONREAD, &ret);
    return ret;
}

termios2 _Serial::GetTermios2() {
    struct termios2 term2;
    ioctl(fileDesc_, TCGETS2, &term2);
    return term2;
}

void _Serial::SetTermios2(termios2 tty) {
    ioctl(fileDesc_, TCSETS2, &tty);
}

void _Serial::Close() {

    // Check if the file is opened.
    if (fileDesc_ != -1) {
        auto retVal = close(fileDesc_);
        if (retVal != 0)
            THROW_EXCEPT("Closing of the serial port failed.");
        fileDesc_ = -1;
    }

    // Set the state to CLOSED.
    state_ = State::CLOSED;
}
