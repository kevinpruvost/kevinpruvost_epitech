/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/27
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "ToyStory.hpp"

ToyStory::ToyStory()
{

}

bool ToyStory::actionStory(Toy & toy, const std::string & s,
                           bool (Toy::* func)(const std::string &))
{
    if (s.rfind("picture:", 0) == 0)
    {
        // 8 = "picture:"
        if (!toy.setAscii(s.substr(8)))
            return false;
        std::cout << toy.getAscii() << std::endl;
    }
    else
    {
        if (!(toy.*func)(s))
            return false;
    }
    return true;
}

void ToyStory::tellMeAStory(const std::string & story,
                  Toy & toy1, bool (Toy::* func1)(const std::string &),
                  Toy & toy2, bool (Toy::* func2)(const std::string &))
{
    std::string s;
    std::ifstream stream(story);

    if (!stream.is_open())
    {
        std::cout << "Bad Story" << std::endl;
        return;
    }

    std::cout << toy1.getAscii() << std::endl
              << toy2.getAscii() << std::endl;

    bool role = true;

    while (std::getline(stream, s, '\n'))
    {
        if (role)
        {
            if (!actionStory(toy1, s, func1))
            {
                Toy::Error error;
                std::cout << error.where() << ": " << error.what() << std::endl;
                return;
            }
            role = false;
        }
        else
        {
            if (!actionStory(toy2, s, func2))
            {
                Toy::Error error;
                std::cout << error.where() << ": " << error.what() << std::endl;
                return;
            }
            role = true;
        }
    }
}
