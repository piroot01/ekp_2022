//==================================================================
//  
//  File: Status.hpp
//  Description: Definition of Status and Level class.
//  Author: Tomas Machacek
//  Date: 1 Nov 2023
//  Notes: N/A
//
//==================================================================

#ifndef STATUS_H
#define STATUS_H

// system headers
#include <iostream>

enum class Level {
    INFO,
    WARNING,
};

class Status {
public:

    Status(const std::string description, const Level level) {
        switch (level) {
            case Level::INFO:
                std::cout << "\33[32m" << "[INFO]:\33[0m\33[1m " << description << "\33[0m\n";
                break;
            case Level::WARNING:
                std::cout << "\33[33m" << "[WARNING]:\33[0m\33[1m " << description << "\33[0m\n";
                break;
            default:
                break;
        }
    }
};

#define STATUS(description, level) Status(description, level);

#endif
