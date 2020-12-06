/*
** EPITECH PROJECT, 2020
** SpriteData.cpp
** File description:
** sprite data
*/

#include "SpriteData.hpp"

// C includes
#include <stddef.h>

// C++ includes
#include <iostream>
#include <vector>
#include <fstream>
#include <regex>

std::string getSpriteDirectory(const std::string & fileName)
{
    return fileName.substr(0, fileName.find_last_of('/') + 1);
}

std::map<char, SpriteData> loadSpriteDataFromFile(const std::string & fileName)
{
    std::map<char, SpriteData> map;

    std::ifstream f1(fileName);
    std::string s;
    std::string directory = fileName.substr(0, fileName.find_last_of('/') + 1);

    if (!f1.is_open())
    {
        throw EXCEPTION("Texture file " + fileName + " cannot be opened.");
        return map;
    }

    std::vector<std::string> lines;

    while (std::getline(f1, s, '\n'))
        lines.push_back(s);
    f1.close();

    lines.erase(lines.begin());
    lines.erase(lines.begin());

    if (lines.empty())
    {
        throw EXCEPTION("Texture file " + fileName + " is not well formated.");
        return map;
    }

    for (auto & line : lines)
    {
        SpriteData spriteData;

        std::string base = line;

        try {
            auto regexx = std::regex("(.) (.*) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (..) (\\d+) (\\d+)");
            std::smatch match;
        
            if (!std::regex_search(line, match, regexx) || match.size() != 11)
            {
                throw EXCEPTION("Texture file " + fileName + " is not well formated.");
                return map;
            }

            spriteData.character = match.str(1).c_str()[0];
            spriteData.spritePictureFilename = directory + match.str(2);
            spriteData.spriteLeft = std::stoi(match.str(3));
            spriteData.spriteTop = std::stoi(match.str(4));
            spriteData.spriteWidth = std::stoi(match.str(5));
            spriteData.spriteHeight = std::stoi(match.str(6));
            spriteData.nbAnim = std::stoi(match.str(7));
            spriteData.replaceChar[0] = match.str(8).c_str()[0];
            spriteData.replaceChar[1] = match.str(8).c_str()[1];
            spriteData.textColor = std::stoi(match.str(9));
            spriteData.fondColor = std::stoi(match.str(10));

        } catch (std::exception & e) {
            std::cout << "Error on line : " << base << "\n : " << e.what() << std::endl;
        }
        
        map.insert(std::make_pair(spriteData.character, spriteData));
    }
    return map;
}