/*
** EPITECH PROJECT, 2020
** Babel server main
** File description:
** Where the program starts
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>

//Project's includes
#include "lib/Exception.hpp"
#include "lib/Network/BinaryStructure.hpp"
#include "lib/Network/Rfc.hpp"

namespace RType {
	namespace Server {
		class TcpClientManager;
		class TcpClient : public boost::enable_shared_from_this<TcpClient> {
		public:
			~TcpClient();

			static boost::shared_ptr<TcpClient> create(boost::asio::io_context& io_context, boost::shared_ptr<RType::Server::TcpClientManager> clientManager_ptr);
			boost::asio::ip::tcp::socket& getSocket();

			void waitForDatas();
			void send(void *datas, const size_t size);
		private:
			TcpClient(boost::asio::io_context& io_context, boost::shared_ptr<RType::Server::TcpClientManager> clientManager_ptr);
			void handleRead(const boost::system::error_code& error, std::size_t bytes_transferred);
			void handleSend(std::shared_ptr<void*> ptr, const boost::system::error_code& error, std::size_t bytes_transferred);
		private:
			boost::asio::ip::tcp::socket _socket;
			boost::weak_ptr<RType::Server::TcpClientManager> _clientManager;
			boost::asio::streambuf _readBuffer;
		};
	}
}