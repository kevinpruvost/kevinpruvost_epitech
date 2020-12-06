/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** FileSystemWatcher
*/

#pragma once

//Project includes
#include "Chrono.hpp"
#include "lib/Engine/Entity.hpp"

#include <list>
#include <iostream>
#include <functional>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

#define UNIX_SUFFIX ".so"
#define WINDOWS_SUFFIX ".dll"

namespace RType {

namespace Common {

namespace FileSystemWatcher {

/**
 * @brief Get every shared object each delta time
 * 
 */
class RTypeFileSystemWatcher {
    public:

        RTypeFileSystemWatcher(const std::string & folderToLookAT, const float delta = 10.f, const unsigned long rate = 1000.f);
        ~RTypeFileSystemWatcher();

        void actualizeList();
        bool isAlreadyInList(const std::string & str, const std::list<std::string> & list);
        bool hasSuffix(const std::string & str, const std::string & suffix);
        void callBeginPing();
        void setCallBack(std::function<void (const std::string& filepath)> function);

        //Get
        const std::list<std::string> & getFolderFile() {return __folderFile;};
        const std::string & getFolderName() {return __folderName;};

    private:

        const std::string __folderName;
        Chrono __chrono;
        std::list<std::string> __folderFile;
        std::thread __loopThread;
        bool __end;
        std::function<void (const std::string& filepath)> __callbackFunction;
};

};

};

};