/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** ClientUDP
*/

#include "ClientUDP.hpp"

using namespace RType::Common::Client;

ClientUDP::ClientUDP(boost::asio::io_context & context, const std::string & ip)
    : __socket ( context )
    , __data (NULL)
    , __read (0)
    , __ip (ip)
    , __isSet (false)
{
}

ClientUDP::~ClientUDP()
{
    __socket.close();
}

void ClientUDP::setCallbackError(const std::function<void()> & error)
{
    __callBackError = error;
}

void ClientUDP::bindSocket(unsigned short port)
{
    boost::asio::ip::udp::endpoint __endpoint(boost::asio::ip::address_v4::from_string(__ip), port);    

    __socket.connect(__endpoint);

    __isSet = true;

    readData();
}

bool ClientUDP::sendData(const void * data, size_t size)
{
    boost::system::error_code error;
    if (__isSet)
        __socket.send(boost::asio::buffer(data, size), 0, error);
    return !error;
}

void ClientUDP::getCallbackData(const std::function<void(void *, size_t)> &callbackFunction)
{
    __callbackFunction = callbackFunction;
}

void ClientUDP::call(boost::shared_ptr<std::vector<char>> & c, boost::system::error_code code, size_t read)
{
    __read = read;
    if (code) {
        std::cout << "code :  ntm " << code.message() << std::endl;
        if (boost::asio::error::eof == code && __callBackError)
            __callBackError();
        return;
    }
    __data = c->data();
    //std::cout.write(c->data(), read) << std::endl;
    if (__callbackFunction)
        __callbackFunction(c->data(), read);
    c->clear();
    __data = NULL;
    readData();
}

void ClientUDP::readData()
{    
    boost::shared_ptr<std::vector<char>> c(new std::vector<char>(1024));
    __socket.async_receive(boost::asio::buffer(*c, c->size()), \
boost::bind(&ClientUDP::call, this, c, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}
