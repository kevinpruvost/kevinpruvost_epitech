/*
** EPITECH PROJECT, 2020
** Babel server main
** File description:
** Where the program starts
*/

#include "UdpServer.hpp"
#include "Room.hpp"

RType::Server::UdpServer::UdpServer(boost::asio::io_context& io_context, unsigned short port, Room& room) :
	_socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)),
	_room(room),
	_syncBuffer(1024, 0),
	_emptyBuffer()
{
}

RType::Server::UdpServer::~UdpServer()
{
	std::cout << "Udp server closed." << std::endl;
}

void RType::Server::UdpServer::close()
{
	if (_socket.is_open())
		_socket.close();
}

/**
 * \brief Asyncronous wait for incoming datas
 */
void RType::Server::UdpServer::waitForDatagrams()
{
	boost::asio::streambuf::mutable_buffers_type bufs = _buffer.prepare(512);

	_socket.async_receive_from(bufs, _remoteEndpoint,
		boost::bind(&UdpServer::handleReceive, this,
			boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

/**
 * \brief Handler called when data is received
 */
void RType::Server::UdpServer::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error) {
		std::cout << "Udp server received: " << bytes_transferred << " bytes from " << _remoteEndpoint << std::endl;
		_buffer.commit(bytes_transferred);
		
		boost::shared_ptr<Player> player(_room.getPlayerByEndpoint(_remoteEndpoint));
		size_t bytes_copied;

		if (!player) {
			boost::shared_ptr<Player> newPlayer(new Player(_remoteEndpoint));
			bytes_copied = boost::asio::buffer_copy(newPlayer->getBuffer().prepare(bytes_transferred), _buffer.data());
			newPlayer->getBuffer().commit(bytes_copied);
			_room.addPlayer(newPlayer);
		} else {
			player->getMutex().lock();
			bytes_copied = boost::asio::buffer_copy(player->getBuffer().prepare(bytes_transferred), _buffer.data());
			player->getBuffer().commit(bytes_copied);
			player->getMutex().unlock();
		}
		_buffer.consume(bytes_copied);
		waitForDatagrams();
	}
	else {
		std::cerr << "Error while reading from the client. (" << error.message() << ")" << std::endl;
	}
}

/**
 * \brief Send datas to the client
 * \param datas
 * \param size of the data
 * \param ip
 * \param port
 */
void RType::Server::UdpServer::sendDatagram(const void* datas, size_t size, const std::string& ip, const unsigned short port)
{
	boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string(ip), port);

	std::shared_ptr<const void*> datas_ptr = std::make_shared<const void*>(datas);

	_socket.async_send_to(boost::asio::buffer(*datas_ptr, size), endpoint,
		boost::bind(&UdpServer::handleSend, this, datas_ptr, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

/**
 * \brief Send datas to the client
 * \param datas
 * \param size of the data
 * \param boost asio endpoint
 */
void RType::Server::UdpServer::sendDatagram(const void* datas, size_t size, boost::asio::ip::udp::endpoint endpoint)
{
	//size_t len = _socket.send_to(boost::asio::buffer(datas, size), endpoint);
	//std::cout << "Successully tansfered: " << len << " bytes." << std::endl;
	std::shared_ptr<const void*> datas_ptr = std::make_shared<const void*>(datas);

	_socket.async_send_to(boost::asio::buffer(*datas_ptr, size), endpoint,
		boost::bind(&UdpServer::handleSend, this, datas_ptr, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

/**
 * \brief Handler called once the data is sent
 */
void RType::Server::UdpServer::handleSend(std::shared_ptr<const void*> ptr, const boost::system::error_code& error, const std::size_t bytes_transferred)
{
	if (!error) {
		std::cout << "Successfully transfered " << bytes_transferred << std::endl;
	}
	else {
		std::cerr << "Error while sending data." << std::endl;
	}
}

/**
 * \brief Receive data synchronously
 * \return vector<char> of datas wich is empty if there is nothing to read
 */
std::pair<std::vector<unsigned char>, boost::asio::ip::udp::endpoint> RType::Server::UdpServer::receiveDatas()
{
	//std::vector<unsigned char> buffer(BUFFER_SIZE, 0);
	//boost::asio::ip::udp::endpoint remoteEndpoint;

	_syncBuffer.resize(BUFFER_SIZE);
	if (_socket.available() > 0) {
		size_t len = _socket.receive_from(boost::asio::buffer(_syncBuffer, _syncBuffer.size()), _remoteEndpoint);
		_syncBuffer.resize(len);
	} else {
		//buffer.resize(0);
		return std::make_pair(_emptyBuffer, _remoteEndpoint);
	}
	return std::make_pair(_syncBuffer, _remoteEndpoint);
}