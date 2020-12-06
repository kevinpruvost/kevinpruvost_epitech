/*
** EPITECH PROJECT, 2020
** Babel server main
** File description:
** Where the program starts
*/

#include "TcpServer.hpp"

RType::Server::TcpServer::TcpServer(boost::asio::io_context& io_context, unsigned short port) :
	_IOcontext(io_context),
	_acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
	_clientManager(new TcpClientManager(io_context)),
	_signals(io_context, SIGINT, SIGTERM)
{
	_signals.async_wait([this](const boost::system::error_code& ec, int code)
	{
		(void)ec;
		(void)code;
		_IOcontext.stop();
	});
}

RType::Server::TcpServer::~TcpServer()
{
	//todo
}

/**
 * \brief Start accepting new connections
 */
void RType::Server::TcpServer::startAccept()
{
	std::cout << "Accepting client on port: " << _acceptor.local_endpoint().port() << std::endl;
	
	boost::shared_ptr<TcpClient> newClient = TcpClient::create(_IOcontext, _clientManager);

	_acceptor.async_accept(newClient->getSocket(),
		boost::bind(&TcpServer::handleAccept, this, newClient,
			boost::asio::placeholders::error));
}

/**
 * \brief Handler called on new connection
 * \param shared pointer to managing new client
 * \param error object
 */
void RType::Server::TcpServer::handleAccept(boost::shared_ptr<TcpClient> newClient, const boost::system::error_code& error)
{
	if (!error) {
		std::cout << "Received new connection" << std::endl;
		_clientManager->addClient(newClient);
		newClient->waitForDatas();
		startAccept();
	} else {
		std::cerr << "Error accepting clients" << std::endl;
	}
}