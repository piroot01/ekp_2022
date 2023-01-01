//==================================================================
//  
//  File: ConfigReader.cpp
//  Description: ConfigReader class.
//  Author: Tomas Machacek
//  Date: 13 Dec 2022
//  Notes: N/A
//
//==================================================================

// system headers
#include <fstream>
#include <unordered_map>
#include <variant>

// user headers
#include "ConfigReader.hpp"
#include "FastAtoi.hpp"
#include "Exception.hpp"

// Class ConfigReader is singleton.
ConfigReader* ConfigReader::pInstance_ = nullptr;

ConfigReader::ConfigReader() {
    config_.clear();
}

// Dectructor of the class ConfigReader, it deallocates the config_ second value (tagValue).
ConfigReader::~ConfigReader() {
    for (auto& value : config_)
        delete value.second;

    config_.clear();
}

// Method for obtaining instance of ConfigReader class.
ConfigReader* ConfigReader::GetInstance() {
    if (pInstance_ == nullptr) {
        pInstance_ = new ConfigReader;
    }

    return pInstance_;
}

// Method for releasing the ConfigReader instance.
void ConfigReader::ReleaseInstance() {
    delete pInstance_;
    pInstance_ = nullptr;
}

// Method for parsing whole config file.
// If everythig runs ok, it returns true.
bool ConfigReader::ParseConfig() {
    std::ifstream inputFile;
    int initPos = 0;
    std::string line, configData, tagName, tagValue;
    int tagValueInt = 0;
    size_t found, len;

    inputFile.open(defaultFileName_.c_str());

    // If the opening of the file fails.
    if (inputFile.fail()) {
        THROW_EXCEPT("Unable to open config file.");
        return false;
    }

    // Read the config file line by line.
    while (std::getline(inputFile, line)) {

        // Skip the lines which have comment sign in front.
        found = line.find_first_of(defaultComment_);
        configData = line.substr(0, found);

        if (configData.empty())
            continue;

        // Divide the line by delimeter.
        len = configData.find(defaultDelimeter_);

        if (len != std::string::npos) {
            tagName = configData.substr(initPos, len);
            tagValue = configData.substr(len + 1);
        }

        // Trim both tagName and tagValue.
        tagName = Trim(tagName);
        tagValue = Trim(tagValue);

        if (tagName.empty())
            continue;

        // Initialize an iterator through config_.
        std::unordered_map<std::string, TagValue*>::iterator it = config_.find(tagName);

        // If the tagName was founded and its value is not empty.
        if (it != config_.end() && !tagValue.empty()) {

            // Try to convert the string to integer.
            if (FastAtoi::Convert(tagValue, tagValueInt)) {
                it->second->tagValue = tagValueInt;
                tagValueInt = 0;
            } else {
                it->second->tagValue = tagValue;
            }
        } else {
            continue;
        }
    }

    return true;
}

// Method used for editing the captured string.
// It returns string with no whitespaces in fron or after the string.
std::string ConfigReader::Trim(const std::string& str) {
    size_t strBegin = str.find_first_not_of(defaultWhiteSpace_);

    if (strBegin == std::string::npos)
        return "";

    size_t strEnd = str.find_last_not_of(defaultWhiteSpace_);

    return str.substr(strBegin, strEnd - strBegin + 1);
}
