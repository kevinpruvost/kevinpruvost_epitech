#include "Chronometer.hpp"

Chronometer::Chronometer()
    : __startTime{ std::chrono::steady_clock::now() }
{
}

Chronometer::~Chronometer()
{
}

void Chronometer::start()
{
    __startTime = std::chrono::steady_clock::now();
}

void Chronometer::restart()
{
    __startTime = std::chrono::steady_clock::now();
}

float Chronometer::getPastTimeInSeconds()
{
    __endTime = std::chrono::steady_clock::now();

    return std::chrono::duration<float, std::chrono::seconds::period>(__endTime - __startTime).count();
}
