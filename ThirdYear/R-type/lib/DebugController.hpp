#pragma once

// C++ includes
#include <iostream>

#define DEBUG_LOG_ERROR(text) if (DebugController::isDebugMode) std::cerr << "[DEBUG_ERROR]: " << text << std::endl
#define DEBUG_LOG(text) if (DebugController::isDebugMode) std::cout << "[DEBUG]: " << text << std::endl

#define LOG_ERROR(text) std::cerr << "[ERROR]: " << text << std::endl
#define LOG_INFO(text) std::cout << "[INFO]: " << text << std::endl


class DebugController
{
    public:
        static void setDebugMode(bool b);
        static void debugArgsIdentify(int argc, const char ** argv);
        static bool isDebugMode;
};