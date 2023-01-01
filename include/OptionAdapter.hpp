//==================================================================
//  
//  File: OptionAdapter.hpp
//  Description: Definition of OptionAdapter class
//  Author: Tomas Machacek
//  Date: 13 Dec 2022
//  Notes: N/A
//
//==================================================================

// system headers
#include <unordered_map>
#include <string>

// user headers
#include "EnumClasses.hpp"

class OptionAdapter {
private:

    class NumDataBits_ {
    public:
        const std::unordered_map<int, NumDataBits> table = {
            {5, NumDataBits::FIVE},
            {6, NumDataBits::SIX},
            {7, NumDataBits::SEVEN},
            {8, NumDataBits::EIGHT},
        };
    };

    class Parity_ {
    public:
        const std::unordered_map<std::string, Parity> table = {
            {"none", Parity::NONE},
            {"even", Parity::EVEN},
            {"odd", Parity::ODD},
        };
    };

    class NumStopBits_ {
    public:
        const std::unordered_map<int, NumStopBits> table = {
            {1, NumStopBits::ONE},
            {2, NumStopBits::TWO},
        };
    };

    NumDataBits_ numDataBits_;
    Parity_ parity_;
    NumStopBits_ numStopBits_;

public:
    const NumDataBits& GetNumDataBitsEnum(const int numDataBits);
    const Parity& GetParityEnum(const std::string parity);
    const NumStopBits& GetNumStopBitsEnum(const int numStopBits);

};
