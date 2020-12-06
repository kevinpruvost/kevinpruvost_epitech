/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** DllLoader
*/

#include "DLLoader.hpp"

/**
 * @brief Construct a new DLLoader::DLLoader object
 * 
 * @param libname absolute path referencing to the dll
 */
DLLoader::DLLoader(const std::string & libname)
    : __name ( libname )
{
    __lib = nullptr;

    #ifdef __unix__
        __lib = linux_dll_open(this->__name.c_str());
    #elif _WIN32
        __lib = windows_dll_open(this->__name.c_str());
    #endif

    if (!__lib) {
        std::cerr << "\nLibrary (" << __name << ") cannot be loaded\n" << std::endl;
        __lib = nullptr;
    }
}

/**
 * @brief Destroy the DLLoader::DLLoader object
 * 
 */
DLLoader::~DLLoader()
{
    if (__lib) {
        #ifdef __unix__
            linux_dll_close(__lib);
        #elif _WIN32
            windows_dll_close((HINSTANCE)__lib);
        #endif
    }
    __lib = nullptr;
}
