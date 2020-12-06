/*
** EPITECH PROJECT, 2020
** ReadDir.cpp
** File description:
** readdir
*/

#include "ReadDir.hpp"

ReadDir::ReadDir(const std::string & path)
{
    if ((dir = opendir(path.c_str())) == NULL)
    {
        throw EXCEPTION("Cannot open '" + path + "' directory.");
    }

    while ((ent = readdir(dir)) != NULL)
        _fileNames.push_back(ent->d_name);
}

std::vector<std::string> ReadDir::getDirectoryFilenames()
{
    return _fileNames;
}

std::vector<std::string> ReadDir::getDirectoryFilenames(const std::string & path)
{
    std::vector<std::string> fileNames;
    DIR * sdir = nullptr;
    struct dirent * sent = nullptr;

    if ((sdir = opendir(path.c_str())) == NULL)
    {
        throw EXCEPTION("Cannot open '" + path + "' directory.");
        return fileNames;
    }

    while ((sent = readdir(sdir)) != NULL)
        fileNames.push_back(sent->d_name);
    
    closedir(sdir);
    return fileNames;
}

ReadDir::~ReadDir()
{
    closedir(dir);
}
