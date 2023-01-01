//==================================================================
//  
//  File: FastAtoi.hpp
//  Description: Definition of FastAtoi class
//  Author: Tomas Machacek
//  Date: 13 Dec 2022
//  Notes: N/A
//
//==================================================================

#ifndef FAST_ATOI
#define FAST_ATOI

// system headers
#include <string>

class FastAtoi {
public:
    static bool Convert(const std::string& str, int& value);

};

#endif
