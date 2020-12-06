/*
** A Kevin Pruvost's project, May 2020
** Thread.hpp
** File description:
** thread
*/

#pragma once

// C++ includes
#include <thread>

// C includes
#include <pthread.h>

class Thread
{
public:
    Thread() noexcept = default;

    Thread(void * (*startRoutine)(void *), void * routineArg)
        : _startRoutine { startRoutine }
        , _routineArg { routineArg }
    {
        mode = 2;
    }

    template<typename _Callable, typename... _Args>
    explicit Thread(_Callable && __f, _Args && ... __args)
        : _thread(__f, __args...)
    {
        mode = 1;
    }

    ~Thread();

    void detach();
    void join();

protected:
private:
    std::thread _thread;
    pthread_t _pthread;
    void * (*_startRoutine)(void *);
    void * _routineArg;
    int mode = 0;
};