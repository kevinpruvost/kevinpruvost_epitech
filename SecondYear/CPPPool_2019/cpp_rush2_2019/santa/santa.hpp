#pragma once


#include<cstdlib>
#include<string>
#include<iostream>
#include<fstream>
#include<ctime>
#include<vector>
#include<sstream>
#include<regex>

class santa
{
public:
        santa(std::string filename);
        ~santa();
        void deserialization(char *str);
        std::string getInsideRawText(const std::string& prop);
        std::string getBuffer();
        void setBuffer(std::string nw);
        std::string readFile(std::string filename);
        
private:
        std::string buffer;
};

class gift
{
public:
        gift();
        ~gift();
        
private:
        
};
