/*
** A Kevin Pruvost's project, May 2020
** CondVar.cpp
** File description:
** condvar
*/

#include "CondVar.hpp"

CondVar::CondVar(std::mutex & mutex)
    : _mutex { mutex }
{
}

CondVar::~CondVar()
{
}

void CondVar::wait()
{
    std::unique_lock<std::mutex> lock(_mutex);
    cond.wait(lock);
}

void CondVar::notify()
{
    std::unique_lock<std::mutex> lock(_mutex);
    cond.notify_all();
}