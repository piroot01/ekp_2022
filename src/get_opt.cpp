//
// The get option class
//

// system headers
#include <string>
#include <iostream>

// user headers
#include "../include/get_opt.hpp"
#include "../include/exception.hpp"

GetOpt::GetOpt(int& argc, char** argv) {
    
    // Set number of arguments.
    argc_ = argc;

    //Assign individual arguments.
    switch (argc_) {
        case 3:
            opt_val_ = argv[2];
        case 2:
            opt_ = argv[1];
        case 1:
            prg_name_ = argv[0];
            break;
        default:

            // Too much arguments, expected max 3.
            THROW_EXCEPT("argc_ value not supported!");
            break;
    }
}

void GetOpt::ShowUsage() {
    std::cerr << help_1_ << prg_name_ << help_2_;
}

std::string& GetOpt::Opt() {
    
    // Option set to help.
    if ((opt_ == option_.help) || (opt_ == option_.Help)) {

        // Check if number of arguments is 2.
        if (argc_ == HELP)
            ShowUsage();
        else
            THROW_EXCEPT("Help does not expect additional argumets.");

    // Option set to path_to_port.
    } else if ((opt_ == option_.port) || (opt_ == option_.Port)) {

        //Check if number of argumets is 3.
        if (argc_ == PATH_TO_PORT)
            return opt_val_;
        else
            THROW_EXCEPT("Port not specified.");

    // If none option is selected print help message.
    } else {
        
        // Check if number of argumets is 1
        if (argc_ == NONE)
            ShowUsage();
        else
            THROW_EXCEPT("Invalid option.");
    }

    // Just for compiler.
    return null_;
}
