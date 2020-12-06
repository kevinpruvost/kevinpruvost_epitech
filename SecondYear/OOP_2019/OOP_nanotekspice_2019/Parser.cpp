/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Parser.hpp"

#include <iostream>

using namespace nts;

bool lineisEmpty(const std::string & line)
{
    if (line.empty())
        return true;
    for (size_t i = 0; i < line.size(); ++i)
        if (line[i] != '\0' && line[i] != '\n' && line[i] != ' ')
            return false;
    return true;
}

bool mystrcmp(const std::string & str1, const std::string & str2)
{
    for (size_t i = 0; i < str2.size(); ++i)
        if (str2[i] != str1[i])
            return false;
    return true;
}

std::string deleteCommentary(std::string & fileContent)
{
    std::string newFileContent;

    for (size_t i = 0; i < fileContent.size(); ++i) {
        if (fileContent[i] == '#')
            while (fileContent[i] != '\n' && i < fileContent.size())
                ++i;
        newFileContent += fileContent[i];
    }
    return newFileContent;
}

bool lineIsFalse(std::string & line)
{
    int countSpace = 0;
    size_t pos = 0;
    std::string save = line;
    std::string token;
    std::string delimiter = " ";

    for (size_t i = 0; i < line.size(); ++i)
        if (line[i] != '\0' && line[i] != '\n' && line[i] != ' ')
            pos = 1;
    if (pos == 0)
        return false;
    pos = 0;
    while ((pos = save.find(delimiter)) != std::string::npos) {
        token = save.substr(0, pos);
        save.erase(0, pos + delimiter.length());
        ++countSpace;
    }
    if (countSpace != 2)
        return true;
    return false;
}

std::string firstArg(std::string & line)
{
    size_t pos = 0;
    std::string token;
    std::string delimiter = " ";
    std::string save = line;
    pos = save.find(delimiter);
    token = save.substr(0, pos);
    return token;
}

std::string secondArg(std::string & line)
{
    size_t pos = 0;
    std::string save = line;
    std::string token;
    std::string delimiter = " ";
    while ((pos = save.find(delimiter)) != std::string::npos) {
        token = save.substr(0, pos);
        save.erase(0, pos + delimiter.length());
    }
    return token;
}

bool Parser::verifyChipsetsIsFalse(std::string &fileContent)
{
    std::string save = fileContent;
    size_t pos = 0;
    std::string token;
    std::string delimiter = "\n";

    while ((pos = save.find(delimiter)) != std::string::npos) {
        token = save.substr(0, pos);
        if (mystrcmp(token, ".links:"))
            break;
        if (!lineisEmpty(token) && token.back() != ' ')
            token += " ";
        if (!mystrcmp(token, ".chipsets:")) {
            if (lineIsFalse(token)) {
                return true;
            }
            if (!lineisEmpty(token))
                if (!_circuit.addComponent(firstArg(token), secondArg(token)))
                    return true;
        }
        save.erase(0, pos + delimiter.length());
    }
    return false;
}

bool verifyLinksAndChipsetsIntegrity(std::string &fileContent)
{
    int numberLink = 0;
    int numberChipset = 0;
    std::string save = fileContent;
    size_t pos = 0;
    std::string token;
    std::string delimiter = "\n";
    while ((pos = save.find(delimiter)) != std::string::npos) {
        token = save.substr(0, pos);
        if (mystrcmp(token, ".links:"))
            ++numberLink;
        if (mystrcmp(token, ".chipsets:"))
            ++numberChipset;
        if (token[0] == '.' && (!mystrcmp(token, ".links:") && !mystrcmp(token, ".chipsets:"))) {
            return true;
        }
        save.erase(0, pos + delimiter.length());
    }
    if (numberChipset != 1 || numberLink != 1)
        return true;
    return false;
}

std::string delete_all_space(std::string & fileContent)
{
    std::vector<std::string> array;
    std::string save;
    std::string keep;
    size_t loop;

    for (size_t i = 0; i < fileContent.size(); ++i) {
        if (fileContent[i] == '\n' && !save.empty()) {
            for (size_t k = 0; (k < save.size() && save[k] == ' ') || (k < save.size() && save[k] == '\t'); ++k)
                save.erase(k, 1);
            for (size_t k = save.size()-1; (k < save.size() && save[k] == ' ') || (k < save.size() && save[k] == '\t'); --k)
                save.erase(k, 1);
            for (loop = 0; loop != save.size() && save[loop] != ' ' && save[loop] != '\t'; ++loop)
                keep += save[loop];
            keep += ' ';
            for (; (loop != save.size() && save[loop] == ' ') || (loop != save.size() && save[loop] == '\t'); ++loop);
            for (; loop != save.size() && save[loop] != ' ' && save[loop] != '\t'; ++loop)
                keep += save[loop];
            if (array.empty())
                array.push_back(keep);
            else
                array.insert(array.begin(), keep);
            keep.clear();
            save.clear();
        }
        while (fileContent[i] == '\n' && i < fileContent.size())++i;
        if (fileContent[i] != '\n' && i < fileContent.size())
            save += fileContent[i];
    }
    if (!save.empty())
        array.insert(array.begin(), save);
    save.clear();
    for (auto & j : array)
    {
        (void)j;
        save += array.back();
        array.pop_back();
        save += '\n';
    }
    return save;
}

std::string regexFinder(std::string & line, std::regex expression, int group)
{
    std::smatch match;
    if (std::regex_search(line, match, expression)) {
        return match.str(group);
    }
    return nullptr;
}

std::string firstLink(std::string & line)
{
    std::string save;
    for (size_t i = 0; i < line.size() && line[i] != ':'; ++i)
        save += line[i];

    return save;
}

int secondLink(std::string & line)
{
    std::string save;
    size_t i = 0;
    for (; i < line.size() && line[i] != ':'; ++i);
    ++i;
    for (; i < line.size() && (line[i] != ' ' && line[i] != '\t'); ++i)
        save += line[i];
    return std::stoi(save);
}

std::string thirdLink(std::string & line)
{
    std::string save;
    size_t i = 0;
    for (; i < line.size() && line[i] != ':'; ++i);
    ++i;
    for (; i < line.size() && (line[i] != ' ' && line[i] != '\t'); ++i);
    for (; i < line.size() && (line[i] == ' ' || line[i] == '\t'); ++i);
    for (; i < line.size() && line[i] != ':'; ++i)
        save += line[i];

    return save;
}

int fourLink(std::string & line)
{
    std::string save;
    size_t i = 0;
    for (; i < line.size() && line[i] != ':'; ++i);
    ++i;
    for (; i < line.size() && (line[i] != ' ' && line[i] != '\t'); ++i);
    for (; i < line.size() && line[i] != ':'; ++i);
    if (line[i] == ':')
        ++i;
    for (; i < line.size() && line[i] != '\n'; ++i)
        save += line[i];
    return std::stoi(save);
}

bool Parser::verifyLinksIsFalse(std::string & fileContent)
{
    std::string save = fileContent;
    std::string token;
    std::string delimiter = "\n";
    /*std::vector<std::regex> yo = {std::regex {(R"(^\w+)(?:\:)")},
                                  std::regex {(R"(?:[\:])([^\ ]*)")},
                                  std::regex {(R"(?:\ )([^\:]*)")},
                                  std::regex {(R"(?:[\:])([^\ ]*)")}};
                                  "(\\w+):(\\d+)\\s+(\\w+):(\\d+)"*/
    bool go = false;
    for (size_t i = 0; i < fileContent.size(); ++i) {
        token.clear();
        for (;fileContent[i] != '\n' && fileContent[i+1] != '\0'; ++i)
            token += fileContent[i];
        if (go) {
            _circuit.addLink(firstLink(token), secondLink(token), thirdLink(token), fourLink(token));
        }
        if (mystrcmp(token, ".links:"))
            go = true;
    }
    return false;
}


bool Parser::exec()
{
    std::ifstream myfile(filename);
    std::string fileContent;

    if (!myfile.is_open()) {
        throw EXCEPTION("Cannot open '" + filename + "'.");
        return false;
    }

    std::getline(myfile, fileContent, '\0');
    fileContent = deleteCommentary(fileContent);
    fileContent = delete_all_space(fileContent);
    if (verifyLinksAndChipsetsIntegrity(fileContent))
        throw EXCEPTION("Issue with Links and Chipsets integrity in file '" + filename + "'.");
    if (verifyChipsetsIsFalse(fileContent))
        throw EXCEPTION("Input issue in file '"+ filename + "'.");
    if (verifyLinksIsFalse(fileContent))
        throw EXCEPTION("Link issue in file '"+ filename + "'.");
    if (!_circuit.verifyLinks())
        return false;
    return true;
}

Parser::Parser(const char * fn, Circuit & circuit)
    : filename { fn }
    , _circuit { circuit }
{
}

bool Parser::parse()
{
    bool ret = true;
    try {
        ret = exec();
    } catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
        ret = false;
    }
    return ret;
}
