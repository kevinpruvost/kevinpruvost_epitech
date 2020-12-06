/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** CPUModule
*/

#include "CPUModule.hpp"

CPUModule::CPUModule()
{
}

CPUModule::~CPUModule()
{
    _cores.clear();
}
// /proc/uptime Uptime
// /proc/stat   CPU Usage
// /sys/devices/system/cpu/cpu$NB/cpufreq/cpuinfo_max_freq Max Freq
// /proc/cpuinfo 

bool CPUModule::parsing()
{
    _cores.clear();
    _coreNumber = 0;

    std::string buffer;
    std::ifstream stream("/proc/cpuinfo");

    if (!stream.is_open())
    {
        std::cerr << "Cannot access /proc/cpuinfo." << std::endl;
        return false;
    }

    while (std::getline(stream, buffer, '\n'))
    {
        remove_if(buffer.begin(), buffer.end(), isspace);
        
        if (buffer.rfind("processor", 0) == 0)
        {
            _cores.push_back(Core());
            ++_coreNumber;
        }
        if (buffer.rfind("cpuMHz", 0) == 0)
        {
            double usage = stod(buffer.substr(buffer.find(":") + 1));
            getActualCore().setUsage(usage);
        }
    }

    stream.close();

    std::ifstream stream2("/proc/uptime");

    if (!stream2.is_open())
    {
        std::cerr << "Uptime cannot be retrieved." << std::endl;
        return false;
    }

    std::getline(stream2, buffer, '\0');

    _uptime = stoi(buffer.substr(0, buffer.find(" ")));

    stream2.close();

    // READ EVERY CORE

    for (int i = 0; i < _coreNumber; ++i)
    {
        std::string str("/sys/devices/system/cpu/cpu");
        str += std::to_string(i);
        str += "/cpufreq/cpuinfo_min_freq";
        std::ifstream streamCore(str);

        if (!streamCore.is_open())
        {
            std::cerr << "Cannot access " << str << std::endl;
            return false;
        }

        std::getline(streamCore, buffer, '\0');

        _cores[i].setMin(stod(buffer) / 1000);
        _cores[i].setUsage(_cores[i].getUsage() - _cores[i].getMin());

        streamCore.close();
    }

    for (int i = 0; i < _coreNumber; ++i)
    {
        std::string str("/sys/devices/system/cpu/cpu");
        str += std::to_string(i);
        str += "/cpufreq/cpuinfo_max_freq";
        std::ifstream streamCore(str);

        if (!streamCore.is_open())
        {
            std::cerr << "Cannot access " << str << std::endl;
            return false;
        }

        std::getline(streamCore, buffer, '\0');

        _cores[i].setMax((stod(buffer) / 1000) - _cores[i].getMin());
        _cores[i].setPercentage(_cores[i].getUsage() / _cores[i].getMax() * 100);

        streamCore.close();
    }
    return true;
}
