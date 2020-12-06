/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Bridge
*/

#ifndef BRIDGE_HPP_
#define BRIDGE_HPP_

// Projet includes
#include "Exception.hpp"

// C++ includes
#include <vector>

namespace Spaceinvader
{
    class Bridge;
}

class Spaceinvader::Bridge {
    public:
        Bridge(const std::pair<int, int> & pos, std::vector<std::vector<char>> & map);
        ~Bridge();
        std::pair<int, int> & getPos() { return _pos;};
        bool & getIsDead() { return isDead; };
    private:
        std::pair<int, int> _pos;
        std::vector<std::vector<char>> _map;
        bool isDead = false;
};

#endif /* !BRIDGE_HPP_ */
