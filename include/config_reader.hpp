#ifndef CONFIG_READER_H
#define CONFIG_READER_H

// system headers
#include <iostream>
#include <map>

class ConfigReader {
public:

    // Create new object.
    static ConfigReader* getInstance();

    // Parse the config file.
    bool parseFile(std::string fileName_);

    // Value in config file could be int or string.
    bool getValue(std::string tag, int& value);
    bool getValue(std::string tag, std::string& value);
private:

    // Default constructor.
    ConfigReader();

    // Default destructor.
    ~ConfigReader();

    // Copy of constructor.
    ConfigReader(const ConfigReader& obj) {}

    // Definition of assigment operator.
    void operator = (const ConfigReader& obj) {}

    // Store data from config file.
    std::map<std::string, std::string> configSettingMap_;

    // Static poiter to make class ConfigReader singleton.
    static ConfigReader* pInstance_;

    // Helper functions.
    std::string Trim(const std::string& str, const std::string& whiteSpace_);
    std::string Reduce(const std::string& str, const std::string& fill_, const std::string& whiteSpace_);

    // Private variables.
    std::string fileName_;
    std::string whiteSpace_;
    std::string fill_;

    // Default variables.
    const std::string defaultFileName_ = "board.conf";
    const std::string defaultWhiteSpace_ = " \t";
    const std::string defaultFill_ = " ";
};

#endif