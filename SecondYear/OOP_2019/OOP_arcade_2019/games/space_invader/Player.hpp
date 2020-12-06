/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

// Project includes
#include "Exception.hpp"

// C++ includes
#include <map>
#include <vector>
#include <chrono>

namespace Spaceinvader
{
    class Player;
}

class Spaceinvader::Player {
    public:
        Player(const std::pair<int, int> & pos, std::vector<std::vector<char>> & map);
        ~Player();

        std::pair<int, int> & getPos() { return _pos; };
        std::pair<int, int> & getShootPos() { return _shoot; };
        bool & isPlayerShooting() { return _isShooting; };
        bool & getIsDead () { return _isDead; };
        int & getDirection() { return _direction ;};
        bool & getWantToShoot() { return _wantToShoot;};

        void setLeft();
        void setShoot();
        int shoot(std::vector<std::vector<char>> &);
        void setRight();
        bool testMove(const std::pair<int, int> & pos);
        int moveForward(std::vector<std::vector<char>> & map);
        int move(const std::pair<int, int> & pos);
        int moveLeft();
        int moveRight();

    protected:
    private:
        std::pair<int, int> _pos;
        std::vector<std::vector<char>> & _map;
        int _direction = 0; // 0 1 2 3 : up down left right
        std::pair<int, int> _shoot;
        bool _isDead = false;
        bool _isShooting = false;
        bool _wantToShoot = false;
};

#endif /* !PLAYER_HPP_ */
