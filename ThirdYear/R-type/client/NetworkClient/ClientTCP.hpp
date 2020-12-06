/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** ClientTCP
*/

#pragma once

#include "INetworkClient.hpp"

namespace RType
{
namespace Common
{
namespace Client
{
    class ClientTCP : virtual public INetworkClient {
        public:
            ClientTCP(boost::asio::io_context & boost, const std::string & ip, unsigned short port);
            ~ClientTCP();

            bool sendData(const void * data, size_t size);
            void getCallbackData(const std::function<void(void *, size_t)> &callbackFunction);
            void readData();

            void setCallbackError(const std::function<void()> & callbackerror);

            void call(boost::system::error_code code, size_t read);

            size_t getSizeToReadTCP() {return __read;};
            const void * getBufTCP() {return __buf.data().data();};

        private:
            boost::asio::ip::tcp::socket __socket;
            std::function<void(void *, size_t)> __callbackFunction;
            std::function<void()> __callbackError; 
            boost::asio::streambuf __buf;
            size_t __read;
    };
}; // !RType::Common::Client
}; // !RType::Common
}; // !RType