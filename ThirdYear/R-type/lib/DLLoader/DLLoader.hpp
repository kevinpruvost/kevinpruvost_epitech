/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** DllLoader
*/

#pragma once

// Project includes
#include "dll.h"

// C++ includes
#include <string>
#include <iostream>

/**
 * @brief Open, Close and get Instance from a Shared object
 * 
 */
class DLLoader {
    public:
    DLLoader(const std::string & name);
    ~DLLoader();

    const std::string & getLibName() {return __name;};
    void * getLib() {return __lib;};

    private:
        void * __lib;
        const std::string __name;
};

#ifdef __unix__
extern "C" {
    void * linux_dll_open (const char * filename);
    int linux_dll_close (void * handle);
    void * linux_dll_sym (void * handle, const char * name);
}
#elif _WIN32
    EXPORT_FUNCTION void windows_dll_close (HINSTANCE dll);
    EXPORT_FUNCTION LPFNDLLFUNC1 windows_dll_sym (HINSTANCE dll, const char *name);
    EXPORT_FUNCTION HINSTANCE windows_dll_open (const char *filename);
#endif