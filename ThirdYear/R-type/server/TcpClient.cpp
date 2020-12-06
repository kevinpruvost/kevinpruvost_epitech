/*
** EPITECH PROJECT, 2020
** Babel server main
** File description:
** Where the program starts
*/

#include "TcpClient.hpp"
#include "TcpClientManager.hpp"
#include "Room.hpp"

RType::Server::TcpClient::TcpClient(boost::asio::io_context& io_context, boost::shared_ptr<RType::Server::TcpClientManager> clientManager_ptr) :
	_socket(io_context),
	_clientManager(clientManager_ptr)
{
	//todo
}

RType::Server::TcpClient::~TcpClient()
{
	//todo
}

/**
 * \brief Create a shared pointer to the TCP client
 * \param io_context
 * \param shared pointer to the Client Manager
 * \return Shared pointer to the new Client
 */
boost::shared_ptr<RType::Server::TcpClient> RType::Server::TcpClient::create(boost::asio::io_context& io_context, boost::shared_ptr<RType::Server::TcpClientManager> clientManager_ptr)
{
	return (boost::shared_ptr<TcpClient>(new TcpClient(io_context, clientManager_ptr)));
}

/**
 * \brief Get the clients socket
 * \return tcp socket
 */
boost::asio::ip::tcp::socket& RType::Server::TcpClient::getSocket()
{
	return (_socket);
}

/**
 * \brief Tell the client to wait for datas
 */
void RType::Server::TcpClient::waitForDatas()
{
	std::cout << "Waiting for datas" << std::endl;

	boost::asio::async_read(_socket, _readBuffer, boost::asio::transfer_at_least(sizeof(Common::Tcp::Header)),
		boost::bind(&TcpClient::handleRead, shared_from_this(),
			boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

/**
 * \brief Handler called when datas is received
 */
void RType::Server::TcpClient::handleRead(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	(void)bytes_transferred;
	boost::shared_ptr<TcpClientManager> clientManager = _clientManager.lock();

	if (!clientManager) {
		std::cout << "Something went wrong while accessing clientManager." << std::endl;
		return;
	}
	if (!error) {
		if (_readBuffer.size() < sizeof(Common::Tcp::Header)) {
			std::cerr << "Error while retrieving header" << std::endl;
			waitForDatas();
			return;
		}
		const Common::Tcp::Header* header = static_cast<const Common::Tcp::Header*>(_readBuffer.data().data());
		std::cout << "Received header of size: " << header->size << std::endl;
		if (_readBuffer.size() < header->size) {
			std::cerr << "Struct not complete" << std::endl;
			waitForDatas();
			return;
		}
		clientManager->manageHeader(shared_from_this(), header);
		_readBuffer.consume(header->size);
		waitForDatas();
	} else {
		std::cerr << "Seems like something went wrong with the client. (Probably just disconnected)" << std::endl;
	}
}

/**
 * \brief Send datas as void *
 * \param datas
 * \param size of given datas
 */
void RType::Server::TcpClient::send(void *datas, const size_t size)
{
	std::shared_ptr<void *> test = std::make_shared<void *>(datas);

	boost::asio::async_write(_socket, boost::asio::buffer(*test, size), boost::bind(&TcpClient::handleSend, shared_from_this(),
		test, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

/**
 * \brief Handler called when datas is completely sent
 * \param ptr to the sent data
 * \param Boost error object
 * \param Number of bytes transfered
 */
void RType::Server::TcpClient::handleSend(std::shared_ptr<void*> ptr, const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error)
		std::cout << "Successfully sent " << bytes_transferred << " bytes" << std::endl;
	else
		std::cerr << "Error while sending message to client." << std::endl;
}