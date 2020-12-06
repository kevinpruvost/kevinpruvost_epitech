/*
** EPITECH PROJECT, 2020
** Babel server main
** File description:
** Where the program starts
*/

#pragma once

#include "TcpClient.hpp"

#include "Game/EntityInGame/Lib.hpp"

namespace RType {
	namespace Server {
		class Player {
		public:
			static boost::shared_ptr<RType::Server::Player> create(boost::asio::ip::udp::endpoint endpoint) {
				return boost::shared_ptr<RType::Server::Player>(new Player(endpoint));
			}
			Player(const boost::asio::ip::udp::endpoint endpoint);
			~Player();
			void setEndpoint(const boost::asio::ip::udp::endpoint endpoint) { _endpoint = endpoint; }
			boost::asio::ip::udp::endpoint getEndpoint() const { return _endpoint; }
			void setUsername(const std::string& username) { _username = username; }
			std::string getUsername() const { return _username; }
			void setEntId(const unsigned int id) { _entId = id; }
			unsigned int getEntId() const { return _entId; }
			boost::asio::streambuf& getBuffer() { return _buffer; }
			std::mutex& getMutex() { return _mutex; }
			std::vector<unsigned char>& getVecBuffer() { return _vecBuffer; }
			void writeInBuffer(std::vector<unsigned char> datas) { _vecBuffer.insert(_vecBuffer.end(), datas.begin(), datas.end()); }
		private:
			boost::asio::ip::udp::endpoint _endpoint;
			std::string _username;
			boost::asio::streambuf _buffer; //for asynchronous
			std::mutex _mutex;
			std::vector<unsigned char> _vecBuffer; //for synchronous
			unsigned int _entId;
		public:
			std::weak_ptr<Common::Engine::InGamePlayer> _ent;
		};
	}
}