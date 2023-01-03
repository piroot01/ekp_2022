//==================================================================
//  
//  File: main.cpp
//  Description: main code
//  Author: Tomas Machacek
//  Date: 2 Jan 2023
//  Notes: N/A
//
//==================================================================

// system headers
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

// user headers
#include "Board.hpp"
#include "Status.hpp"
#include "Exception.hpp"

// Terminal symbols used in UART.
#define CR '\r'
#define FF '\f'

int main() {

    // File where captured data will be stored.
    const std::string output = "data/output.csv";
    
    std::ofstream outputFile;
    char data;
    int i = 0;
    std::vector<std::string> readBuffer;
    std::string tmpBuffer;
    std::chrono::time_point<std::chrono::steady_clock> prevUpdate;
    int numUpdates = 0;
    std::string updateMsg;


    // Initialize communication.
    Board* pBoard = Board::GetInstance();
    pBoard->Open();
    pBoard->serial.FlushSerialBuffers();
    
    // Open or if does not exists create output file.
    outputFile.open(output);

    // Capture time when the imu read starts.
    const auto readStart = std::chrono::steady_clock::now();
    
    // Read from imu for given sample time.
    while (std::chrono::steady_clock::now() <= readStart + std::chrono::seconds(pBoard->GetSampleTime())) {
        pBoard->serial.Read(data);

        if (data == FF) {
            if (i != 0) {
                readBuffer.push_back(tmpBuffer);
                tmpBuffer.clear();
            }
            i++;
        } else {
            if (data == CR) {
                tmpBuffer.push_back(',');
            } else {
                tmpBuffer.push_back(data);
            }
        }

        // Every second post the status of reading.
        if (std::chrono::steady_clock::now() - prevUpdate > std::chrono::seconds(1)) {
            prevUpdate = std::chrono::steady_clock::now();
            numUpdates++;
            std::cout << '\r';
            updateMsg = "Reading from imu: " + std::to_string(100 * numUpdates / pBoard->GetSampleTime()) + " %";
            STATUS(updateMsg, Level::WARNING);
            std::flush(std::cout);
        }
    }
    
    // Clean output buffer.
    std::cout << std::endl;

    // Post status message about number of entries.
    STATUS("It was saved " + std::to_string(i - 1) + " entries to: " + output, Level::INFO);

    // Save the data.
    for (std::string& it : readBuffer)
        outputFile << it << '\n';

    // Close the serial communication.
    pBoard->serial.Close();
    pBoard->ReleaseInstance();
    return 0;
}


