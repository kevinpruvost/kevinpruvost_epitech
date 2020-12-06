/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** INetworkClient
*/

#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "lib/Network/Rfc.hpp"
#include "lib/Network/BinaryStructure.hpp"

#include "lib/Exception.hpp"

namespace RType
{
namespace Common
{
namespace Client
{
    class INetworkClient {
        public:
            virtual bool sendData(const void * data, size_t size) = 0;
            virtual void getCallbackData(const std::function<void(void *, size_t)> &callbackFunction) = 0;
            virtual void readData() = 0;
    };
}; // !RType::Common::Client
}; // !RType::Common
}; // !RType