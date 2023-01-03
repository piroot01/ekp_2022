//==================================================================
//  
//  File: Board.hpp
//  Title: Definition of Board class.
//  Author: Machacek Tomas
//  Date: 31 Dec 2022
//  Notes: Class is implementing singleton pattern.
//
//==================================================================

#ifndef BOARD_H
#define BOARD_H

// user headers
#include "OptionAdapter.hpp"
#include "EnumClasses.hpp"
#include "Serial.hpp"
#include "ConfigReader.hpp"

#define INIT 'i'

class Board {
public:

    // Create public instance of _Serial class.
    _Serial serial;

    // Get static instance of Board class.
    static Board* GetInstance();

    // Reset instance.
    static void ReleaseInstance();

    // Method for initialization of the board-pc communication.
    void Open();

    // Method for obtaining sampleTime from config.
    int GetSampleTime();

private:

    // Private constructor and destructor.
    Board();
    ~Board();

    // Method for initialization of the communication between the pc and the board.
    void SerialInit();

    // Static instance of the class.
    static Board* pInstance_;

    // Option variables, they could be modified using config.
    typedef struct OptionValues {
        std::string device;
        size_t baudRate;
        NumDataBits numDataBits;
        Parity parity;
        NumStopBits numStopBits;
        int32_t initTimeout_ms;
        int sampleTime_s;
    } OptionValues;

    // Default option values.
    typedef struct OptionDefaultValues {
        const std::string device = "/dev/ttyACM0";
        const int baudRate = 9600;
        const int numDataBits = 8;
        const std::string parity = "none";
        const int numStopBits = 1;
        const int initTimeout_ms = 2000;
        const int sampleTime_s = 10;
    } OptionDefaultValues;

    // Tags for the pptions.
    typedef struct OptionTags {
        const std::string device = "path_to_port";
        const std::string baudRate = "baud_rate";
        const std::string numDataBits = "number_of_data_bits";
        const std::string parity = "parity";
        const std::string numStopBits = "number_of_stop_bits";
        const std::string initTimeout = "init_timeout";
        const std::string sampleTime = "sample_time";
    } OptionTags;

    // Instances of the structs.
    OptionValues optionValues_;
    OptionDefaultValues optionDefaultValues_;
    OptionTags optionTags_;

    // Instance of adapter class.
    OptionAdapter optionAdapter_;

    char data_;
};

#endif
