/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/27
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Picture.hpp"

Picture::Picture(const std::string & file)
    : data { "" }
{
    if (!getPictureFromFile(file))
        data = "ERROR";
}

bool Picture::getPictureFromFile(const std::string & file)
{
    if (file.empty())
        return true;

    std::ifstream stream(file);

    if (!stream.is_open())
        return false;

    std::string s;

    while (std::getline(stream, s, '\0'))
        data.append(s);

    stream.close();
    return true;
}
