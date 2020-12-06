/*
** EPITECH PROJECT, 2020
** Babel server
** File description:
** 
*/

#pragma once

#include "BabelClient.hpp"

namespace Babel {
    /**
    * \brief Server namespace containing server code
    */
    namespace Server {
        /**
         * \brief Contains everything the server needs to run properly
         */
        class BabelServer {
        public:
            BabelServer(boost::asio::io_context& io_context, unsigned int port);
            BabelServer(boost::asio::io_context& io_context, const std::string & ip, unsigned int port);
            ~BabelServer();
        private:
            void startAccept();
            void handleAccept(boost::shared_ptr<BabelClient> newClient, const boost::system::error_code& error);
        private:
            boost::asio::io_context& _IOcontext;
            boost::asio::ip::tcp::acceptor _acceptor;
            boost::shared_ptr<Babel::Server::ClientManager> _clientManager_ptr;
            boost::asio::signal_set _signals;
        };
    }
}