/*
** EPITECH PROJECT, 2020
** SpriteData.hpp
** File description:
** sprite data
*/

#pragma once

// Project includes
#include "Exception.hpp"

// C++ includes
#include <map>
#include <string>
#include <algorithm>

class SpriteData
{
public:
    SpriteData() = default;
    ~SpriteData() = default;

public:
    int x;
    int y;
    std::string spritePictureFilename;
    int spriteLeft;
    int spriteTop;
    unsigned int spriteWidth;
    unsigned int spriteHeight;
    unsigned char character;
    unsigned char replaceChar[2];
    unsigned char nbAnim;
    unsigned char fondColor;
    unsigned char textColor;
};

std::map<char, SpriteData> loadSpriteDataFromFile(const std::string & fileName);
std::string getSpriteDirectory(const std::string & fileName);