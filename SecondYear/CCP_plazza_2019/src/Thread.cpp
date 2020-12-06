/*
** A Kevin Pruvost's project, May 2020
** Thread.cpp
** File description:
** thread
*/

#include "Thread.hpp"

Thread::~Thread()
{
}

void Thread::detach()
{
    if (mode == 1)
        _thread.detach();
    else if (mode == 2)
        pthread_create(&_pthread, NULL, _startRoutine, _routineArg);
}

void Thread::join()
{
    _thread.join();
}