/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** KernelModule
*/

#include "KernelModule.hpp"


KernelModule::KernelModule()
{
}

KernelModule::~KernelModule()
{
}

std::vector<std::string> KernelModule::getVectorKernel() const
{
    return this->_kernel;
}

bool KernelModule::parsing()
{
    _kernel.clear();
    struct utsname sysinfo;
    uname(&sysinfo);

    _kernel.push_back(sysinfo.sysname);
    _kernel.push_back(sysinfo.release);
    _kernel.push_back(sysinfo.version);
    _kernel.push_back(sysinfo.machine);

    return true;
}