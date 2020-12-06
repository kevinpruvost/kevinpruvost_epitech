/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** SwapModule
*/

#include "SwapModule.hpp"

SwapModule::SwapModule()
{
}

SwapModule::~SwapModule()
{

}

static int find_elem(const std::string& s)
{
    std::string save;
    for (int i = 0; s[i]; ++i) {
        if (s[i] <= '9' && s[i] >= '0')
            save += s[i];
    }
    return std::stoi(save);
}

std::vector<int> SwapModule::getSwapVector() const
{
    return this->swap;
}


bool SwapModule::parsing()
{
    std::string buff;
    std::ifstream myfile ("/proc/meminfo");
    std::vector<std::string> looking_for = {"SwapTotal", "SwapFree"};
    swap.clear();

    if (!myfile.is_open()) {
        std::cerr << "Can't open /proc/meminfo" << std::endl;
        return false;
    }
    while (std::getline(myfile, buff, '\n')) {
        for (auto i : looking_for)
            if (buff.find(i, 0) != std::string::npos)
                swap.push_back(find_elem(buff));
    }
    myfile.close();
    return true;
}
