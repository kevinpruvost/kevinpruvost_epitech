/*
** EPITECH PROJECT, 2020
** Babel server main
** File description:
** Where the program starts
*/

// Project includes
#include "TcpServer.hpp"

int main(int ac, char** av)
{
	(void)ac;
	(void)av;
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	try {
		boost::asio::io_context io_context;
		RType::Server::TcpServer server(io_context, 7171);
		server.startAccept();
		io_context.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << "Server closed successfully !" << std::endl;
    return EXIT_SUCCESS;
}