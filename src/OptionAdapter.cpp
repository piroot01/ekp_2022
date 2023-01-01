//==================================================================
//  
//  File: OptionAdapter.cpp
//  Description: OptionAdapter class.
//  Author: Tomas Machacek
//  Date: 13 Dec 2022
//  Notes: N/A
//
//==================================================================

// system headers
#include <unordered_map>

// user headers
#include "OptionAdapter.hpp"
#include "EnumClasses.hpp"
#include "Exception.hpp"

const NumDataBits& OptionAdapter::GetNumDataBitsEnum(const int numDataBits) {
    std::unordered_map<int, NumDataBits>::const_iterator it = numDataBits_.table.find(numDataBits);

    if (it != numDataBits_.table.end())
        return it->second;
    else
        THROW_EXCEPT("NumDataBits parsing error.");
}

const Parity& OptionAdapter::GetParityEnum(const std::string parity) {
    std::unordered_map<std::string, Parity>::const_iterator it = parity_.table.find(parity);

    if (it != parity_.table.end())
        return it->second;
    else
        THROW_EXCEPT("Parity parsing error.");
}

const NumStopBits& OptionAdapter::GetNumStopBitsEnum(const int numStopBits) {
    std::unordered_map<int, NumStopBits>::const_iterator it = numStopBits_.table.find(numStopBits);

    if (it != numStopBits_.table.end())
        return it->second;
    else
        THROW_EXCEPT("NumStopBits parsing error.");
}
