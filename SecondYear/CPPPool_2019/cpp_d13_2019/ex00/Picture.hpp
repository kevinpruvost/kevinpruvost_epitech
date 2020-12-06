/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/27
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef PICTURE_HPP
#define PICTURE_HPP

// C++ includes
#include <string>
#include <iostream>
#include <fstream>

class Picture
{
public:
    Picture(const std::string & file = "");

public:
    bool getPictureFromFile(const std::string & file);

public:
    std::string data;
};

#endif // PICTURE_HPP
