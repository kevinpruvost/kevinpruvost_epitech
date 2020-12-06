/*
** EPITECH PROJECT, 2020
** cpp_rush3_2019
** File description:
** NetworkModule
*/

#ifndef NETWORKMODULE_HPP_
#define NETWORKMODULE_HPP_

#include "IMonitorModule.hpp"

class NetworkModule: public IMonitorModule {
	public:
        class Network {
            public:
                Network(const std::string &pName,
                     const int &pReceiveBytes,
                     const int &pReceivePackets,
                     const int &pTrransmitBytes, 
                     const int &pTransmitPackets);
                ~Network();

                std::string getName() const;
                int getReceivedBytes() const;
                int getReceivedPackets() const;
                int getTransmitBytes() const;
                int getTransmitPackets() const;
            private:
                std::string _interfaceName;
                int _receiveBytes;
                int _receivePackets;
                int _transmitBytes;
                int _transmitPackets;
        };
		NetworkModule();
		~NetworkModule();

        bool parsing() override;
        std::vector<NetworkModule::Network> getNetworkList() const;
	protected:
	private:
        std::vector<NetworkModule::Network> _lNetwork;
};

#endif /* !NETWORKMODULE_HPP_ */
