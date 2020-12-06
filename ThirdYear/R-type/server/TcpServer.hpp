/*
** EPITECH PROJECT, 2020
** Babel server main
** File description:
** Where the program starts
*/

#pragma once

#include "TcpClientManager.hpp"

namespace RType {
	namespace Server {
		class TcpServer {
		public:
			TcpServer(boost::asio::io_context& io_context, unsigned short port);
			~TcpServer();
			void startAccept();
		private:
			void handleAccept(boost::shared_ptr<TcpClient> newClient, const boost::system::error_code& error);
		private:
			boost::asio::io_context& _IOcontext;
			boost::asio::ip::tcp::acceptor _acceptor;
			boost::asio::signal_set _signals;
			boost::shared_ptr<TcpClientManager> _clientManager;
		};
	}
}