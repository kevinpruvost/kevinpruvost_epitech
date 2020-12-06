/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Chrono
*/

#include "Chrono.hpp"
#include <iostream>

using namespace RType::Common::FileSystemWatcher;

/**
 * @brief Construct a new Chrono:: Chrono object
 * 
 * @param delta Refresh time in seconds
 * @param rate Sleep time between each call in milliseconds
 */
Chrono::Chrono(const float delta, const unsigned long rate)
    : __delta ( delta )
    , __rate ( rate )
    , __end ( false )
{
}

/**
 * @brief Destroy the Chrono:: Chrono object
 * 
 */
Chrono::~Chrono()
{
}

/**
 * @brief Set the callback function, used when the refresh time has been reached
 * 
 * @param function callback function
 */
void Chrono::setCallback(std::function<void()> function)
{
    __calback = function;
}

/**
 * @brief Start refresh clock
 * 
 */
void Chrono::beginPing()
{
    __start = std::chrono::steady_clock::now();
    getDeltaTime();
}

/**
 * @brief Change refresh time and start clock
 * 
 * @param delta new refresh time
 */
void Chrono::beginPing(const float delta)
{
    __delta = delta;
    beginPing();
}

/**
 * @brief Set new rate time
 * 
 * @param rate new rate time
 */
void Chrono::setRate(unsigned long rate)
{
    __rate = rate;
}

/**
 * @brief Use callback when delta time between the start and end clock is equal or superior to the refresh time
 * 
 */
void Chrono::getDeltaTime()
{
    if (__end)
        return;
    auto end = std::chrono::steady_clock::now();
    float delta = std::chrono::duration<double, std::ratio<1, 1>>(end - __start).count();

    if (delta >= __delta) {
        if (__calback)
            __calback();
        __start = std::chrono::steady_clock::now();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(__rate));
    getDeltaTime();
}

/**
 * @brief Prepare the thread to join
 * 
 */
void Chrono::end()
{
    __end = true;
}
