/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** dll
*/

#pragma once

#ifdef __unix__
    #include <dlfcn.h>
    #include <stdio.h>
    #define EXPORT_FUNCTION extern "C"
#elif _WIN32
    #include <windows.h>
    #include <stdio.h>
    typedef HRESULT(CALLBACK* LPFNDLLFUNC1)(DWORD, UINT*);
    #define EXPORT_FUNCTION extern "C" __declspec(dllexport)
#endif