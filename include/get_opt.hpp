//
// The get option header.
//

#ifndef GET_OPT_H
#define GET_OPT_H

// system headers
#include <string>

class GetOpt {
public:

    // Default constructor.
    GetOpt(int& argc, char** argv);

    // Show usage of the program.
    void ShowUsage();
    
    // Determine which option is used.
    void Opt(std::string& port);

    // Return path to port (everything after -p/--port option) or show help message.
    std::string& GetPort();
private:

    // Path to port.
    std::string port_ = "";

    // Strings for program name, option and option value.
    std::string prg_name_, opt_, opt_val_;
    
    // Number of input arguments.
    int argc_;

    // Numer as option.
    enum option_num_ {
        NONE = 1,
        HELP,
        PATH_TO_PORT,
    };

    // Options
    struct Option {

        // For help.
        std::string help = "-h";
        std::string Help = "--help";

        // For port path.
        std::string port = "-p";
        std::string Port = "--port";
    };
    
    struct Option option_;
    
    // Help message.
    std::string help_1_ = "Usage: ";
    std::string help_2_ = " <option(s)> PATH_TO_PORT\nOptions:\n-h, --help\t\tShow this help message.\n-p, --port PATH_TO_PORT\tSpecify the path to port.";
};

#endif
