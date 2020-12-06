/*
** A Kevin Pruvost's project, May 2020
** CondVar.hpp
** File description:
** condvar
*/

#pragma once

// C++ includes
#include <condition_variable>
#include <mutex>

class CondVar
{
public:
    CondVar(std::mutex & mutex);
    ~CondVar();

    void wait();
    void notify();

private:
    std::condition_variable cond;
    std::mutex & _mutex;
};