/*
** EPITECH PROJECT, 2020
** Babel server main
** File description:
** Where the program starts
*/

#pragma once

#include "Room.hpp"

#include "FileSystemWatcher/RTypeFileSystemWatcher.hpp"

namespace RType {
	namespace Server {
		class TcpClientManager : public boost::enable_shared_from_this<TcpClientManager> {
		public:
			TcpClientManager(boost::asio::io_context& io_context);
			~TcpClientManager();

			void addClient(boost::shared_ptr<TcpClient> client);
			void deleteClient(boost::shared_ptr<TcpClient> client);

			void manageHeader(boost::shared_ptr<TcpClient> client, const Common::Tcp::Header* header);

			boost::shared_ptr<Room> getRoomByID(const std::string& id);
			void killInactiveRooms();

			void loadSharedLib(const std::string& filepath);

			/* functions pointers */
			bool login(boost::shared_ptr<TcpClient> client, const Common::Tcp::Header *header);
		private:
			boost::asio::io_context& _IOcontext;
			std::set<boost::shared_ptr<TcpClient>> _clients;
			std::map<RType::Common::Rfc::TcpCode, bool (TcpClientManager::*)(boost::shared_ptr<TcpClient>, const Common::Tcp::Header*)> _functionPointers;
			std::set<boost::shared_ptr<Room>> _rooms;

			Common::FileSystemWatcher::RTypeFileSystemWatcher _systemWatcher;
			std::vector<std::string> _sharedLibrairiesPaths;
		};
	}
}