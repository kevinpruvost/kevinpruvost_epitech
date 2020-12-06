#pragma once

#include <array>
#include <string>

namespace Babel
{
    namespace Common
    {
        /**
         *  @brief Contains default ip and ports used by the Babel.
         */
        namespace Constants
        {
            constexpr const auto defaultIp = "127.0.0.1";
            constexpr const uint16_t defaultPort = 0;

            constexpr const uint16_t referencePort = 26517;
        }

        /**
         * @brief Contains ip and port.
         */
        class ConnectionCredentials {
        public:
            ConnectionCredentials(uint16_t Port  = Constants::defaultPort,
                                  std::string IP = Constants::defaultIp) : _PortOfConnection(Port), _IPOfConnection(IP) {}
            ~ConnectionCredentials() {}
            uint16_t getPort() const { return _PortOfConnection; }
            void setPort(uint16_t port) { _PortOfConnection = port; }
            const std::string& getIP() const { return _IPOfConnection; }
            void setIP(const std::string& Ip) { _IPOfConnection = Ip; }
            bool operator==(const ConnectionCredentials& ConnectionCredentials) const { return ConnectionCredentials.getPort() == this->getPort() && ConnectionCredentials.getIP() == this->getIP(); }
        private:
            uint16_t _PortOfConnection;
            std::string _IPOfConnection;
        };
    }
}

