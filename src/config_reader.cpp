//
// The config reader class.
//

// system headers
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
#include <utility>

// user headers
#include "../include/config_reader.hpp"
#include "../include/exception.hpp"

#define NULL_PTR 0

// Create null pointer as an instance of class.
ConfigReader* ConfigReader::pInstance_ = NULL_PTR;

// Default constructor.
ConfigReader::ConfigReader() {
    
    // Clear data.
    configSettingMap_.clear();
    
    // Set default fileName_.
    fileName_ = defaultFileName_;
}

// Default destructor.
ConfigReader::~ConfigReader() {
    
    // Clear data.
    configSettingMap_.clear();
}

// Create new instance of class.
ConfigReader* ConfigReader::getInstance() {
    if (pInstance_ == NULL_PTR)
        pInstance_ = new ConfigReader;

    return pInstance_;
}

// Find tag and its value. Convert to int.
bool ConfigReader::getValue(std::string tag, int& value) {
    std::map<std::string, std::string>::iterator it;
    it = configSettingMap_.find(tag);

    if (it != configSettingMap_.end()) {
        value = atoi((it->second).c_str());
        return true;
    }

    return false;
}

// Find tag and its value. Convert to 
bool ConfigReader::getValue(std::string tag, std::string& value) {
    std::map<std::string, std::string>::iterator it;
    it = configSettingMap_.find(tag);

    if (it != configSettingMap_.end()) {
        value = it->second;
        return true;
    }

    return false;
}

// Config parser.
bool ConfigReader::parseFile()
{
    std::ifstream inputFile;
    inputFile.open(fileName_.c_str());
    int initPos = 0;
    std::string line;

    if (inputFile.fail()) {
        THROW_EXCEPT("Unable to open config file.");
        return false;
    }
    
    while (std::getline(inputFile, line)) {
        
        // Remove comments.
        size_t found = line.find_first_of(defaultComment_);
        std::string configData = line.substr(0, found);

        // Remove \r from config file.
        // Erase–remove idiom
        //configData.erase(std::remove(configData.begin(), configData.end(), '\r'), configData.end());
        
        // If the defaultComment_ sign was not found, skip.
        if (configData.empty())
            continue;

        std::size_t len = configData.find(defaultDelimeter_);

        std::string tag, value;

        if (len != std::string::npos) {
            tag = configData.substr(initPos, len);
            value = configData.substr(len + 1);
        }

        tag = Reduce(tag);
        value = Reduce(value);

        if (tag.empty() || value.empty())
            continue;

        std::map<std::string, std::string>::iterator itr = configSettingMap_.find(tag);

        if (itr != configSettingMap_.end())
            configSettingMap_.erase(tag);

        configSettingMap_.insert(std::pair<std::string, std::string>(tag, value));
    }
    return true;
}

// Helper functions
std::string ConfigReader::Trim(const std::string& str)
{
    size_t strBegin = str.find_first_not_of(defaultWhiteSpace_);
    if (strBegin == std::string::npos)
        return "";

    size_t strEnd = str.find_last_not_of(defaultWhiteSpace_);
    size_t strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string ConfigReader::Reduce(const std::string& str)
{
    // Trim first.
    std::string result = Trim(str);

    size_t beginSpace = result.find_first_of(defaultWhiteSpace_);
    while (beginSpace != std::string::npos)
    {
        size_t endSpace = result.find_first_not_of(defaultWhiteSpace_, beginSpace);
        size_t range = endSpace - beginSpace;

        result.replace(beginSpace, range, defaultFill_);

        size_t newStart = beginSpace + defaultFill_.length();
        beginSpace = result.find_first_of(defaultWhiteSpace_, newStart);
    }

    return result;
}
