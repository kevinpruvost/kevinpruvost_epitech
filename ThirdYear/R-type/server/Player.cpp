/*
** EPITECH PROJECT, 2020
** Babel server main
** File description:
** Where the program starts
*/

#include "Player.hpp"

RType::Server::Player::Player(const boost::asio::ip::udp::endpoint endpoint) : _endpoint(endpoint), _entId(0)
{
	//todo
}

RType::Server::Player::~Player()
{
	//todo
}

//all getters & setters are in the hpp