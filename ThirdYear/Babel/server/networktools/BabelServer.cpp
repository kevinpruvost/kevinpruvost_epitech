/*
** EPITECH PROJECT, 2020
** Babel server
** File description:
**
*/

#include "BabelServer.hpp"

Babel::Server::BabelServer::BabelServer(boost::asio::io_context& io_context, unsigned int port) :
	_IOcontext(io_context),
	_acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
	_clientManager_ptr(new ClientManager()),
	_signals(io_context, SIGINT, SIGTERM)
{
	startAccept();
	_signals.async_wait([this](const boost::system::error_code& ec, int code)
	{
		_IOcontext.stop();
	});
}

Babel::Server::BabelServer::BabelServer(boost::asio::io_context& io_context, const std::string & internalPublicIpAddress, unsigned int port) :
	_IOcontext(io_context),
	_acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(internalPublicIpAddress), port)),
	_clientManager_ptr(new ClientManager()),
	_signals(io_context, SIGINT, SIGTERM)
{
	startAccept();
	_signals.async_wait([this](const boost::system::error_code& ec, int code)
	{
		_IOcontext.stop();
	});
}

Babel::Server::BabelServer::~BabelServer()
{
}

/**
 * \brief Start accepting sockets
 */
void Babel::Server::BabelServer::startAccept()
{
	boost::shared_ptr<BabelClient> newClient = BabelClient::create(_IOcontext, _clientManager_ptr);

	_acceptor.async_accept(newClient->getSocket(),
		boost::bind(&BabelServer::handleAccept, this, newClient,
			boost::asio::placeholders::error));
}

/**
 * \brief Handler called every time a socket connect to the server
 */
void Babel::Server::BabelServer::handleAccept(boost::shared_ptr<BabelClient> newClient, const boost::system::error_code& error)
{
	if (!error) {
		std::cout << "New client!" << std::endl;
		_clientManager_ptr->connect(newClient);
		newClient->waitForDatas();
		startAccept();
	}
	else {
		std::cerr << "Accept failed: " << error.message() << std::endl;
	}
}