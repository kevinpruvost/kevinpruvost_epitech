/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** linux_load
*/

#include "dll.h"

/**
 * @brief Return a pointer to the linux shared object (.so)
 * 
 * @param filename Absolute path of the shared object
 * @return void* Can be either NULL or a pointer to the linux shared object
 */
void * linux_dll_open (const char * filename)
{
    void * handle = NULL;

    handle = dlopen(filename, RTLD_NOW);

    if (!handle) {
        fputs(dlerror(), stderr);
        return NULL;
    }
    return handle;
}

/**
 * @brief Close the linux shared object
 * 
 * @param handle Pointer to the linux shared object
 * @return int Closed shared object result
 */
int linux_dll_close (void * handle)
{
    return dlclose(handle);
}

/**
 * @brief Obtain address of a symbol in a shared object or executable
 * 
 * @param handle Pointer to the linux shared object
 * @param name Name of the function to retrieve
 * @return void* Can be either NULL or be a pointer to the address symbol
 */
void * linux_dll_sym (void * handle, const char * name)
{
    void * cosine = NULL;
    char * error = NULL;

    cosine = dlsym(handle, name);
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        return NULL;
    }
    return cosine;
}