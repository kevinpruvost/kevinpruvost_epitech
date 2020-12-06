/*
** EPITECH PROJECT, 2020
** Babel server main
** File description:
** Where the program starts
*/

#include "Room.hpp"

using namespace RType::Common;

RType::Server::Room::Room(const std::string& id, boost::asio::io_context& context) :
	_gameThread(nullptr),
	_isThreadRunning(false),
	_isGameRunning(false),
	_roomId(id),
	_udpServer(context, 0, *this)
{
	std::string posibleChars("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	if (id == "") {
		for (size_t i = 0; i < 8; ++i) {
			_roomId.push_back(static_cast<char>(std::rand() % posibleChars.size()));
		}
	}

    try
    {
        _engine.RegisterComponent<Engine::Audio>(Rfc::ComponentTypeId::Audio);
        _engine.RegisterComponent<Engine::KeyInput>(Rfc::ComponentTypeId::KeyInput);
        _engine.RegisterComponent<Engine::Transform>(Rfc::ComponentTypeId::Transform);
        _engine.RegisterComponent<Engine::UITransform>(Rfc::ComponentTypeId::UITransform);
        _engine.RegisterComponent<Engine::RectangleCollider>(Rfc::ComponentTypeId::RectangleCollider);
        _engine.RegisterComponent<Engine::CircleCollider>(Rfc::ComponentTypeId::CircleCollider);
        _engine.RegisterComponent<Engine::SpriteAnimation>(Rfc::ComponentTypeId::SpriteAnimation);
        _engine.RegisterComponent<Engine::Sprite>(Rfc::ComponentTypeId::Sprite);
        _engine.RegisterComponent<Engine::Text>(Rfc::ComponentTypeId::Text);
        _engine.RegisterComponent<Engine::TextInput>(Rfc::ComponentTypeId::TextInput);
        _engine.RegisterComponent<Engine::CharacterCharacteristics>(Rfc::ComponentTypeId::CharacterCharacteristics);
        _engine.RegisterComponent<Engine::Weapon>(Rfc::ComponentTypeId::Weapon);
        auto colliderSystem = _engine.RegisterSystem<Engine::ColliderSystem>(_engine);
        auto movementSystem = _engine.RegisterSystem<Engine::MovementSystem>(_engine);
        auto background = _engine.CreateEntity<Engine::Background>(_engine);

        {
            auto boss = _engine.CreateEntity<Engine::InGameBoss>(_engine);
            auto mob = _engine.CreateEntity<Engine::InGameGenericMob>(_engine);
            _engine.RegisterEntity<Engine::InGameBoss>(*boss);
            _engine.RegisterEntity<Engine::InGameGenericMob>(*mob);
        }
		_monstersFactory = _engine.CreateEntity<Engine::InGameMonsterFactory>(_engine);
        auto obstacle1 = _engine.CreateEntity<Engine::InGameObstacle>(_engine);

        auto obstacle2 = _engine.CreateEntity<Engine::InGameObstacle>(_engine);
		obstacle2->SetToDown();
        auto obstacle3 = _engine.CreateEntity<Engine::InGameObstacle>(_engine);
		obstacle3->SetToRight();
        auto obstacle4 = _engine.CreateEntity<Engine::InGameObstacle>(_engine);
		obstacle3->SetToUp();

        auto fpsDisplayer = _engine.CreateEntity<Engine::FpsDisplayer>(_engine);
        auto audio = _engine.CreateEntity<Engine::MenuAudio>(_engine);

    } catch (const MinorException & e) {
        LOG_ERROR(e.what());
    } catch (const CriticalException& e) {
        LOG_ERROR(e.what());
    }
}

RType::Server::Room::~Room()
{
	_isThreadRunning = false;
	if (_gameThread && _gameThread->joinable())
		_gameThread->join();
	_engine.Stop(false);
}

/**
 * \brief Begin a new thread and start the game inside it
 * \return True if everything went well
 */
bool RType::Server::Room::startGameLoop()
{
	if (_isThreadRunning) {
		std::cerr << "Cannot start room: Game already running." << std::endl;
		return (false);
	}
	_isThreadRunning = true;
	_gameThread = new std::thread([this]() { this->gameLoop(); });
	return (true);
}

/**
 * \brief Stop the game loop
 * \return True if everything went well
 */
bool RType::Server::Room::stopGameLoop()
{
	if (!_isThreadRunning) {
		std::cerr << "Cannot stop room: Game is not running." << std::endl;
		return (false);
	}
	_isThreadRunning = false;
	return (true);
}

/**
 * \brief Manager packet header & call the right function pointer
 */
void RType::Server::Room::manageHeader(boost::shared_ptr<Player> player, RType::Common::Udp::Header* header)
{
	switch (header->code) {
	case RType::Common::Rfc::UdpCode::Username: username(player, header);
		break;
	case RType::Common::Rfc::UdpCode::ReadyRequest: ready(player, header);
		break;
	case RType::Common::Rfc::UdpCode::Input: input(player, header);
		break;
	case RType::Common::Rfc::UdpCode::InputXY: inputXY(player, header);
		break;
	default: std::cerr << "Received unknown packet." << std::endl;
		break;
	}
}

/**
 * \brief Read datas on the UDP socket & call the manageHeader function once a complete packet is received
 */
void RType::Server::Room::manageNetwork()
{
	std::pair<std::vector<unsigned char>, boost::asio::ip::udp::endpoint> packet;
	size_t nbRead = 0;

	while (((packet = _udpServer.receiveDatas()).first.size() > 0) && ((nbRead++) < MAX_UDP_READ_PER_FRAME)) {
		boost::shared_ptr<Player> player(getPlayerByEndpoint(packet.second));
		if (!player) {
			//new player (send all ents to player, create new entity & send new ent to every players)
			player = boost::shared_ptr<Player>(new Player(packet.second));
			_players.insert(player);
			sendEntitiesToPlayer(player);
			player->_ent = _engine.CreateEntity<RType::Common::Engine::InGamePlayer>(_engine);
		}
		player->writeInBuffer(packet.first);
		std::vector<unsigned char>& buffer(player->getVecBuffer());
		if (buffer.size() < sizeof(RType::Common::Udp::Header))
			continue;
		RType::Common::Udp::Header* header = static_cast<RType::Common::Udp::Header*>(static_cast<void*>(buffer.data()));
		if (buffer.size() < header->size)
			continue;
		manageHeader(player, header);
		buffer.erase(buffer.begin(), buffer.begin() + header->size);
	}
}

/**
 * \brief gameLoop meant to be run in a thread
 */
void RType::Server::Room::gameLoop()
{
	std::cout << "Game running..." << std::endl;
	while (_isThreadRunning) {
		try {
			manageNetwork();
			try {
				if (!_engine.shouldTick())
					continue;
				_engine.Loop();
				sendDestroyedEntitiesToAllPlayers(_engine.GetDestroyedEntityIds());
				sendCreatedEntitiesToAllPlayers(_engine.GetCreatedEntities());
				sendCreatedComponentToAllPlayers(_engine.GetCreatedComponents());
				sendComponentsUpdateToAllPlayers();
			} catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
			}
		} catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
	std::cout << "Game terminated." << std::endl;
}

boost::shared_ptr<RType::Server::Player> RType::Server::Room::getPlayerByEndpoint(const boost::asio::ip::udp::endpoint endpoint)
{
	for (auto& player : _players) {
		if (player->getEndpoint() == endpoint)
			return (player);
	}
	return nullptr;
}

/* function pointers */

bool RType::Server::Room::username(boost::shared_ptr<Player> player, RType::Common::Udp::Header* header)
{
	RType::Common::Udp::UsernameRequest* username = static_cast<RType::Common::Udp::UsernameRequest*>(static_cast<void*>(header));
	
	std::cout << "User set his username to: " << username->username << "." << std::endl;
	player->setUsername(username->username);
	return true;
}

bool RType::Server::Room::ready(boost::shared_ptr<Player> player, RType::Common::Udp::Header* header)
{
	(void)player;
	(void)header;
	/*if (_isGameRunning) {
		std::cout << "Error: game already running" << std::endl;
		return false;
	}
	RType::Common::Udp::GameStartedAnswer answer{ {Common::Rfc::UdpCode::GameStartedAnswer, sizeof(Common::Udp::GameStartedAnswer)} };

	for (auto& p : _players)
		_udpServer.sendDatagram(static_cast<void*>(&answer), answer.header.size, p->getEndpoint());
	_isGameRunning = true;*/
	return true;
}

bool RType::Server::Room::input(boost::shared_ptr<Player> player, RType::Common::Udp::Header* header)
{
	RType::Common::Udp::InputRequest* input = static_cast<RType::Common::Udp::InputRequest*>(static_cast<void*>(header));

	std::cout << "Input received: ";
	std::cout << static_cast<int>(input->inputCode) << std::endl;

	if (player->_ent.expired())
		return false;
	player->_ent.lock()->Input(input->inputCode);
	return true;
}

bool RType::Server::Room::inputXY(boost::shared_ptr<Player> player, RType::Common::Udp::Header* header)
{
	RType::Common::Udp::InputXYRequest* input = static_cast<RType::Common::Udp::InputXYRequest*>(static_cast<void*>(header));

	std::cout << "InputXY received : " << static_cast<int>(input->inputCode) << ";" << static_cast<int>(input->inputValue) << ", " << static_cast<int>(input->inputValue2) << std::endl;
	return true;
}

bool RType::Server::Room::logout(boost::shared_ptr<Player> player, RType::Common::Udp::Header* header)
{
	(void)header;
	std::cout << player->getUsername() << " has disconected from the room" << std::endl;
	_engine.DestroyEntityId(player->getEntId());
	_players.erase(player);

	if (_players.size() == 0) {
		_engine.Stop(false);
		_udpServer.close();
		_isThreadRunning = false;
	}
	return true;
}

/* DLL management */

void RType::Server::Room::loadLibrairies(std::vector<std::string> sharedLibrairiesPaths)
{
	std::cout << "Updating entities..." << std::endl;

	for (auto& path : sharedLibrairiesPaths) {
		RType::Common::DLLoader::RTypeDLLoader<RType::Common::Engine::Entity> loader(path);

		if (loader == nullptr)
			continue;
		auto ent = loader.getInstance("getClass", _engine);
		_engine.RegisterEntity(*ent);
		if (_monstersFactory.expired())
			break;
		std::shared_ptr<Common::Engine::InGameMonsterFactory> factory = _monstersFactory.lock();
		if (!factory)
			break;
		factory->AddNewEnemy(ent->ClassName());
		std::cout << "New enemy added to engine." << std::endl;
	}

	std::cout << "Room has " << _entities.size() << " entities loaded." << std::endl;
}

void RType::Server::Room::sendEntitiesToPlayer(boost::shared_ptr<Player> player)
{
	auto entities = _engine.GetAllEntities();

	for (auto& entity : entities) {
		if (entity.expired()) continue;
		 std::shared_ptr<RType::Common::Engine::Entity> ent = entity.lock();

		if (!ent)
			continue;
		RType::Common::Udp::Entities::CreateEntity e;
		e.header.code = RType::Common::Rfc::UdpCode::CreateEntity;
		e.header.size = sizeof(RType::Common::Udp::Entities::CreateEntity);
		e.id = ent->getId();
		_udpServer.sendDatagram(static_cast<void*>(&e), e.header.size, player->getEndpoint());
	}

	auto components = _engine.GetAllComponents();

	for (auto& component : components) {
		if (component.expired()) continue;
		std::shared_ptr<RType::Common::Engine::Component> comp = component.lock();

		if (!comp)
			continue;
		if (comp->GetComponentTypeId() == Common::Rfc::ComponentTypeId::KeyInput)
			continue;
		RType::Common::Udp::Entities::UpdateRequest c = comp->CreateUpdateRequest();
		c.header.code = RType::Common::Rfc::UdpCode::CreateComponent;
		c.header.size = sizeof(RType::Common::Udp::Entities::CreateComponent);
		c.entityId = comp->entityId;
		c.typeId = comp->GetComponentTypeId();

		_udpServer.sendDatagram(static_cast<void*>(&c), c.header.size, player->getEndpoint());
	}
}

void RType::Server::Room::sendComponentsUpdateToAllPlayers()
{
	auto components = _engine.GetAllComponents();

	for (auto& component : components) {
		std::shared_ptr<RType::Common::Engine::Component> comp = component.lock();

		if (!comp)
			continue;
		if (comp->GetComponentTypeId() == Common::Rfc::ComponentTypeId::KeyInput)
			continue;
		RType::Common::Udp::Entities::UpdateRequest u = comp->CreateUpdateRequest();
		u.header.code = RType::Common::Rfc::UdpCode::Update;
		u.header.size = sizeof(RType::Common::Udp::Entities::UpdateRequest);
		u.entityId = comp->entityId;
		u.typeId = comp->GetComponentTypeId();

		for (auto player : _players)
			_udpServer.sendDatagram(static_cast<void*>(&u), u.header.size, player->getEndpoint());
	}
}

void RType::Server::Room::sendDestroyedEntitiesToAllPlayers(std::vector<unsigned int> ids)
{
	if (ids.size() <= 0)
		return;

	for (auto& id : ids) {
		RType::Common::Udp::Entities::DeleteRequest d;

		d.header.code = RType::Common::Rfc::UdpCode::Delete;
		d.header.size = sizeof(RType::Common::Udp::Entities::DeleteRequest);
		d.entityId = id;
		for (auto& player : _players)
			_udpServer.sendDatagram(static_cast<void*>(&d), d.header.size, player->getEndpoint());
	}
}

void RType::Server::Room::sendCreatedComponentToAllPlayers(std::vector<std::weak_ptr<RType::Common::Engine::Component>> components)
{
	if (components.size() <= 0)
		return;
	
	for (auto& component : components) {
		if (component.expired()) continue;
		std::shared_ptr<RType::Common::Engine::Component> comp = component.lock();

		if (!comp)
			continue;
		RType::Common::Udp::Entities::UpdateRequest c = comp->CreateUpdateRequest();

		c.header.code = RType::Common::Rfc::UdpCode::CreateComponent;
		c.header.size = sizeof(RType::Common::Udp::Entities::CreateComponent);
		c.entityId = comp->entityId;
		c.typeId = comp->GetComponentTypeId();
		
		for (auto& player : _players) {
			_udpServer.sendDatagram(static_cast<void*>(&c), c.header.size, player->getEndpoint());
		}
	}
}

void RType::Server::Room::sendCreatedEntitiesToAllPlayers(std::vector<unsigned int> ids)
{
	if (ids.size() <= 0)
		return;

	for (auto& id : ids) {
		RType::Common::Udp::Entities::CreateEntity c;

		c.header.code = RType::Common::Rfc::UdpCode::CreateEntity;
		c.header.size = sizeof(RType::Common::Udp::Entities::CreateEntity);
		c.id = id;
		for (auto& player : _players) {
			_udpServer.sendDatagram(static_cast<void*>(&c), c.header.size, player->getEndpoint());
		}
	}
}