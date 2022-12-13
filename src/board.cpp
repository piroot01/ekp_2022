//
// The board class.
//

// system headers
#include <bits/chrono.h>
#include <string>
#include <thread>
#include <chrono>

// user headers
#include "../include/board.hpp"
#include "../lib/include/cpp_serial.hpp"
#include "../include/exception.hpp"
#include "../include/config_reader.hpp"

Board::Board() {
    // Create instance of ConfigReader class
    ConfigReader* pconf = ConfigReader::getInstance();
    
    // Use default config file name.
    pconf->parseFile();

    // Parse individual options.
    pconf->getValue(deviceTag_, boardConfig.device_);
    pconf->getValue(baudRateTag_, boardConfig.baudRate_);
    pconf->getValue(numDataBitsTag_, boardConfig.numDataBits_);
    pconf->getValue(parityTag_, boardConfig.parity_);
    pconf->getValue(numStopBitsTag_, boardConfig.numStopBits_);
    pconf->getValue(timeoutTag_, boardConfig.timeout_ms_);
    pconf->getValue(initMsgTag_, boardConfig.initMsg_);
    pconf->getValue(initUpdatePerTag_, boardConfig.initUpdatePer_ms_);
    pconf->getValue(initTimeoutTag_, boardConfig.initTimeout_ms_);
    pconf->getValue(readBuffSizeTag_, boardConfig.readBuffSize_);
    pconf->getValue(readUpdatePerTag_, boardConfig.readUpdatePer_us_);
    pconf->getValue(readBuffTimeoutTag_, boardConfig.readBuffTimeout_ms_);

    // If some option in config file is set wrongly or not at all, use default values.
    if (boardConfig.device_.empty())
        boardConfig.device_ = defaultDevice_;

    if (boardConfig.baudRate_ == 0)
        boardSerialConfig.baudRate_ = defaultBaudRate_;
    else
        boardSerialConfig.baudRate_ = boardConfig.baudRate_;

    if (boardConfig.numDataBits_ == 0)
        boardSerialConfig.numDataBits_ = defaultNumDataBits_;
    else
        boardSerialConfig.numDataBits_ = GetNumDataBits(boardConfig.numDataBits_);

    if (boardConfig.parity_.empty())
        boardSerialConfig.parity_ = defaultParity_;
    else
        boardSerialConfig.parity_ = GetParity(boardConfig.parity_);

    if (boardConfig.numStopBits_ == 0)
        boardSerialConfig.numStopBits_ = defaultNumStopBits_;
    else
        boardSerialConfig.numStopBits_ = GetNumStopBits(boardConfig.numStopBits_);

    if (boardConfig.timeout_ms_ == 0)
        boardSerialConfig.timeout_ms_ = defaultTimeout_ms_;
    else
        boardSerialConfig.timeout_ms_ = boardConfig.timeout_ms_;

    if (boardConfig.initMsg_.empty())
        boardConfig.initMsg_ = defaultInitMsg_;

    if (boardConfig.initUpdatePer_ms_ == 0)
        boardConfig.initUpdatePer_ms_ = defaultInitUpdatePer_ms_;

    if (boardConfig.initTimeout_ms_ == 0)
        boardConfig.initTimeout_ms_ = defaultInitTimeout_ms_;

    if (boardConfig.readBuffSize_ == 0)
        boardConfig.readBuffSize_ = defaultReadBuffSize_;

    if (boardConfig.readUpdatePer_us_ == 0)
        boardConfig.readUpdatePer_us_ = defaultReadUpdatePer_us_;

    if (boardConfig.readBuffTimeout_ms_ == 0)
        boardConfig.readBuffTimeout_ms_ = defaultReadBuffTimeout_ms_;

    // Set serial port accordingly.
    serial.SetDevice(boardConfig.device_);

    serial.SetBaudRate(boardSerialConfig.baudRate_);

    serial.SetNumDataBits(boardSerialConfig.numDataBits_);

    serial.SetParity(boardSerialConfig.parity_);

    serial.SetNumStopBits(boardSerialConfig.numStopBits_);

    serial.SetTimeout(boardSerialConfig.timeout_ms_);
}

// Method for opening the serial port.
void Board::Open() {

    // Open the serial port.
    serial.Open();

    // Remove any data from both receive and transmitter buffer.
    serial.FlushSerialBuff();
    
    // Before any communication wait for boards serial interface to start up.
    WaitForSerialInit(serial);
}

void Board::ReadUntil(std::string& data) {
    data.clear();
    auto start = std::chrono::steady_clock::now();

    if(serial.GetState() != CppSerial::State::OPEN)
            THROW_EXCEPT(std::string() + __PRETTY_FUNCTION__ + " called but state != OPEN. Please call Open() first.");

    while (std::chrono::steady_clock::now() <= start + std::chrono::milliseconds(boardConfig.readBuffTimeout_ms_)) {

        // If serial buffer contains as many as readBuffSize_ chars;
        if (serial.Available() >= boardConfig.readBuffSize_) {
            serial.Read(data);
            return;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(boardConfig.readUpdatePer_us_));
    }

    // If the message is not received within initTimeout_ms_ period.
    THROW_EXCEPT("Serial board did not fill the input buffer within timeout!");
    return;
}

void Board::ReadUntil(std::string& data, int& limit) {
    data.clear();
    //auto start = std::chrono::steady_clock::now();

    if(serial.GetState() != CppSerial::State::OPEN)
            THROW_EXCEPT(std::string() + __PRETTY_FUNCTION__ + " called but state != OPEN. Please call Open() first.");

    while (true) {

        // If serial buffer contains as many as readBuffSize_ chars;
        if (serial.Available() >= limit) {
            serial.Read(data);
            return;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(boardConfig.readUpdatePer_us_));
    }

    // If the message is not received within initTimeout_ms_ period.
    THROW_EXCEPT("Serial board did not fill the input buffer within timeout!");
    return;

}


// Wait for board to inicialize serial communication.
void Board::WaitForSerialInit(CppSerial::SerialPort& serial) {
    if(serial.GetState() != CppSerial::State::OPEN)
        THROW_EXCEPT(std::string() + __PRETTY_FUNCTION__ + " called but state != OPEN. Please call Open() first.");

    auto start = std::chrono::steady_clock::now();

    while (std::chrono::steady_clock::now() <= start + std::chrono::milliseconds(boardConfig.initTimeout_ms_)) {
    
        // Read serial buffer.
        if (serial.Available() > 0)
            serial.Read(readBuffer_);
        
        // Check if board is inicialized.
        if (readBuffer_.compare(boardConfig.initMsg_) == 0) {
            return;
        } else {
            
            // Sleep for sleep time.
                std::this_thread::sleep_for(std::chrono::milliseconds(boardConfig.initUpdatePer_ms_));
        }
    }
    
    // If the message is not received within initTimeout_ms_ period.
    THROW_EXCEPT("Init timeout - serial communication could not be inicialized!");
    return;
}

// Adapter from int to CppSerial::NumDataBits
CppSerial::NumDataBits Board::GetNumDataBits(int& numDataBits_) {
    CppSerial::NumDataBits tmpNumDataBits;
    auto it = numDataBitsTable_.find(numDataBits_);

    if (it != numDataBitsTable_.end())
        tmpNumDataBits = it->second;
    else
        THROW_EXCEPT("Wrong number of data bits!");

    return tmpNumDataBits; 
}

// Adapter from string to CppSerial::Parity
CppSerial::Parity Board::GetParity(std::string& parity_) {
    CppSerial::Parity tmpParity;
    auto it = parityTable_.find(parity_);

    if (it != parityTable_.end())
        tmpParity = it->second;
    else
        THROW_EXCEPT("Wrong parity!");

    return tmpParity; 
}

// Adapter from int to CppSerial::NumStopBits
CppSerial::NumStopBits Board::GetNumStopBits(int& numStopBits_) {
    CppSerial::NumStopBits tmpNumStopBits;
    auto it = numStopBitsTable_.find(numStopBits_);

    if (it != numStopBitsTable_.end())
        tmpNumStopBits = it->second;
    else
        THROW_EXCEPT("Wrong number of stop bits!");

    return tmpNumStopBits; 
}

