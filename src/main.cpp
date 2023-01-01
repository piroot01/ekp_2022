#include <vector>
#include <iostream>

#include "Board.hpp"

#define CR '\r'

int main() {
    Board* pBoard = Board::GetInstance();

    pBoard->Open();

    pBoard->serial.FlushSerialBuffers();

    char data;
    int i = 0;
    std::vector<std::string> readBuffer;
    std::string tmpBuffer;

    while (i < 100) {
        pBoard->serial.Read(data);
        if (data != CR) {
            tmpBuffer.push_back(data);
        } else {
            readBuffer.push_back(tmpBuffer);
            tmpBuffer.clear();
            i++;
        }
    }
    
    i = 0;
    for (std::string& it : readBuffer) {
        std::cout << "[" << i << "]: " << it << '\n';
        i++;
    }

    pBoard->serial.Close();
    pBoard->ReleaseInstance();
    return 0;
}


