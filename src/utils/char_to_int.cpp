#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>

int main() {
    std::string inp;
    
    std::cin >> inp;

    //int nthNum = 0, numSize = 0;
    //int* tmpNum = NULL;
    unsigned int num = 0;
/*
    for (char& tmpChar : inp) {
        if (nthNum == numSize) {
            (nthNum == 0)?(numSize = 1):(numSize *= 2);
            tmpNum = (int*)realloc(tmpNum, numSize * sizeof(int));
        }
        tmpNum[nthNum] = (int)tmpChar - 48;
        nthNum++;
    }

    for (int i = 0; i < nthNum; ++i) {
        num += std::pow(10, i) * tmpNum[nthNum - i - 1];
    }
*/

    num = std::stoi(inp);

    std::cout << num << std::endl;

    //free(tmpNum);
    exit(0);
}

