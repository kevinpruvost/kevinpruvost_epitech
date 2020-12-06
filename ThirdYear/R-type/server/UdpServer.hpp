/*
** EPITECH PROJECT, 2020
** Babel server main
** File description:
** Where the program starts
*/

#pragma once

#include "Player.hpp"

#define BUFFER_SIZE 512

namespace RType {
	namespace Server {
		class Room;
		class UdpServer {
		public:
			UdpServer(boost::asio::io_context& io_context, unsigned short port, Room& room);
			~UdpServer();

			void waitForDatagrams();
			void sendDatagram(const void *datas, size_t size, const std::string& ip, const unsigned short port);
			void sendDatagram(const void* datas, size_t size, boost::asio::ip::udp::endpoint endpoint);

			std::string getIp() const { return _socket.local_endpoint().address().to_string(); }
			unsigned short getPort() const { return _socket.local_endpoint().port(); }

			void close();

			std::pair<std::vector<unsigned char>, boost::asio::ip::udp::endpoint> receiveDatas();
		private:
			void handleReceive(const boost::system::error_code& error, const std::size_t bytes_transferred);
			void handleSend(std::shared_ptr<const void*> ptr, const boost::system::error_code& error, const std::size_t bytes_transferred);
		private:
			boost::asio::ip::udp::socket _socket;
			boost::asio::streambuf _buffer;
			boost::asio::ip::udp::endpoint _remoteEndpoint;
			Room& _room;
			std::vector<unsigned char> _syncBuffer;
			std::vector<unsigned char> _emptyBuffer;
		};
	}
}