/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Ennemy
*/

#ifndef ENNEMY_HPP_
#define ENNEMY_HPP_

// Project includes
#include "Exception.hpp"

// C++ includes
#include <vector>

#define MAP_HEIGHT 30
#define INVADERRIGHT 0
#define INVADERLEFT 1

namespace Spaceinvader {
    class Ennemy;
}

class Spaceinvader::Ennemy {
    public:
        Ennemy(const std::pair<int, int> & pos, std::vector<std::vector<char>> & map);
        ~Ennemy();
        void setDirection(int direc) {_direction = direc;};
        void setIsDead() {isDead = !isDead;};
        bool & getIsDead() {return isDead;};
        int update(std::vector<std::vector<char>> & map, int &);
        int & getDirection() { return _direction;};
        int move(std::vector<std::vector<char>> & map);
        int reduceHeight(std::vector<std::vector<char>> &);
        int shoot(std::vector<std::vector<char>> &);
        bool & getIsShooting() { return _isShooting; };
        bool canIShoot(std::vector<std::vector<char>> &);
        std::pair<int, int> & getShootPos() { return _shoot;};
        std::pair<int, int> & getPos() {return _pos;};

    private:
        std::pair<int, int> _pos;
        std::vector<std::vector<char>> _map;
        bool _isShooting = false;
        int _direction;
        bool isDead;
        std::pair<int, int> _shoot;
};

#endif /* !ENNEMY_HPP_ */
