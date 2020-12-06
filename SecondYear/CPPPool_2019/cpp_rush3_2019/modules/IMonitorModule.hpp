/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** IMonitorModule
*/

#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <dirent.h>
#include <sys/utsname.h>
#include <ctime>
#include <chrono>

class IMonitorModule
{
    public:
        virtual bool parsing() = 0;
	protected:
        std::string _id;
        bool _activated;
    private:
};