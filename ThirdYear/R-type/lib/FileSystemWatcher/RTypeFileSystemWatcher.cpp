/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** FileSystemWatcher
*/

#include "RTypeFileSystemWatcher.hpp"

using namespace RType::Common::FileSystemWatcher;

/**
 * @brief Construct a new RTypeFileSystemWatcher::RTypeFileSystemWatcher object
 * 
 * @param folderToLookAt Path to set the File System Watcher
 * @param delta Files's list refresh time in seconds
 * @param rate Sleep time between each call in milliseconds
 */
RTypeFileSystemWatcher::RTypeFileSystemWatcher(const std::string & folderToLookAt, const float delta, const unsigned long rate)
    : __folderName(folderToLookAt)
    , __chrono(delta, rate)
    , __loopThread(&RTypeFileSystemWatcher::callBeginPing, this)
    , __end ( false )
{
    __chrono.setCallback([this]() {
        actualizeList();
    });
    actualizeList();
}

/**
 * @brief Destroy the RTypeFileSystemWatcher::RTypeFileSystemWatcher object
 * 
 */
RTypeFileSystemWatcher::~RTypeFileSystemWatcher()
{
    __chrono.end();
    __loopThread.join();
}

/**
 * @brief Start the chrono
 * 
 */
void RTypeFileSystemWatcher::callBeginPing()
{
    __chrono.beginPing();
}

/**
 * @brief Check if string is already is the list
 * 
 * @param str String to check
 * @param list List to check
 * @return true String is already in list
 * @return false String is not in the list
 */
bool RTypeFileSystemWatcher::isAlreadyInList(const std::string & str, const std::list<std::string> & list)
{
    if (list.empty())
        return false;
    for (auto & string : list)
        if (str == string)
            return true;
    return false;
}

/**
 * @brief Check if the given string has the the given suffix
 * 
 * @param str String to check
 * @param suffix Suffix to check
 * @return true Given string has the suffix
 * @return false Given string doesn't have the suffix
 */
bool RTypeFileSystemWatcher::hasSuffix(const std::string & str, const std::string & suffix)
{
    return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

/**
 * @brief Add path that finishes with either .dll or .so and if so, add it to the list
 * 
 */
void RTypeFileSystemWatcher::actualizeList()
{
    for (const auto & entry : std::experimental::filesystem::recursive_directory_iterator(__folderName)) {
        #ifdef __unix__
            if (hasSuffix(entry.path(), UNIX_SUFFIX) && !isAlreadyInList(entry.path(), __folderFile)) {
                __folderFile.push_front(entry.path());
                if (__callbackFunction)
                    __callbackFunction(entry.path());
            }
        #elif _WIN32
        if (hasSuffix(entry.path().generic_string(), WINDOWS_SUFFIX) && !isAlreadyInList(entry.path().generic_string(), __folderFile)) {
            __folderFile.push_front(entry.path().generic_string());
            if (__callbackFunction)
                __callbackFunction(entry.path().generic_string());
        }
        #endif
    }
}

void RTypeFileSystemWatcher::setCallBack(std::function<void (const std::string& filepath)> myfunction)
{
    __callbackFunction = myfunction;
}