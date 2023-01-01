//==================================================================
//  
//  File: FastAtoi.cpp
//  Description: FastAtoi class
//  Author: Tomas Machacek
//  Date: 13 Dec 2022
//  Notes: N/A
//
//==================================================================

// system headers
#include <string>

// user headers
#include "FastAtoi.hpp"

// Method for fast conversion from std::string to int.
// It returns true if converdion was successful otherwise false (it depends on chars in str).
bool FastAtoi::Convert(const std::string& str, int& value) {
    bool negative;
    size_t nth = 0;

    if (str.find_first_not_of("-") != 0) {
        negative = true;
        nth = 1;
    } else {
        negative = false;
    }

    for (; nth < str.length(); ++nth) {
        if (str[nth] < '0' || str[nth] > '9') {
            return false;
        }
        value = (value * 10) + (str[nth] - '0');
    }

    if (negative)
        value *= -1;

    return true;
}
