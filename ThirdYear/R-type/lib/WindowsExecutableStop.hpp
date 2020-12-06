#pragma once

#include "ForEpitechNorme.hpp"

#include <iostream>

void WindowsExecutableStop()
{
#ifdef _WIN32
    // Just for 'Windows' tests.
    system("pause");
#endif
}