/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Client
*/

#pragma once

#include <string>

//project includes
#include "NetworkClient/ClientTCP.hpp"
#include "NetworkClient/ClientUDP.hpp"

#include "Engine/REngine.hpp"
#include "Game/GamePage/Controller.hpp"

namespace RType
{
namespace Common
{
namespace Client
{
    class Client {
        public:
            Client(boost::asio::io_context & context, const std::string & ip, unsigned short port);
            ~Client();

            void linkEngine(Engine::REngine* engine);

            /* Network */
            void getDataTCP(void * data, size_t size);
            void getDataUDP(void * data, size_t size);

            void startNetwork();

            //TCP send
            void sendLogin(const std::string & roomId);
    
            //TCP receive
            void receiveLoginAnswer(char * buffer);
            void receiveError(char * buffer);
            void receiveUnknown(char * buffer);

            //UDP send
            void sendUsername(const std::string & name);
            void sendInput(RType::Common::Rfc::InputCode input);
            void sendXYInput(RType::Common::Rfc::InputCode input, float inputX, float inputY);
            void sendReady();
            void sendLogout();

            //UDP receive
            void receiveDelete(char * buffer);
            void receiveUpdate(char *buffer);
            void receiveCreateEntities(char *buffer);
            void receiveCreateComponents(char *buffer);
            void receiveGameStarted(char *buffer);

            void stopEngineError();

            ClientTCP & getTCPSocket() {return __tcp;};
            ClientUDP & getUDPSocket() {return __udp;};   

        private:
            ClientTCP __tcp;
            ClientUDP __udp;

            std::vector<unsigned char> __dataTCP;
            std::vector<unsigned char> __dataUDP;
            size_t __readedTCP;

            Engine::REngine * __engine;

            //room
            char __roomID[ROOM_ID_SIZE];
    };
}; // !RType::Common::Client
}; // !RType::Common
}; // !RType