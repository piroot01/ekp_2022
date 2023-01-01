#include <vector>
#include <iostream>

#include "Board.hpp"

#define CR '\r'
#define FF '\f'

int main() {
    Board* pBoard = Board::GetInstance();

    pBoard->Open();
    
    pBoard->serial.FlushSerialBuffers();

    char data;
    int i = 0;
    std::vector<std::string> readBuffer;
    std::string tmpBuffer;

    while (i < 11) {
        pBoard->serial.Read(data);

        if (data == CR) {
            if (i != 0) {
                readBuffer.push_back(tmpBuffer);
                tmpBuffer.clear();
            }
            i++;
        } else {
            if (data == FF) {
                tmpBuffer.push_back(',');
            } else {
                tmpBuffer.push_back(data);
            }
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


