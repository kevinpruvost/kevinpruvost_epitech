/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/30
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "BF_Translator.hpp"

BF_Translator::BF_Translator()
{
}

bool writeContent(std::string & out, std::string & in)
{
    for (size_t i = 0; i < in.size(); ++i)
    {
        switch (in[i])
        {
            case '>':
                out += "++ptr;";
                break;
            case '<':
                out += "--ptr;";
                break;
            case '+':
                out += "++*ptr;";
                break;
            case '-':
                out += "--*ptr;";
                break;
            case '.':
                out += "putchar(*ptr);";
                break;
            case ',':
                out += "*ptr=getchar();";
                break;
            case '[':
                out += "while(*ptr){";
                break;
            case ']':
                out += "}";
                break;
            case ' ':
                break;
            case '\n':
                break;
            case '\t':
                break;
            case '\r':
                break;
            default:
                return false;
        }
    }
    return true;
}

int BF_Translator::translate(const std::string & in, const std::string & out)
{
    std::ifstream instream(in);

    std::string incontent;

    std::getline(instream, incontent, '\0');

    std::string outContent("#include <stdio.h>\nint main(void){char array[30000] = {0};char *ptr = array;");

    if (!writeContent(outContent, incontent))
        return EXIT_FAILURE;

    outContent += "}";

    std::ofstream of(out);

    of.write(outContent.c_str(), outContent.size());

    return EXIT_SUCCESS;
}
