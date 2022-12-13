#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>

int main() {
    std::string inp;
    
    std::cin >> inp;

    unsigned int num = 0;

    num = std::stoi(inp);

    std::cout << num << std::endl;

    exit(0);
}

