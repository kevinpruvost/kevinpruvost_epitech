#include "DebugController.hpp"

bool DebugController::isDebugMode = false;

void DebugController::setDebugMode(bool b)
{
    isDebugMode = b;
}

void DebugController::debugArgsIdentify(int argc, const char ** argv)
{
    if (argc >= 1)
    {
        for (int i = 0; i < argc; ++i)
        {
            std::string arg = argv[i];
            if (arg == "-d" || arg == "--debug")
                DebugController::setDebugMode(true);
        }
    }
}