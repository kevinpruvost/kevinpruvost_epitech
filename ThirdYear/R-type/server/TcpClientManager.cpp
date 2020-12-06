/*
** EPITECH PROJECT, 2020
** Babel server main
** File description:
** Where the program starts
*/

#include "TcpClientManager.hpp"

RType::Server::TcpClientManager::TcpClientManager(boost::asio::io_context& io_context) : _functionPointers{
	{RType::Common::Rfc::TcpCode::Login, &TcpClientManager::login} },
	_IOcontext(io_context),
	_systemWatcher("./")
{
	_systemWatcher.setCallBack([this](const std::string& filepath) { this->loadSharedLib(filepath); });
}

RType::Server::TcpClientManager::~TcpClientManager()
{
	//todo
}

/**
 * \brief Add new client to the client manager
 * \param Shared pointer to the client
 */
void RType::Server::TcpClientManager::addClient(boost::shared_ptr<TcpClient> client)
{
	_clients.insert(client);
}

/**
 * \brief Delete client from the client manager
 * \param Shared pointer to the client
 */
void RType::Server::TcpClientManager::deleteClient(boost::shared_ptr<TcpClient> client)
{
	_clients.erase(client);
}

/**
 * \brief get the room handle by its id
 * \param room id
 * \return shared pointer to room
 */
boost::shared_ptr<RType::Server::Room> RType::Server::TcpClientManager::getRoomByID(const std::string& id)
{
	for (auto& room : _rooms) {
		if (room->getId() == id) {
			return (room);
		}
	}
	return (nullptr);
}

void RType::Server::TcpClientManager::killInactiveRooms()
{
	std::set<boost::shared_ptr<Room>>::iterator it;

	do {
		it = std::find_if(_rooms.begin(), _rooms.end(), [](const boost::shared_ptr<Room>& val) { return !val->getIsThreadRunning(); });
		if (it != _rooms.end()) {
			_rooms.erase(it);
			std::cout << "A room has been deleted cause it was inactive." << std::endl;
		}
	} while (it != _rooms.end());
}

/**
 * \brief Manager header received by clients
 * \param Shared pointer to the client caller & its header
 */
void RType::Server::TcpClientManager::manageHeader(boost::shared_ptr<TcpClient> client, const Common::Tcp::Header* header)
{
	auto it = _functionPointers.find(header->code);
	if (it != _functionPointers.end()) {
		(this->*(it->second))(client, header);
	} else {
		std::cerr << "Carefull: An unknown commandType has been received !" << std::endl;
		Common::Tcp::UnknownRequest error = { {RType::Common::Rfc::TcpCode::Unknown, sizeof(Common::Tcp::UnknownRequest)} };
		client->send(static_cast<void*>(&error), error.header.size);
	}
}

/* function pointers */

bool RType::Server::TcpClientManager::login(boost::shared_ptr<TcpClient> client, const Common::Tcp::Header* header)
{
	const Common::Tcp::LoginRequest* login = static_cast<const Common::Tcp::LoginRequest*>(static_cast<const void*>(header));
	boost::shared_ptr<Room> room = nullptr;

	killInactiveRooms();

	std::cout << "Received login request with roomId: " << login->roomId << std::endl;
	if (!(room = getRoomByID(std::string(login->roomId)))) {
		//create room
		std::cout << "Creating room..." << std::endl;
		room = Room::createRoom(login->roomId, _IOcontext);
		room->loadLibrairies(_sharedLibrairiesPaths);
		std::cout << "Room UDP ip: " << room->getIp() << ":" << room->getPort() << std::endl;
		_rooms.insert(room);
		room->startGameLoop();
	}
	//join room
	if (room->isRunning() || room->getNumberOfPlayers() >= 4) {
		std::cerr << "Client tried to join an already running room." << std::endl;
		//TODO envoyer une erreur au client
		return false;
	}
	std::cout << "Joining room..." << std::endl;
	Common::Tcp::LoginOkAnswer logAnswer{ {Common::Rfc::TcpCode::LoginAnswer, sizeof(Common::Tcp::LoginOkAnswer)}, room->getPort(), "" };
	std::memset(logAnswer.roomId, 0, ROOM_ID_SIZE);
	size_t len = room->getId().copy(logAnswer.roomId, ROOM_ID_SIZE);
	logAnswer.roomId[len] = '\0';
	client->send(static_cast<void*>(&logAnswer), logAnswer.header.size);
	return true;
}

void RType::Server::TcpClientManager::loadSharedLib(const std::string& path)
{
	_sharedLibrairiesPaths.push_back(path);
}