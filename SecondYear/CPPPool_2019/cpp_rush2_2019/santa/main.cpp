/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** Temp
*/

#include <vector>
#include <Object.hpp>
#include <GiftPaper.hpp>
#include <LittlePony.hpp>
#include <Teddy.hpp>
#include <Box.hpp>
#include "santa.hpp"


int main(int ac, char **av)
{
    std::string type;
    std::string name;
    std::vector<Object *> gifts;
    bool is_in_box = false;

    for (int i = 1; i < ac; i++) {
        santa lol(av[i]);
        lol.setBuffer(lol.getInsideRawText("GiftPaper"));
        if (lol.getBuffer().substr(1, lol.getBuffer().find('>', 1) - 1) != "Box") {
            is_in_box = false;
            GiftPaper elem;
            type = lol.getBuffer().substr(1, lol.getBuffer().find('>', 1) - 1);
            name = lol.getInsideRawText("name");
            if (type == "LittlePony") {
                LittlePony item(name);
                elem.wrapMeThat(&item);
            }
            if (type == "Teddy") {
                Teddy item(name);
                elem.wrapMeThat(&item);
            }
            gifts.push_back(&elem);
        }
        else {
            is_in_box = true;
            lol.setBuffer(lol.getInsideRawText("Box"));
            type = lol.getBuffer().substr(1, lol.getBuffer().find('>', 1) - 1);
            name = lol.getInsideRawText("name");
            GiftPaper elem;
            Box box;
            if (type == "LittlePony") {
                LittlePony item(name);
                box.wrapMeThat(&item);
            }
            if (type == "Teddy") {
                Teddy item(name);
                box.wrapMeThat(&item);
            }
            elem.wrapMeThat(&box);
            gifts.push_back(&elem);
        }
        // DEBUG PRINTING
        // std::cout << "[" << type << " - " << name << " -> " << is_in_box << "]" << std::endl;
        // UNCOMMENT THIS AS NEEDED
    }
}
