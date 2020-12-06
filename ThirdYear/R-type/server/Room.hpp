/*
** EPITECH PROJECT, 2020
** Babel server main
** File description:
** Where the program starts
*/

#pragma once

#include "UdpServer.hpp"

#include "Engine/REngine.hpp"
#include "Engine/REntity.hpp"
#include "DLLoader/RTypeDLLoader.hpp"


#include "Systems/ColliderSystem.hpp"
#include "Systems/RenderingSystem.hpp"
#include "Systems/MovementSystem.hpp"

#include "Game/MenuPage/TextBar.hpp"
#include "Game/MenuPage/Background.hpp"
#include "Game/MenuPage/MenuAudio.hpp"
#include "Components/Audio/Audio.hpp"

#include "Entities/Object/Character/Player/Player.hpp"

#include "Game/EntityInGame/Lib.hpp"
#include "Game/FpsDisplayer.hpp"

#define MAX_UDP_READ_PER_FRAME 20

namespace RType {
	namespace Server {
		class Room {
		public:
			Room(const std::string& id, boost::asio::io_context& context);
			~Room();

			static boost::shared_ptr<Room> createRoom(const std::string& id, boost::asio::io_context& context) {
				return boost::shared_ptr<Room>(new Room(id, context));
			}

			bool startGameLoop();
			bool stopGameLoop();

			std::string getId() const { return _roomId; }

			std::string getIp() const { return _udpServer.getIp(); }
			unsigned short getPort() const { return _udpServer.getPort(); }

			bool getIsThreadRunning() const { return _isThreadRunning; }

			bool isRunning() const { return _isGameRunning; }
			size_t getNumberOfPlayers() const { return _players.size(); }

			boost::shared_ptr<Player> getPlayerByEndpoint(const boost::asio::ip::udp::endpoint endpoint);
			void addPlayer(boost::shared_ptr<Player> player) { _players.insert(player); }
			void deletePlayer(boost::shared_ptr<Player> player) { _players.erase(player); }

			/* DLL management */
			void loadLibrairies(std::vector<std::string> filepaths);
		private:
			void gameLoop();
			void manageNetwork();
			void manageHeader(boost::shared_ptr<Player> player, RType::Common::Udp::Header *header);

			/* function pointers */
			bool username(boost::shared_ptr<Player> player, RType::Common::Udp::Header* header);
			bool ready(boost::shared_ptr<Player> player, RType::Common::Udp::Header* header);
			bool input(boost::shared_ptr<Player> player, RType::Common::Udp::Header* header);
			bool inputXY(boost::shared_ptr<Player> player, RType::Common::Udp::Header* header);
			bool logout(boost::shared_ptr<Player> player, RType::Common::Udp::Header* header);
			/* DLL management */
			void sendEntitiesToPlayer(boost::shared_ptr<Player> player);
			void sendComponentsUpdateToAllPlayers();
			void sendDestroyedEntitiesToAllPlayers(std::vector<unsigned int> ids);
			void sendCreatedComponentToAllPlayers(std::vector<std::weak_ptr<RType::Common::Engine::Component>> components);
			void sendCreatedEntitiesToAllPlayers(std::vector<unsigned int> ids);
		private:
			std::thread* _gameThread;
			bool _isThreadRunning;
			bool _isGameRunning;
			std::string _roomId;
			UdpServer _udpServer;
			std::set<boost::shared_ptr<Player>> _players;

			/* ENGINE */
			RType::Common::Engine::REngine _engine;
			std::vector<RType::Common::Engine::Entity*> _entities;
			std::weak_ptr<Common::Engine::InGameMonsterFactory> _monstersFactory;
		};
	}
}