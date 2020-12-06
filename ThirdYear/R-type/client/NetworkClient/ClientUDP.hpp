/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** ClientUDP
*/

#pragma once

#include "INetworkClient.hpp"
#include <vector>

namespace RType
{
namespace Common
{
namespace Client
{
    class ClientUDP : virtual public INetworkClient {
        public:
            ClientUDP(boost::asio::io_context & context, const std::string & ip);
            ~ClientUDP();

            void bindSocket(unsigned short port);
            void call(boost::shared_ptr<std::vector<char>> & c, boost::system::error_code code, size_t read);

            //get
            size_t getSizeDataUDP() {return __read;};
            void * getDataUDP() {return __data;};

            //INetWork
            bool sendData(const void * data, size_t size);
            void getCallbackData(const std::function<void(void *, size_t size)> &callbackFunction);
            void readData();

            void setCallbackError(const std::function<void()> & error);

        private:
            boost::asio::ip::udp::socket __socket;
            std::function<void(void *, size_t)> __callbackFunction;
            std::function<void()> __callBackError;
            void * __data;
            size_t __read;
            std::string __ip;
            bool __isSet;
    };
}; // !RType::Common::Client
}; // !RType::Common
}; // !RType
