//
// The board header.
//

#ifndef BOARD_H
#define BOARD_H

// system headers
#include <string>
#include <unordered_map>

// user headers
#include "../lib/include/cpp_serial.hpp"

class Board {
public:
    
    // Create public 
    CppSerial::SerialPort serial;
    
    // Default constructor.
    Board();

    void Open();

private:

    // Adapter for class NumDataBits. From int to NumDataBits.
    CppSerial::NumDataBits GetNumDataBits(int& numDataBits_);

    // Adapter for class Parity. From string to Parity.
    CppSerial::Parity GetParity(std::string& parity_);

    // Adapter for class NumStopBits. From int to NumStopBits.
    CppSerial::NumStopBits GetNumStopBits(int& numStopBits_);

    // Wait for board to initialize serial communication.
    void WaitForSerialInit(CppSerial::SerialPort& serial);

    // Private read buffer
    std::string readBuffer_;

    // Variables that store values from config file.
    typedef struct Config {
        std::string device_;
        int baudRate_;
        int numDataBits_;
        std::string parity_;
        int numStopBits_;
        int timeout_ms_;

        std::string initMsg_;
        int updatePer_;
    } Config;

    // Variables needed by seril library.
    typedef struct Serial {
        size_t baudRate_;
        CppSerial::NumDataBits numDataBits_;
        CppSerial::Parity parity_;
        CppSerial::NumStopBits numStopBits_;
        int32_t timeout_ms_;
    } Serial;

    // Create instances of structs.
    Config boardConfig;
    Serial boardSerialConfig;
    
    // Defualt values for config.
    const std::string defaultDevice_ = "/dev/ttyACM0";
    const size_t defaultBaudRate_ = 9600;
    const CppSerial::NumDataBits defaultNumDataBits_ = CppSerial::NumDataBits::EIGHT;
    const CppSerial::Parity defaultParity_ = CppSerial::Parity::NONE;
    const CppSerial::NumStopBits defaultNumStopBits_ = CppSerial::NumStopBits::ONE;
    const int32_t defaultTimeout_ms_ = -1;
    const std::string defaultInitMsg_ = "i";
    const int defaultUpdatePer_ = 50;

    // Tag name definitions, that will be look for in config file.
    const std::string deviceTag_ = "path_to_port";
    const std::string baudRateTag_ = "baud_rate";
    const std::string numDataBitsTag_ = "number_of_data_bits";
    const std::string parityTag_ = "parity";
    const std::string numStopBitsTag_ = "number_of_stop_bits";
    const std::string timeoutTag_ms_ = "timeout";
    const std::string initMsgTag_ = "init_message";
    const std::string updatePerTag_ = "update_period";

    // Adapter map from int to CppSerial::NumDataBits 
    std::unordered_map<int, CppSerial::NumDataBits>
    const numDataBitsTable_ = {
        {5, CppSerial::NumDataBits::FIVE},
        {6, CppSerial::NumDataBits::SIX},
        {7, CppSerial::NumDataBits::SEVEN},
        {8, CppSerial::NumDataBits::EIGHT}
    };

    // Adapter map from string to CppSerial::Parity
    std::unordered_map<std::string, CppSerial::Parity>
    const parityTable_ = {
        {"none", CppSerial::Parity::NONE},
        {"even", CppSerial::Parity::EVEN},
        {"odd", CppSerial::Parity::ODD}
    };

    // Adapter map from int to CppSerial::NumStopBits
    std::unordered_map<int, CppSerial::NumStopBits>
    const numStopBitsTable_ = {
        {1, CppSerial::NumStopBits::ONE},
        {2, CppSerial::NumStopBits::TWO}
    };
};

#endif
