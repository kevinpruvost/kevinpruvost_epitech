#pragma once

// C++ includes
#include <chrono>

class Chronometer
{
public:
    Chronometer();
    ~Chronometer();

    void start();
    void restart();

    float getPastTimeInSeconds();

private:
    std::chrono::steady_clock::time_point __startTime;
    std::chrono::steady_clock::time_point __endTime;
};