//==================================================================
//  
//  File: Config_reader.tcc
//  Title: Definition of ConfigReader templated methods.
//  Author: Machacek Tomas
//  Date: 14 Dec 2022
//  Notes: Class ConfigReader uses singleton pattern.
//
//==================================================================

// user headers
#include "ConfigReader.hpp"
#include "Exception.hpp"

// Method for retrieving tagValue from config_.
template <typename T>
const T& TagValue::GetValue() {
    return std::get<T>(tagValue);
}

// Method for setting default tag values based on tagName.
// It returns true if new tag was created, if tag with desired tagName already exists it returns false.
template <typename T>
bool ConfigReader::SaveDefaultTagValue(const std::string& tagName, const T& defaultTagValue) {
    std::unordered_map<std::string, TagValue*>::iterator it = config_.find(tagName);

    if (it == config_.end()) {
    
        // Initialization of new member of config_
        config_[tagName] = new TagValue(defaultTagValue);
        return true;
    } else {

        // If the tag is already saved.
        THROW_EXCEPT("Config option with tag '" + tagName + "' already saved.");
        return false;
    }
}

// Method for getting values from config.
// It returns valid tagValue based on tagName.
template <typename T>
const T& ConfigReader::GetValue(const std::string& tagName) {
    std::unordered_map<std::string, TagValue*>::iterator it = config_.find(tagName);

    if (it != config_.end())
        return it->second->GetValue<T>();

    // Just in case.
    THROW_EXCEPT("Config option with tag '" + tagName + "' not found.");
}
