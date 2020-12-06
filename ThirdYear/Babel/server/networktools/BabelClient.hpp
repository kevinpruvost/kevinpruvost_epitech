/*
** EPITECH PROJECT, 2020
** Babel server client
** File description:
**
*/

#pragma once

#include "ClientManager.hpp"

namespace Babel {
    namespace Server {
        /**
         * \brief Client instance
         */
        class BabelClient : public boost::enable_shared_from_this<BabelClient> {
        public:
            ~BabelClient();
            static boost::shared_ptr<BabelClient> create(boost::asio::io_context& io_context, boost::shared_ptr<Babel::Server::ClientManager> clientManager_ptr);
            boost::asio::ip::tcp::socket& getSocket();
            void waitForDatas();
            void send(const Babel::Rfc::Code code, const std::vector<std::string>& arguments = {});

            /* getters and setters */
            void setUsername(const std::string& name) { _username = name; }
            std::string getUsername() const { return (_username); }
            void setPassword(const std::string& password) { _password = password; }
            std::string getPassword() const { return (_password); }
            void setUuid(const std::string& uuid) { _uuid = uuid; }
            std::string getUuid() const { return (_uuid); }
            void setState(const Babel::Rfc::State& state) { _state = state; }
            Babel::Rfc::State getState() const { return (_state); }
            bool addContact(const std::pair<std::string, std::string>& contact) {
                if (std::find_if(_contacts.begin(), _contacts.end(), [contact](const std::pair<std::string, std::string>& element) { return element.first == contact.first; }) != _contacts.end())
                    return (false);
                _contacts.push_back(contact);
                return (true);
            }
            bool addContact(const std::vector<std::pair<std::string, std::string>> & contacts) {
                _contacts.insert(_contacts.end(), contacts.begin(), contacts.end());
                return (true);
            }
            std::vector<std::pair<std::string, std::string>> getContacts() const { return (_contacts); }
            void setCaller(const std::string& uuidCaller) { _uuidCaller = uuidCaller; }
            std::string getCaller() const { return (_uuidCaller); }

        private:
            BabelClient(boost::asio::io_context& io_context, boost::shared_ptr<Babel::Server::ClientManager> clientManager_ptr);
            void handleRead(const boost::system::error_code& error, size_t bytes_transferred);
            void handleWrite(const boost::system::error_code& error, size_t bytes_transferred);

        private:
            boost::asio::ip::tcp::socket _socket;
            boost::weak_ptr<Babel::Server::ClientManager> _clientManager_ptr;
            boost::asio::streambuf _readBuffer;
            Babel::Common::PacketsDataBinarySerialized _packetSender;

        private:
            std::string _username;
            std::string _password;
            std::string _uuid;
            Babel::Rfc::State _state;
            std::string _uuidCaller;
            std::vector<std::pair<std::string, std::string>> _contacts;
        };
    }
}