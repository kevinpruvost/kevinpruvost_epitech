/*
** EPITECH PROJECT, 2020
** Babel client main
** File description:
** Where the program starts
*/

// Project includes
#include "Client.hpp"
#include "MainWindow.hpp"

// Qt includes
#include <QApplication>

// C++ includes
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
using namespace boost::asio::ip;

using namespace Babel::Client::UserInterface;

int main(int argc, char ** argv)
{
    std::cout << "Welcome on the client side." << std::endl;

    /*Babel::Client::VOIP voip;
    voip.setIPandPort("127.0.0.1", 0);
    voip.setTargetIPandPort("127.0.0.1", voip.getPort());
    voip.startStream();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    voip.setMicrophoneState(false);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    voip.setMicrophoneState(true);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    voip.stopStream();
    return 0;*/

    //WindowsExecutableStop();

    Babel::Common::ConnectionCredentials connectionCredentials;
    std::string myIp = Babel::Common::Constants::defaultIp;

    connectionCredentials.setIP(Babel::Common::Constants::defaultIp);
    connectionCredentials.setPort(Babel::Common::Constants::referencePort);
    if (argc >= 2)
    {
        std::string serverIP = argv[1];
        connectionCredentials.setIP(serverIP);
    }

    std::cerr << "Server IP is : " << connectionCredentials.getIP() << ":" << connectionCredentials.getPort() << std::endl;

    QApplication a(argc, argv);
    MainWindow w(connectionCredentials, myIp);
    return a.exec();
}