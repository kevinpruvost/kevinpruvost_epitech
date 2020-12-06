/*
** EPITECH PROJECT, 2020
** Babel server client manager
** File description:
**
*/

#pragma once

#include <ctime>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/lexical_cast.hpp>

#include "./lib/Babel/PacketsData.hpp"
#include "./lib/Babel/ConnectionCredentials.hpp"
#include "./server/database/sqliteDataBase.hpp"
#include "./lib/Babel/PacketsDataBinary.hpp"
#include "./lib/Exception.hpp"

#define functionPointerCaller(instance, ptr) ((instance).*(ptr))

namespace Babel {
    namespace Server {
        class BabelClient;
        /**
         * \brief Manage clients and interact with database
         */
        class ClientManager : public boost::enable_shared_from_this<ClientManager> {
        public:
            ClientManager();
            ~ClientManager();

            void connect(boost::shared_ptr<BabelClient> client_ptr);
            void disconnect(boost::shared_ptr<BabelClient> client_ptr);
            void manageCommand(boost::shared_ptr<BabelClient> babelClient, const Babel::Common::PacketsDataBinary& packet);

            boost::shared_ptr<BabelClient> getClientByUsername(const std::string& username);
            boost::shared_ptr<BabelClient> getClientByUuid(const std::string& uuid);

            void sendStateToContacts(boost::shared_ptr<Babel::Server::BabelClient> babelClient);
            void getContactsStates(boost::shared_ptr<Babel::Server::BabelClient> babelClient);

            //function pointers
            bool login(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args);
            bool logout(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args);
            bool call(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args);
            bool callAnswer(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args);
            bool callEnd(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args);
            bool contact(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args);
            bool message(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args);
            bool ping(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args);
            bool error(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args);

        private:
            std::set<boost::shared_ptr<BabelClient>> _clients;
            std::map<Babel::Rfc::Code, bool (ClientManager::*)(boost::shared_ptr<Babel::Server::BabelClient>, std::vector<std::string>)> _functionPointers;
            sqliteDataBase _database;
            boost::uuids::random_generator _generator;
        };
    }
}