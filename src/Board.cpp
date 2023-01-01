//==================================================================
//  
//  File: Board.cpp
//  Description: Board class.
//  Author: Tomas Machacek
//  Date: 31 Dec 2022
//  Notes: N/A
//
//==================================================================

// system headers
#include <chrono>
#include <thread>

// user headers
#include "Board.hpp"
#include "ConfigReader.hpp"
#include "Exception.hpp"
#include "ConfigReader.tcc"
#include "Status.hpp"

Board* Board::pInstance_ = nullptr;

Board* Board::GetInstance() {
    if (pInstance_ == nullptr)
        pInstance_ = new Board;

    return pInstance_;
}

void Board::ReleaseInstance() {
    delete pInstance_;
    pInstance_ = nullptr;
}

Board::~Board() {};

Board::Board() {
    ConfigReader* pConf = ConfigReader::GetInstance();
    
    // Save default option values.
    pConf->SaveDefaultTagValue(optionTags_.device, optionDefaultValues_.device);
    pConf->SaveDefaultTagValue(optionTags_.baudRate, optionDefaultValues_.baudRate);
    pConf->SaveDefaultTagValue(optionTags_.numDataBits, optionDefaultValues_.numDataBits);
    pConf->SaveDefaultTagValue(optionTags_.parity, optionDefaultValues_.parity);
    pConf->SaveDefaultTagValue(optionTags_.numStopBits, optionDefaultValues_.numStopBits);
    pConf->SaveDefaultTagValue(optionTags_.initTimeout, optionDefaultValues_.initTimeout_ms);

    // Parse whole config
    if (pConf->ParseConfig())
        STATUS("Parsing of the config.", Level::INFO);

    // Configure the serial accordingly.
    serial.SetDevice(pConf->GetValue<std::string>(optionTags_.device));
    serial.SetBaudRate(pConf->GetValue<int>(optionTags_.baudRate));
    serial.SetNumDataBits(optionAdapter_.GetNumDataBitsEnum(pConf->GetValue<int>(optionTags_.numDataBits)));
    serial.SetParity(optionAdapter_.GetParityEnum(pConf->GetValue<std::string>(optionTags_.parity)));
    serial.SetNumStopBits(optionAdapter_.GetNumStopBitsEnum(pConf->GetValue<int>(optionTags_.numStopBits)));

    // Other options.
    optionValues_.initTimeout_ms = pConf->GetValue<int>(optionTags_.initTimeout);

    // Release the pConf.
    pConf->ReleaseInstance();
}

void Board::Open() {
    serial.Open();
    STATUS("Serial port was opened.", Level::INFO);
    serial.FlushSerialBuffers();
    SerialInit();
}

void Board::SerialInit() {
    const auto initStart = std::chrono::steady_clock::now();
    bool initSuccessful = false;

    while (std::chrono::steady_clock::now() <= initStart + std::chrono::milliseconds(optionValues_.initTimeout_ms)) {
        if (serial.Available() > 0) {
            serial.Read(data_);
            if (data_ == INIT) {
                initSuccessful = true;
                break;
            } else {
                serial.FlushReceiverBuffer();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    if (!initSuccessful) {
        THROW_EXCEPT("Initialization failed - timeout.");
    } else {
        STATUS("Communication between board and pc was initiated.", Level::INFO);
    }
}
