//==================================================================
//  
//  File: EnumClasses.hpp
//  Description: Definition of enum classes
//  Author: Tomas Machacek
//  Date: 13 Dec 2022
//  Notes: They are for Serial and OptionAdaptr
//
//==================================================================

#ifndef ENUM_CLASSES_H
#define ENUM_CLASSES_H

enum class NumDataBits {
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
};

enum class Parity {
    NONE,
    EVEN,
    ODD,
};

enum class NumStopBits {
    ONE,
    TWO,
};

enum class State {
    CLOSED,
    OPEN,
};

#endif
