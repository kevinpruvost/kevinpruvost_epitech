/*
** EPITECH PROJECT, 2020
** Babel server client
** File description:
**
*/

#include "BabelClient.hpp"

Babel::Server::BabelClient::BabelClient(boost::asio::io_context& io_context,
    boost::shared_ptr<Babel::Server::ClientManager> clientManager_ptr) :
    _socket(io_context),
    _clientManager_ptr(clientManager_ptr),
    _state(Babel::Rfc::State::Connected),
    _packetSender()
{
}

Babel::Server::BabelClient::~BabelClient()
{
}

/**
 * \brief Create a shared pointer to a BabelClient object
 * \return Shared pointer to BabelClient
 */
boost::shared_ptr<Babel::Server::BabelClient> Babel::Server::BabelClient::create(boost::asio::io_context& io_context,
    boost::shared_ptr<Babel::Server::ClientManager> clientManager_ptr)
{
    return boost::shared_ptr<BabelClient>(new BabelClient(io_context, clientManager_ptr));
}

/**
 * \brief Return the client's socket
 * \return Tcp socket
 */
boost::asio::ip::tcp::socket& Babel::Server::BabelClient::getSocket()
{
    return (_socket);
}

/**
 * \brief Start an asynchronous read
 */
void Babel::Server::BabelClient::waitForDatas()
{
    std::cout << "Waiting for datas" << std::endl;

    /*boost::asio::async_read_until(_socket, _readBuffer, "\r\n",
        boost::bind(&BabelClient::handleRead, shared_from_this(),
        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));*/
    boost::asio::async_read(_socket, _readBuffer, boost::asio::transfer_at_least(Babel::Common::PacketsDataBinary::PacketsDataBinarySerializedMinimumSize),
        boost::bind(&BabelClient::handleRead, shared_from_this(),
        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

/**
 * \brief This function is called when there is something to read
 * \param boost error code
 * \param size_t Number of bytes transfered
 */
void Babel::Server::BabelClient::handleRead(const boost::system::error_code& error, size_t bytes_transferred)
{
    boost::shared_ptr<ClientManager> clientManager = _clientManager_ptr.lock();

    if (clientManager) {
        if (!error) {
            boost::asio::const_buffer rawBytesBuffer = _readBuffer.data();
            try {
                Babel::Common::PacketsDataBinary packet = Babel::Common::PacketsDataBinary::deserializeData((void*)rawBytesBuffer.data(), bytes_transferred);
                _readBuffer.consume(packet.getBytesSize());
                clientManager->manageCommand(shared_from_this(), packet);
                waitForDatas();
            }
            catch (std::exception& e) {
                std::cerr << "Error while desarialising packet: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Closing connection with the client" << std::endl;
            clientManager->disconnect(shared_from_this());
        }
    }
}

/**
 * \brief Send packet on the socket
 * \param RFC code
 * \param Vector of arguments
 */
void Babel::Server::BabelClient::send(const Babel::Rfc::Code code, const std::vector<std::string>& arguments)
{
    Babel::Common::PacketsDataBinary newPacket(code, arguments);

    _packetSender = newPacket.serializeData();

    boost::asio::async_write(_socket, boost::asio::buffer((void*)&_packetSender, _packetSender.size),
        boost::bind(&BabelClient::handleWrite, shared_from_this(),
        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

/**
 * \brief Handle for called when write process is finished
 * \param boost error code
 * \param size_t Number of bytes transfered
 */
void Babel::Server::BabelClient::handleWrite(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
        std::cout << bytes_transferred << " bytes has been transfered successfully !" << std::endl;
    else
        std::cerr << "Something went wrong when sending to the client." << std::endl;
}