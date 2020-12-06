/*
** EPITECH PROJECT, 2020
** Babel server client manager
** File description:
**
*/

#include "ClientManager.hpp"
#include "BabelClient.hpp"

Babel::Server::ClientManager::ClientManager() : _functionPointers{
    {Babel::Rfc::Code::CS_LOGIN, &ClientManager::login},
    {Babel::Rfc::Code::CS_LOGOUT, &ClientManager::logout},
    {Babel::Rfc::Code::CS_CALL, &ClientManager::call},
    {Babel::Rfc::Code::CS_CALL_ANSWER, &ClientManager::callAnswer},
    {Babel::Rfc::Code::CS_CALL_END, &ClientManager::callEnd},
    {Babel::Rfc::Code::CS_CONTACT, &ClientManager::contact},
    {Babel::Rfc::Code::CS_MSG, &ClientManager::message},
    {Babel::Rfc::Code::CS_PING, &ClientManager::ping},
    {Babel::Rfc::Code::CS_ERROR, &ClientManager::error} }
{
}

Babel::Server::ClientManager::~ClientManager()
{
}

/**
 * \brief Add BabelClient to the ClientManager
 * \param Shared pointer to the BabelClient
 */
void Babel::Server::ClientManager::connect(boost::shared_ptr<Babel::Server::BabelClient> client_ptr)
{
    _clients.insert(client_ptr);
}

/**
 * \brief Delete BabelClient from the ClientManager
 * \param Shared pointer to the BabelClient
 */
void Babel::Server::ClientManager::disconnect(boost::shared_ptr<BabelClient> client_ptr)
{
    if (client_ptr->getState() == Babel::Rfc::State::Occupied) {
        boost::shared_ptr<BabelClient> caller = getClientByUuid(client_ptr->getCaller());
        if (caller)
            caller->send(Babel::Rfc::SC_CALL_END, { client_ptr->getUuid() });
    }
    client_ptr->setState(Babel::Rfc::State::Disconnected);
    sendStateToContacts(client_ptr);
    _clients.erase(client_ptr);
}

/**
 * \brief Get BabelClient form its username
 * \param string username
 * \return Shared pointer to the BabelClient
 */
boost::shared_ptr<Babel::Server::BabelClient> Babel::Server::ClientManager::getClientByUsername(const std::string& username)
{
    for (auto& client : _clients) {
        if (client->getUsername() == username)
            return client;
    }
    return (nullptr);
}

/**
 * \brief Get BabelClient from its uuid
 * \param string uuid
 * \return Shared pointer to the BabelClient
 */
boost::shared_ptr<Babel::Server::BabelClient> Babel::Server::ClientManager::getClientByUuid(const std::string& uuid)
{
    for (auto& client : _clients) {
        if (client->getUuid() == uuid)
            return client;
    }
    return (nullptr);
}

/**
 * \brief Get BabelClient from its uuid
 * \param Shared pointer to the BabelClient
 * \param PacketsDataBinary packet
 */
void Babel::Server::ClientManager::manageCommand(boost::shared_ptr<BabelClient> babelClient, const Babel::Common::PacketsDataBinary& packet)
{
    Babel::Rfc::Code commandType = packet.getCommandType();

    std::cout << "Receiving packet of type: " << commandType << " with " << packet.getNumberOfArguments() << " arguments inside." << std::endl;
    
    auto it = _functionPointers.find(commandType);
    if (it != _functionPointers.end()) {
        functionPointerCaller(*this, it->second)(babelClient, packet.getArguments());
    } else {
        std::cerr << "Carefull: An unknown commandType has been received but could not be handled" << std::endl;
        babelClient->send(Babel::Rfc::Code::UNKNOWN);
    }
}

/**
 * \brief Send user's state to its contact
 * \param Shared pointer to the BabelClient
 */
void Babel::Server::ClientManager::sendStateToContacts(boost::shared_ptr<Babel::Server::BabelClient> babelClient)
{
    for (const std::pair<std::string, std::string>& contact : babelClient->getContacts()) {
        boost::shared_ptr<BabelClient> targetedClient = getClientByUuid(contact.first);
        if (!targetedClient)
            continue;
        targetedClient->send(Babel::Rfc::Code::SC_CONTACT, { babelClient->getUuid(), babelClient->getUsername(), std::to_string(babelClient->getState()) });
    }
}

/**
 * \brief Get user contacts states
 * \param Shared pointer to the BabelClient
 */
void Babel::Server::ClientManager::getContactsStates(boost::shared_ptr<Babel::Server::BabelClient> babelClient)
{
    for (const std::pair<std::string, std::string>& contact : babelClient->getContacts()) {
        boost::shared_ptr<Babel::Server::BabelClient> contactPtr = getClientByUuid(contact.first);
        if (!contactPtr) {
            babelClient->send(Babel::Rfc::Code::SC_CONTACT, { contact.first, contact.second, std::to_string(Babel::Rfc::State::Disconnected) });
            continue;
        }
        babelClient->send(Babel::Rfc::Code::SC_CONTACT, { contact.first, contact.second, std::to_string(contactPtr->getState()) });
    }
}

//FUNCTION POINTERS

/**
 * \brief Login manager
 * \param Shared pointer to the BabelClient
 * \param Vector of string containing arguments
 */
bool Babel::Server::ClientManager::login(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args)
{
    if (args.size() != 2) {
        std::cerr << "Not enough arguments to login" << std::endl;
        babelClient->send(Babel::Rfc::Code::SC_ERROR, { std::to_string(Babel::Rfc::Code::CS_LOGIN), "Not enough argument" });
        return (false);
    }
    if (getClientByUsername(args.at(0)) != nullptr) {
        std::cerr << "User already loged in." << std::endl;
        babelClient->send(Babel::Rfc::Code::SC_ERROR, { std::to_string(Babel::Rfc::Code::CS_LOGIN), "User already logged in" });
        return (false);
    }

    std::cout << "Client tried to login with: user=" << args.at(0) << ", password=" << args.at(1) << std::endl;

    std::vector<std::string> accountCredentials(_database.getAccount(args.at(0)));

    if (accountCredentials.size() == 3) {
        if (args.at(1) == accountCredentials.at(2)) {
            babelClient->setUuid(accountCredentials.at(0));
            babelClient->setUsername(accountCredentials.at(1));
            babelClient->setPassword(accountCredentials.at(2));
            babelClient->addContact(_database.getContacts(babelClient->getUuid()));
            babelClient->send(Babel::Rfc::Code::SC_USER, { babelClient->getUuid(), babelClient->getUsername(), std::to_string(Babel::Rfc::State::Connected) });
            sendStateToContacts(babelClient);
            getContactsStates(babelClient);
        } else {
            babelClient->send(Babel::Rfc::Code::SC_ERROR, { std::to_string(Babel::Rfc::Code::CS_LOGIN), "Wrong password" });
            return (false);
        }
    } else {
        boost::uuids::uuid boost_uuid = _generator();
        std::string uuid = boost::lexical_cast<std::string>(boost_uuid);
        babelClient->setUuid(uuid);
        babelClient->setUsername(args.at(0));
        babelClient->setPassword(args.at(1));
        _database.addAccount(uuid, babelClient->getUsername(), babelClient->getPassword());
        babelClient->send(Babel::Rfc::Code::SC_USER, { babelClient->getUuid(), babelClient->getUsername(), std::to_string(Babel::Rfc::State::Connected) });
    }
    return (true);
}

/**
 * \brief Logout manager
 * \param Shared pointer to the BabelClient
 * \param Vector of string containing arguments
 */
bool Babel::Server::ClientManager::logout(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args)
{
    disconnect(babelClient);
    return (true);
}

/**
 * \brief Call manager
 * \param Shared pointer to the BabelClient
 * \param Vector of string containing arguments
 */
bool Babel::Server::ClientManager::call(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args)
{
    if (args.size() != 3) {
        std::cerr << "Not enough argument to make a call." << std::endl;
        babelClient->send(Babel::Rfc::Code::SC_ERROR, { std::to_string(Babel::Rfc::Code::CS_CALL), "Not enough argument" });
        return (false);
    }

    boost::shared_ptr<BabelClient> targetedClient(getClientByUuid(args.at(0)));

    if (!targetedClient) {
        std::cerr << "Couldn't make the call: Client is not connected or doesn't exist" << std::endl;
        babelClient->send(Babel::Rfc::Code::SC_ERROR, { std::to_string(Babel::Rfc::Code::CS_CALL), "User not connected or does not exist" });
        return (false);
    }
    if (targetedClient->getState() == Babel::Rfc::State::Occupied) {
        std::cerr << "User is occupied" << std::endl;
        babelClient->send(Babel::Rfc::Code::SC_ERROR, { std::to_string(Babel::Rfc::Code::CS_CALL), "User is occupied" });
        return (false);
    }
    targetedClient->send(Babel::Rfc::Code::SC_CALL, { babelClient->getUuid(), args.at(1), args.at(2) });
    return (true);
}

/**
 * \brief CallAnswer manager
 * \param Shared pointer to the BabelClient
 * \param Vector of string containing arguments
 */
bool Babel::Server::ClientManager::callAnswer(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args)
{
    if (args.size() != 3) {
        std::cerr << "Not enough argument to make a call." << std::endl;
        babelClient->send(Babel::Rfc::Code::SC_ERROR, { std::to_string(Babel::Rfc::Code::CS_CALL_ANSWER), "Not enough argument" });
        return (false);
    }

    boost::shared_ptr<BabelClient> targetedClient(getClientByUuid(args.at(0)));

    if (!targetedClient) {
        std::cerr << "Couldn't make the call: Client is not connected or doesn't exist" << std::endl;
        babelClient->send(Babel::Rfc::Code::SC_ERROR, { std::to_string(Babel::Rfc::Code::CS_CALL_ANSWER), "Client is not connected or does not exist" });
        return (false);
    }
    babelClient->setState(Babel::Rfc::State::Occupied);
    targetedClient->setState(Babel::Rfc::State::Occupied);
    babelClient->setCaller(targetedClient->getUuid());
    targetedClient->setCaller(babelClient->getUuid());
    targetedClient->send(Babel::Rfc::Code::SC_CALL_ANSWER, { babelClient->getUuid(), args.at(1), args.at(2) });
    sendStateToContacts(babelClient);
    sendStateToContacts(targetedClient);
    return (true);
}

/**
 * \brief CallEnd manager
 * \param Shared pointer to the BabelClient
 * \param Vector of string containing arguments
 */
bool Babel::Server::ClientManager::callEnd(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args)
{
    if (args.size() != 1) {
        std::cerr << "Not enough argument to end the call." << std::endl;
        babelClient->send(Babel::Rfc::Code::SC_ERROR, { std::to_string(Babel::Rfc::Code::CS_CALL_END), "Not enough arguments" });
        return (false);
    }

    boost::shared_ptr<BabelClient> targetedClient(getClientByUuid(args.at(0)));

    if (!targetedClient) {
        std::cerr << "Couldn't end the call with the user: user doesn't exist or is disconnected" << std::endl;
        babelClient->send(Babel::Rfc::Code::SC_ERROR, { std::to_string(Babel::Rfc::Code::CS_CALL_END), "Client is not connected or does not exist" });
        return (false);
    }
    babelClient->setState(Babel::Rfc::State::Connected);
    targetedClient->setState(Babel::Rfc::State::Connected);
    babelClient->setCaller("");
    targetedClient->setCaller("");
    targetedClient->send(Babel::Rfc::Code::SC_CALL_END, { babelClient->getUuid() });
    sendStateToContacts(babelClient);
    sendStateToContacts(targetedClient);
    return (true);
}

/**
 * \brief Contact manager
 * \param Shared pointer to the BabelClient
 * \param Vector of string containing arguments
 */
bool Babel::Server::ClientManager::contact(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args)
{
    if (args.size() != 1) {
        std::cerr << "Not enough arguments to add contact" << std::endl;
        babelClient->send(Babel::Rfc::Code::SC_ERROR, { std::to_string(Babel::Rfc::Code::CS_CONTACT), "Not enough arguments" });
        return (false);
    }
    boost::shared_ptr<BabelClient> targetedClient(getClientByUsername(args.at(0)));

    if (!targetedClient) { //if not logged
        std::vector<std::string> accountCredentials(_database.getAccount(args.at(0)));
        if (accountCredentials.size() != 3) { //if not in database
            babelClient->send(Babel::Rfc::Code::SC_ERROR, { std::to_string(Babel::Rfc::Code::CS_CONTACT), "Client does not exist" });
            return (false);
        }
        //if in database
        babelClient->addContact(std::make_pair(accountCredentials.at(0), accountCredentials.at(1)));
        _database.addContact(babelClient->getUuid(), std::make_pair(accountCredentials.at(0), accountCredentials.at(1)));
        _database.addContact(accountCredentials.at(0), std::make_pair(babelClient->getUuid(), babelClient->getUsername()));
        babelClient->send(Babel::Rfc::Code::SC_CONTACT, { accountCredentials.at(0), accountCredentials.at(1), std::to_string(Babel::Rfc::State::Disconnected) });
    }
    else { //if logged
        babelClient->addContact(std::make_pair(targetedClient->getUuid(), targetedClient->getUsername()));
        targetedClient->addContact(std::make_pair(babelClient->getUuid(), babelClient->getUsername()));
        _database.addContact(babelClient->getUuid(), std::make_pair(targetedClient->getUuid(), targetedClient->getUsername()));
        _database.addContact(targetedClient->getUuid(), std::make_pair(babelClient->getUuid(), babelClient->getUsername()));
        babelClient->send(Babel::Rfc::Code::SC_CONTACT, { targetedClient->getUuid(), targetedClient->getUsername(), std::to_string(targetedClient->getState()) });
        targetedClient->send(Babel::Rfc::Code::SC_CONTACT, { babelClient->getUuid(), babelClient->getUsername(), std::to_string(babelClient->getState()) });
    }
    return (true);
}

/**
 * \brief Message manager
 * \param Shared pointer to the BabelClient
 * \param Vector of string containing arguments
 */
bool Babel::Server::ClientManager::message(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args)
{
    if (args.size() != 2) {
        std::cerr << "Not enough argument to send message." << std::endl;
        babelClient->send(Babel::Rfc::Code::SC_ERROR, { std::to_string(Babel::Rfc::Code::CS_MSG), "Not enough arguments" });
        return (false);
    }

    boost::shared_ptr<BabelClient> targetedClient(getClientByUuid(args.at(0)));

    if (!targetedClient) {
        std::cerr << "Error sending message: client is not connected or doesn't exist" << std::endl;
        babelClient->send(Babel::Rfc::Code::SC_ERROR, { std::to_string(Babel::Rfc::Code::CS_MSG), "Client is not connected or does not exist" });
        return (false);
    }
    targetedClient->send(Babel::Rfc::Code::SC_MSG, { babelClient->getUuid(), args.at(1) });
    return (true);
}

/**
 * \brief Ping manager
 * \param Shared pointer to the BabelClient
 * \param Vector of string containing arguments
 */
bool Babel::Server::ClientManager::ping(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args)
{
    babelClient->send(Babel::Rfc::Code::SC_OK, { std::to_string(Babel::Rfc::Code::CS_PING) });
    return (true);
}

/**
 * \brief Error manager
 * \param Shared pointer to the BabelClient
 * \param Vector of string containing arguments
 */
bool Babel::Server::ClientManager::error(boost::shared_ptr<Babel::Server::BabelClient> babelClient, std::vector<std::string> args)
{
    if (args.size() != 2)
        return (false);
    std::cout << "Got error message: " << args.at(1) << " from commandID: " << args.at(0) << std::endl;
    return (true);
}