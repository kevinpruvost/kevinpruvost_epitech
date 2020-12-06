/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** RamModule
*/

#include "RamModule.hpp"

RamModule::RamModule()
{
}

RamModule::~RamModule()
{
}

std::vector<int> RamModule::getMemoryInfo()
{
    return this->_memoryinfo;
}

void RamModule::setDebug(bool value)
{
    this->_debug = value;
}

void RamModule::displayMemoryInfo()
{
    for (auto i: this->_memoryinfo)
        std::cerr << "Vector contain: "<<  i << std::endl;
}

void RamModule::checkInformation()
{
    if (this->_memoryinfo.size() != this->_lookingFor.size())
        std::cerr << "Informations missing." << std::endl;
    else
        std::cerr << "All information was found." << std::endl;
}

static int findElem(const std::string& str)
{
    std::string save;
    for (int i = 0; str[i]; ++i) {
        if (str[i] <= '9' && str[i] >= '0')
            save += str[i];
    }
    return std::stoi(save);
}

bool RamModule::parsing()
{
    std::string buffer;
    std::ifstream myfile(this->_path);
    std::string str;
    _memoryinfo.clear();

    if (!myfile.is_open()) {
        if (this->_debug == true) {
            std::cerr << "The file: " << this->_path << " can not be opened" << std::endl;
            return false;
        }
    }
    while (std::getline(myfile, buffer, '\n')) {
        for (auto i : this->_lookingFor)
            if (buffer.find(i, 0) != std::string::npos)
                this->_memoryinfo.push_back(findElem(buffer));
    }
    myfile.close();
    if (this->_debug == true) {
        displayMemoryInfo();
        checkInformation();
    }
    return true;
}
