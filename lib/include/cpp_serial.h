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
    
    // Strongly-typed enumeration of baud rates for use with the SerialPort class.
    enum class BaudRate {
        B_0,
        B_50,
        B_75,
        B_110,
        B_134,
        B_150,
        B_200,
        B_300,
        B_600,
        B_1200,
        B_1800,
        B_2400,
        B_4800,
        B_9600,
        B_19200,
        B_38400,
        B_57600,
        B_115200,
        B_230400,
        B_460800,
        B_CUSTOM,
    };

    // Enumeration of all the valid num. of data bits. Must align with the options
    enum class NumDataBits {
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
    };

    enum class Parity {
        NONE,
        EVEN,
        ODD,
    };

    enum class NumStopBits {
        ONE,
        TWO,
    };

    // Represents the state of the serial port.
    enum class State {
        CLOSED,
        OPEN,
    };

    // SerialPort object is used to perform rx/tx serial communication.
    class SerialPort {
    public:
        
        // Default constructor. You must specify at least the device before calling Open().
        SerialPort();

        // Constructor that sets up serial port with the basic (required) parameters.
        SerialPort(const std::string &device, BaudRate baudRate);

        // Constructor that sets up serial port and allows the user to specify all the common parameters.
        SerialPort(const std::string &device, BaudRate baudRate, NumDataBits numDataBits, Parity parity, NumStopBits numStopBits);

        // Constructor that sets up serial port with the basic parameters, and a custom baud rate.
        SerialPort(const std::string &device, speed_t baudRate);

        // Destructor. Closes serial port if still open.
        virtual ~SerialPort();

        // Sets the device to use for serial port communications.
        void SetDevice(const std::string &device);

        // Call this to set a standard baud rate.
        void SetBaudRate(BaudRate baudRate);

        // Call this to set a custom baud rate.
        void SetBaudRate(speed_t baudRate);

        // Call this to set the num. of data bits.
        void SetNumDataBits(NumDataBits numDataBits);

        // Call this to set the parity.
        void SetParity(Parity parity);

        void SetNumStopBits(NumStopBits numStopBits);

        // Sets the read timeout (in milliseconds)/blocking mode.
        void SetTimeout(int32_t timeout_ms);

        // Enables/disables echo.
        void SetEcho(bool value);

        // Opens the COM port for use.
        void Open();

        // Closes the COM port.
        void Close();

        // Sends a text message over the com port.
        void Write(const std::string& data);

        // Sends a binary message over the com port.
        void WriteBinary(const std::vector<uint8_t>& data);

        // Use to read text from the COM port.
        void Read(std::string& data);

        // Use to read binary data from the COM port.
        void ReadBinary(std::vector<uint8_t>& data);

        // Use to get number of bytes available in receive buffer.
        // It returns the number of bytes available in the receive buffer (ready to be read).
        int32_t Available();

        // Use to get the state of the serial port.
        // It returns the state of the serial port.
        State GetState();

    private:

        // Configures the tty device as a serial port.
        void ConfigureTermios();

        // Returns a populated termios2 structure for the serial port pointed to by the file descriptor.
        termios2 GetTermios2();

        // Assigns the provided tty settings to the serial port pointed to by the file descriptor.
        void SetTermios2(termios2 tty);

        // Keeps track of the serial port's state.
        State state_;

        // The file path to the serial port device (e.g. "/dev/ttyUSB0").
        std::string device_;

        // The type of baud rate that the user has specified.
        BaudRateType baudRateType_;

        // The current baud rate if baudRateType_ == STANDARD.
        BaudRate baudRateStandard_;

        // The current baud rate if baudRateType_ == CUSTOM.
        speed_t baudRateCustom_;

        // The num. of data bits. Defaults to 8 (most common).
        NumDataBits numDataBits_ = NumDataBits::EIGHT;

        // The parity. Defaults to none (most common).
        Parity parity_ = Parity::NONE;

        // The num. of stop bits. Defaults to 1 (most common).
        NumStopBits numStopBits_ = NumStopBits::ONE;

        // The file descriptor for the open file. This gets written to when Open() is called.
        int fileDesc_;

        bool echo_;

        int32_t timeout_ms_;

        std::vector<char> readBuffer_;
        unsigned char readBufferSize_B_;

        static constexpr BaudRate defaultBaudRate_ = BaudRate::B_57600;
        static constexpr int32_t defaultTimeout_ms_ = -1;
        static constexpr unsigned char defaultReadBufferSize_B_ = 255;
    };
}

#endif
