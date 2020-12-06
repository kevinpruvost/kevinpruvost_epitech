/*
** EPITECH PROJECT, 2020
** Babel server main
** File description:
** Where the program starts
*/

#include "networktools/BabelServer.hpp"

int main(int ac, char** av)
{
    try {
        boost::asio::io_context io_context;
        Babel::Server::BabelServer * server = nullptr;

        if (ac > 1) {
            server = new Babel::Server::BabelServer(io_context, std::string(av[1]), Babel::Common::Constants::referencePort);
        } else {
            server = new Babel::Server::BabelServer(io_context, Babel::Common::Constants::referencePort);
        }
        io_context.run();

        if (server)
            delete server;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "Program closed successfully" << std::endl;
    return (EXIT_SUCCESS);
}