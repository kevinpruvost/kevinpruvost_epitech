/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Chrono
*/

#pragma once

#include <chrono>
#include <ctime>
#include <functional>
#include <thread>

namespace RType
{
namespace Common
{
namespace FileSystemWatcher
{
    /**
     * @brief Call a function each delta time
     * 
     */
    class Chrono {
        public:
            Chrono(const float delta, const unsigned long rate);
            ~Chrono();

            void setCallback(std::function<void()> function);

            void beginPing();
            void setRate(unsigned long rate);
            void beginPing(const float delta);
            void getDeltaTime();
            void end();

        private:
            float __delta;
            unsigned long __rate;
            std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> __start;
            std::function<void()> __calback;
            bool __end;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
