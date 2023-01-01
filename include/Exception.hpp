//==================================================================
//  
//  File: Exception.hpp
//  Description: Definition of Exception class.
//  Author: Tomas Machacek
//  Date: 13 Dec 2022
//  Notes: File originally from
//         https://github.com/mbedded-ninja/CppUtils.
//
//==================================================================

#ifndef EXCEPTION_H
#define EXCEPTION_H

// system headers
#include <iostream>
#include <stdexcept>

class Exception : public std::runtime_error {
public:

    Exception(const char* file, int line, const std::string& arg) :
        std::runtime_error(arg) {

        // Save formated error message inside msg_.
        msg_ = "\33[1m" + std::string(file) + ":" + std::to_string(line) + ": \33[31merror:\33[0m " + arg;
    }

    ~Exception() throw() {}

    const char* what() const throw() override {
        return msg_.c_str();
    }

private:

    std::string msg_;
};

#define THROW_EXCEPT(arg) throw Exception(__FILE__, __LINE__, arg);

#endif
