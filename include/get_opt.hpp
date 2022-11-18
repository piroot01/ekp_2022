//
// The get-option header.
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
    void Opt(/*std::string& port*/);

    // Return path to port (everything after -p/--port option) or show help message.
    std::string& GetPort();
private:

    // Path to port.
//    std::string port_ = "";

    // Strings for program name, option and option value.
    std::string prgName_, opt_, optVal_;
    
    // Number of input arguments.
    int argc_;

    // Numer as option.
    enum option_num_ {
        NONE = 1,
        HELP,
//        PATH_TO_PORT,
    };

    // Options
    struct Option {

        // For help.
        std::string help = "-h";
        std::string Help = "--help";

        // For port path.
//        std::string port = "-p";
//        std::string Port = "--port";
    };
    
    struct Option option_;
    
    // Help message.
    std::string help_msg_ = "Help message.";
};

#endif
