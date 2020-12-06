/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** NetworkModule
*/

#include "NetworkModule.hpp"

NetworkModule::NetworkModule()
{
}

NetworkModule::~NetworkModule()
{
}

bool NetworkModule::parsing()
{
    _lNetwork.clear();
    std::string buff;
    std::ifstream myfile("/proc/net/dev");

    if (!myfile.is_open()) {
        std::cerr << "/proc/net/dev" << " can't be opened" << std::endl;
        return false;
    }
    std::getline(myfile, buff);
    std::getline(myfile, buff);
    while(std::getline(myfile, buff)) {
        char *parsed = strtok((char *)buff.c_str(), ": \t");
        std::vector<char *> lParsed;
        while (parsed != NULL)
        {
            lParsed.push_back(parsed);
            parsed = std::strtok(NULL, ": \t");
        }
        _lNetwork.push_back(NetworkModule::Network(lParsed[0], atoi(lParsed[1]), atoi(lParsed[2]), atoi(lParsed[9]), atoi(lParsed[10])));
    }
    myfile.close();
    return (true);
}

std::vector<NetworkModule::Network> NetworkModule::getNetworkList() const
{
    return (_lNetwork);
}

NetworkModule::Network::Network(const std::string &pName,
                          const int &pReceiveBytes, 
                          const int &pReceivePackets, 
                          const int &pTrransmitBytes, 
                          const int &pTransmitPackets)
: _interfaceName(pName), _receiveBytes(pReceiveBytes), 
_receivePackets(pReceivePackets), _transmitBytes(pTrransmitBytes), 
_transmitPackets(pTransmitPackets)
{
    //std::cout << "Name : " << _interfaceName << std::endl;
    //std::cout << "Received Bytes : " <<_receiveBytes << std::endl;
    //std::cout << "Received Packets : " << _receivePackets << std::endl;
    //std::cout << "Transmitted Bytes : " << _transmitBytes << std::endl;
    //std::cout << "Transmitted Packets : " << _transmitPackets << std::endl;
}

NetworkModule::Network::~Network()
{
}

std::string NetworkModule::Network::getName() const
{
    return(this->_interfaceName);
}

int NetworkModule::Network::getReceivedBytes() const
{
    return (this->_receiveBytes);
}

int NetworkModule::Network::getReceivedPackets() const
{
    return (this->_receivePackets);
}

int NetworkModule::Network::getTransmitBytes() const
{
    return (this->_transmitBytes);
}

int NetworkModule::Network::getTransmitPackets() const
{
    return (this->_transmitPackets);
}