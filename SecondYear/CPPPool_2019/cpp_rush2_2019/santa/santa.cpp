#include "santa.hpp"
#include <utility>

santa::santa(std::string filename)
{
    this->buffer = readFile(filename);
}

santa::~santa()
{
}

std::string file_open(char *str)
{
        std::ifstream stream;
        stream.open(str);
        std::string buff;
        std::string line;
        
        while (std::getline(stream, line)) {
                buff+=line;
                // buff.push_back('\n');
        }
        return buff;
}

std::vector<std::string>split(std::string str,char limit)
{
        std::vector<std::string> result;
        std::stringstream stream(str);
        std::string part;
        while(std::getline(stream,part,limit))
                result.push_back(part);
        return result;
}

std::string split2(std::string str,char limit)
{
        std::string result;
        std::stringstream stream(str);
        std::string part;
        while(std::getline(stream,part,limit))
                result += part;
        return result;
}

std::vector<std::string> xml_parser(char *file)
{
        std::string file_str = file_open(file);

        std::regex re("[<>]");
        
        std::sregex_token_iterator first{file_str.begin(), file_str.end(), re, -1}, last;
        
        std::vector<std::string> dtab(first, last);
        for (const std::string &i: dtab)
                std::cout << i << std::endl;
        return dtab;
}

gift::gift()
{
}

gift::~gift()
{
}


void santa::deserialization(char *filename)
{
        this->buffer = readFile(filename);
        std::cout << getInsideRawText("GiftBox");
        
}

std::string santa::readFile(std::string filename)
{
    std::ifstream file(filename);
    std::string final;
    std::string buf;

    if (file.is_open()) {
        while (std::getline(file, buf)) {
            buf.erase(0, buf.find_first_not_of(' '));
            final += buf;
        }
    }
    return (final);
}

std::string santa::getBuffer()
{
    return this->buffer;
}

void santa::setBuffer(std::string nw)
{
    this->buffer = nw;
}

std::string santa::getInsideRawText(const std::string& prop)
{
    size_t first = this->buffer.find("<" + prop + ">");
    size_t last = this->buffer.find("</" + prop + ">");

    if (first > last || first == std::string::npos || last == std::string::npos) {
        return ("");
    }
    return (this->buffer.substr(first + (prop.length() + 2), (last - (first + (prop.length() + 2)))));
}
