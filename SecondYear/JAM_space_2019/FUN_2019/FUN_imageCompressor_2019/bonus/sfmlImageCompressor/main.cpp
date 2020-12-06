/*
** EPITECH PROJECT, 2020
** FUN_imageCompressor_2019
** File description:
** main
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <vector>

#include <SFML/Graphics.hpp>


#include <sstream> 
  
std::vector<int> extractIntegerWords(std::string str) 
{ 
    std::stringstream ss;
    std::vector<int> ret;
  
    /* Storing the whole string into string stream */
    ss << str; 
  
    /* Running loop till the end of the stream */
    std::string temp; 
    int found; 
    while (!ss.eof()) { 
  
        /* extracting word by word from stream */
        ss >> temp; 
  
        /* Checking the given word is integer or not */
        if (std::stringstream(temp) >> found) 
            ret.push_back(found);
  
        /* To save from space at the end of string */
        temp = ""; 
    }
    return (ret);
} 
  

/*    ./../../imageCompressor 2 0.8 ../test0 | ./sfmlImageCompressor    */

void readImage(std::string filepath)
{
    std::ofstream myfile("resultRead.txt");
    sf::Image img;

    if (!myfile.is_open()) {
        std::cerr << "Error while opening file" << std::endl;
        return;
    }
    if (!img.loadFromFile(filepath)) {
        std::cerr << "Error while opening image" << std::endl;
        return;
    }
    sf::Vector2u size = img.getSize();

    for (unsigned int y = 0; y < size.y; y++) {
        for (unsigned int x = 0; x < size.x; x++) {
            sf::Color color = img.getPixel(x, y);
            myfile << "(" << x << "," << y << ") (" << (int) color.r << "," << (int) color.g << "," << (int) color.b << ")\n";
        }
    }
    myfile.close();
}

void writeImage(std::string filepath, sf::Vector2u imageSize)
{
    sf::Image img;
    std::smatch match;
    sf::Color color = sf::Color::Red;
    std::string new_line;
    std::vector<int> res;

    img.create(imageSize.x, imageSize.y, sf::Color::Black);

    std::cout << "Reading pixels" << std::endl;
    for (std::string line; std::getline(std::cin, line);) {
        std::cout << "Parsing: '" + line << "'" << std::endl;

        std::regex_search(line, match, (std::regex)"^\\(\\d+,\\d+,\\d+\\)$");
        if (match.size() > 0) {
            res = extractIntegerWords(std::regex_replace(std::regex_replace(line, (std::regex)"\\(|\\)", ""), (std::regex)",", " "));
            if (res.size() > 2) {
                color = sf::Color(res[0], res[1], res[2]);
            }
            continue;
        }
        std::regex_search(line, match, (std::regex)"^\\(\\d+,\\d+\\) \\(\\d+,\\d+,\\d+\\)$");
        if (match.size() > 0) {
            res = extractIntegerWords(std::regex_replace(std::regex_replace(line, (std::regex)"\\(|\\)", ""), (std::regex)",", " "));
            if (res.size() > 1) {
                if (res[0] > (int) imageSize.x || res[1] > (int) imageSize.y) {
                    std::cerr << "Error wrong image size given as argument" << std::endl;
                    break;
                }
                img.setPixel(res[0], res[1], color);
            }
        }
    }
    std::cout << "Complete" << std::endl;
    std::cout << "Saving..." << std::endl;
    if (!img.saveToFile(filepath)) {
        std::cerr << "Error while saving image" << std::endl;
        return;
    }
    std::cout << "Complete" << std::endl;
}

int main(int ac, char **av)
{
    if (ac < 3 || 5 < ac) {
        std::cerr << "Usage: ./sfmlImageCompressor filepath read/write [width] [height]" << std::endl;
        return (84);
    }
    if (std::string(av[2]) == "read") {
        readImage(std::string(av[1]));
    } else if (std::string(av[2]) == "write") {
        writeImage(std::string(av[1]), sf::Vector2u(std::stoi(std::string(av[3])),std::stoi(std::string(av[4]))));
    } else {
        std::cerr << "Error. Please use read or write" << std::endl;
        return (84);
    }
    return 0;
}