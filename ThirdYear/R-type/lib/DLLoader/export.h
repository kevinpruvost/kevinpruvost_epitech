#pragma once

#ifdef __unix__
#define EXPORT_FUNCTION extern "C"
#elif _WIN32
#define EXPORT_FUNCTION extern "C" __declspec(dllexport)
#endif