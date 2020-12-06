/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** ClientTCP
*/

#include "ClientTCP.hpp"

using namespace RType::Common::Client;

ClientTCP::ClientTCP(boost::asio::io_context & context, const std::string & ip, unsigned short port)
    : __socket (context)
{
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::from_string(ip), port);
    boost::system::error_code errorCode;

    __socket.connect(endpoint, errorCode);

    if (errorCode) {
        throw CRITICAL_EXCEPTION("Error : unable to reach server tcp\n");
    }
}

ClientTCP::~ClientTCP()
{
}

void ClientTCP::getCallbackData(const std::function<void(void *, size_t)> &callbackFunction)
{
    __callbackFunction = callbackFunction;
}

void ClientTCP::setCallbackError(const std::function<void()> & callbackerror)
{
    __callbackError = callbackerror;
}

void ClientTCP::call(boost::system::error_code code, size_t read)
{
    __read = read;
    if (code) {
        if (__callbackError && boost::asio::error::eof == code) {
            __callbackError();
        }
        return readData();
    }
    //std::cout.write((const char *)__buf.data().data(), read) << std::endl;
    if (__callbackFunction)
        __callbackFunction((void *)__buf.data().data(), read);
    __buf.consume(read);
    readData();
}

void ClientTCP::readData()
{
    boost::asio::async_read(__socket, __buf, boost::asio::transfer_at_least(sizeof(RType::Common::Tcp::Header)),  \
boost::bind(&ClientTCP::call, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

bool ClientTCP::sendData(const void * data, size_t size)
{    
    boost::system::error_code error;
    __socket.send(boost::asio::buffer(data, size), 0, error);

    return !error;
}