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
#include <cstdlib>
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
    long long int i = 0;
    std::vector<std::string> readBuffer;
    std::string tmpBuffer;
    std::chrono::time_point<std::chrono::steady_clock> prevUpdate;
    int numUpdates = 0;
    std::string updateMsg;
    std::string answer;

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
            if (i <= 1) {
                tmpBuffer.clear();
            } else {
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

    pBoard->serial.Close();
    pBoard->ReleaseInstance();

    // Manage the read data.
    STATUS("It was registered " + std::to_string(i - 1) + " entries.", Level::INFO);
    STATUS("Save the data into " + output + "? [Y/n] ", Level::INPUT);
    std::getline(std::cin, answer);

    if (answer == "y" || answer == "Y" || answer.empty()) {
        
        // Save the data.
        for (std::string& it : readBuffer)
            outputFile << it << '\n';
        outputFile.close();

        answer.clear();

        STATUS("Process the data? [Y/n] ", Level::INPUT);
        std::getline(std::cin, answer);

        if (answer == "y" || answer == "Y" || answer.empty()) {
            STATUS("Processing the data.", Level::INFO);
            std::system("python src/DataProcessor.py");
            std::system("convert data/raw_data.png data/euler_angles.png data/acceleration.png data/velocity.png data/position.png data/position_3D.png data/output.pdf");
        }

        answer.clear();
        STATUS("Show output.pdf? [Y/n] ", Level::INPUT);
        std::getline(std::cin, answer);

        if (answer == "y" || answer == "Y" || answer.empty())
            std::system("zathura data/output.pdf");
        
    }

    return 0;
}
