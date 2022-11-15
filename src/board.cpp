//
// The board class.
//

// system headers
#include <string>
#include <thread>
#include <chrono>

// user headers
#include "../include/board.hpp"
#include "../lib/include/cpp_serial.hpp"

Board::Board() {
    updatePer_ = defaultUpdatePer_;
}

Board::Board(time_t& updatePer) {
    updatePer_ = updatePer;
}

// Wait for board to inicialize serial communication.
void Board::WaitForSerialInit(CppSerial::SerialPort& serial, std::string& readBuffer) {
    while (1) {
        
        // Read serial buffer.
        serial.Read(readBuffer);

        // Check if board is inicialized.
        if (readBuffer.compare(bytes_.serialInit) == 0) {
            break;
        } else {

            // Sleep for sleep time.
            std::this_thread::sleep_for(std::chrono::milliseconds(updatePer_));
        }
    }
}

// Set custom update period of checking if board is ready.
void Board::SetUpdatePer(time_t& updatePer) {
    updatePer_ = updatePer;
}
