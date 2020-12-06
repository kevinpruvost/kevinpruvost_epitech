/*
** EPITECH PROJECT, 2020
** ReadDir.hpp
** File description:
** readdir
*/

#pragma once

// Project includes
#include "Exception.hpp"

// C++ includes
#include <string>
#include <vector>

// C includes
#include <dirent.h>

class ReadDir
{
public:
    ReadDir(const std::string & path);
    ~ReadDir();

    std::vector<std::string> getDirectoryFilenames();
    static std::vector<std::string> getDirectoryFilenames(const std::string & path);

private:
    DIR * dir = nullptr;
    struct dirent * ent = nullptr;

    std::vector<std::string> _fileNames;
};
