/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** window_load
*/

#include "dll.h"

/**
 * @brief Return a pointer to the windows shared object (.dll)
 * 
 * @param filename Absolute path of the shared object
 * @return void* Can be either NULL or a pointer to the windows shared object
 */
void * windows_dll_open (const char *filename)
{
    HINSTANCE dll;

    dll = LoadLibrary(filename);
    if (NULL == dll) {
        fprintf(stderr, "Windows Error : cannot load lib : %d, trying to load '%s'\n",
            GetLastError(),
            filename);
        return NULL;
    }
    return dll;
}

/**
 * @brief Close the windows shared object
 * 
 * @param handle Pointer to the windows shared object
 * @return int Closed shared object result
 */
void windows_dll_close (void * dll)
{
    FreeLibrary(dll);
}

/**
 * @brief Obtain address of a symbol in a shared object or executable
 * 
 * @param handle Pointer to the windows shared object
 * @param name Name of the function to retrieve
 * @return void* Can be either NULL or be a pointer to the address symbol
 */
LPFNDLLFUNC1 windows_dll_sym (void *dll, const char *name)
{
    LPFNDLLFUNC1 lpfnDllFunc1 = (LPFNDLLFUNC1)GetProcAddress(dll, name);
    if (NULL == lpfnDllFunc1) {
        fprintf(stderr, "Windows Error : cannot load sym : %d trying with '%s'\n",
            GetLastError(),
            name);
        return NULL;
    }
    return lpfnDllFunc1;
}