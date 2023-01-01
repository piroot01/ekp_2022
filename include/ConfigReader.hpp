//==================================================================
//  
//  File: Config_reader.hpp
//  Title: Definition of ConfigReader class.
//  Author: Machacek Tomas
//  Date: 14 Dec 2022
//  Notes: Class ConfigReader uses singleton pattern.
//
//==================================================================

#ifndef CONFIG_READER_H
#define CONFIG_READER_H

// system headers
#include <string>
#include <unordered_map>
#include <variant>

// Private class TagValue that is accessible only by ConfigReader class.
// It stores tagValue as an variant
class TagValue {
private:
    friend class ConfigReader;

    TagValue(const std::variant<std::string, int> &value) : tagValue(value) {};
    
    template <typename T>
    const T& GetValue();

    std::variant<std::string, int> tagValue;
};

class ConfigReader {
public:
    
    // Get static instance of ConfigReader class.
    static ConfigReader* GetInstance();
    
    // Reset instance, free the singleton.
    static void ReleaseInstance();

    // Method for setting default tag values based on tagName.
    // It returns true if new tag was created, if tag with desired tagName already exists it returns false.
    template <typename T>
    bool SaveDefaultTagValue(const std::string& tagName, const T& defaultTagValue);

    // Parse the config file.
    bool ParseConfig();

    // Method for getting values from config.
    // It returns valid tagValue based on tagName.
    template <typename T>
    const T& GetValue(const std::string& tagName);

private:
    
    // Constructor and destructor must be private.
    ConfigReader();
    ~ConfigReader();

    // Method for trimming loaded tag or its value.
    std::string Trim(const std::string& str);

    // Static pointer which will point to the instance of this class.
    static ConfigReader* pInstance_;

    // Here will be stored all tags with options.
    std::unordered_map<std::string, TagValue*> config_;

    // Default values.
    const std::string defaultFileName_ = "board.conf";
    const std::string defaultWhiteSpace_ = " \t";
    const std::string defaultDelimeter_ = "=";
    const std::string defaultComment_ = "#";
};

#endif
