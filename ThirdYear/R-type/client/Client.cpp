/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Client
*/

#include "Client.hpp"

using namespace RType::Common::Client;

Client::Client(boost::asio::io_context & context, const std::string & ip, unsigned short port)
    : __tcp ( ClientTCP(context, ip, port) )
    , __udp ( ClientUDP(context, ip) )
{
    __tcp.getCallbackData([this](void * data, size_t size) {
        Client::getDataTCP(data, size);
    });

    __tcp.setCallbackError([this]() {
        Client::stopEngineError();
    });

    __udp.setCallbackError([this]() {
        Client::stopEngineError();
    });

    __udp.getCallbackData([this](void * data, size_t size){
        Client::getDataUDP(data, size);
    });

    __tcp.readData();
    __readedTCP = 0;

    std::memset(__roomID, 0, ROOM_ID_SIZE);
}

Client::~Client()
{
}

void Client::linkEngine(Engine::REngine* engine)
{
    __engine = engine;
}

void Client::stopEngineError()
{   
    if (__engine) {
        __engine->Stop(true);
    }
}

/* TCP get data */

void Client::getDataTCP(void * data, size_t size)
{
    unsigned char * castdata = (unsigned char *)data;
    RType::Common::Tcp::Header h;

    for (size_t i = 0; i < size; ++i) {
        __dataTCP.push_back(castdata[i]);
    }

    if (__dataTCP.size() < sizeof(RType::Common::Tcp::Header))
        return;
    
    __readedTCP += __dataTCP.size();

    while (__readedTCP > 0) {
        std::memset(&h, 0, sizeof(RType::Common::Tcp::Header));
        std::memcpy(&h, __dataTCP.data(), sizeof(RType::Common::Tcp::Header));

        if (h.size > __readedTCP)
            return;
        std::cout << "Je suis TCP func : " << (int)h.code << std::endl;
        switch (h.code)
        {
        case RType::Common::Rfc::TcpCode::LoginAnswer:
            receiveLoginAnswer((char *)__dataTCP.data());
            break;

        case RType::Common::Rfc::TcpCode::Error:
            receiveError((char *)__dataTCP.data());
            break;

        case RType::Common::Rfc::TcpCode::Unknown:
            receiveUnknown((char *)__dataTCP.data());
            break;

        default:
            __dataTCP.clear();
            return; //Revoir le cas là
        }
        __dataTCP = std::vector<unsigned char>(__dataTCP.begin() + h.size, __dataTCP.end());
    }
}

/* TCP get data */

void Client::getDataUDP(void * data, size_t size)
{
    unsigned char * castdata = (unsigned char *)data;
    RType::Common::Udp::Header h;

    for (size_t i = 0; i < size; ++i) {
        __dataUDP.push_back(castdata[i]);
    }

    while (__dataUDP.size() > 0) {

        if (__dataUDP.size() < sizeof(RType::Common::Udp::Header)) {
            __dataUDP.clear();
            return;
        }
    
        std::memset(&h, 0, sizeof(RType::Common::Udp::Header));
        std::memcpy(&h, __dataUDP.data(), sizeof(RType::Common::Udp::Header));

        if (h.size > __dataUDP.size()) {
            __dataUDP.clear();
            return;
        }
        std::cout << "Je suis UDP func : " << (int)h.code << std::endl;
        switch (h.code)
        {
        case RType::Common::Rfc::UdpCode::Delete:
            receiveDelete((char *)__dataUDP.data());
            break;

        case RType::Common::Rfc::UdpCode::CreateEntity:
            receiveCreateEntities((char *)__dataUDP.data());
            break;
        
        case RType::Common::Rfc::UdpCode::CreateComponent:
            receiveCreateComponents((char *)__dataUDP.data());
            break;

        case RType::Common::Rfc::UdpCode::Update:
            receiveUpdate((char *)__dataUDP.data());
            break;
        case RType::Common::Rfc::UdpCode::GameStartedAnswer:
            receiveGameStarted((char *)__dataUDP.data());
            break;
        default:
            __dataUDP.clear();
            return;
        }
        __dataUDP = std::vector<unsigned char>(__dataUDP.begin() + h.size, __dataUDP.end());
    }
    __dataUDP.clear();
}

/*  TCP Request */

void Client::sendLogin(const std::string & roomId)
{
    Common::Tcp::LoginRequest * log = new Common::Tcp::LoginRequest();

    log->header.code = RType::Common::Rfc::TcpCode::Login;
    log->header.size = sizeof(RType::Common::Tcp::LoginRequest);

    std::memset(log->roomId, 0, ROOM_ID_SIZE);
    std::memcpy(log->roomId, roomId.c_str(), roomId.size() > ROOM_ID_SIZE ? ROOM_ID_SIZE : roomId.size());

    bool error = __tcp.sendData((void *)log, sizeof(RType::Common::Tcp::LoginRequest));

    delete log;

    if (__engine && !error)
        __engine->Stop(true);
}

void Client::sendLogout()
{
    Common::Tcp::LogoutRequest * log = new Common::Tcp::LogoutRequest();

    log->header.code = RType::Common::Rfc::TcpCode::Logout;
    log->header.size = sizeof(RType::Common::Tcp::LogoutRequest);
    
    std::memset(log->roomId, 0, ROOM_ID_SIZE);
    std::memcpy(log->roomId, __roomID, ROOM_ID_SIZE);

    bool error = __udp.sendData((void *)log, sizeof(RType::Common::Tcp::LogoutRequest));

    //TODO call SFML

    delete log;

    if (__engine && error)
        __engine->Stop(true);
}

/* UDP Request */

void Client::sendUsername(const std::string & name)
{
    Common::Udp::UsernameRequest * log = new Common::Udp::UsernameRequest();
    int size = name.size() > USERNAME_LENGTH ? USERNAME_LENGTH - 1 : name.size();

    log->header.code = RType::Common::Rfc::UdpCode::Username;
    log->header.size = sizeof(RType::Common::Udp::UsernameRequest);

    std::memset(log->username, 0, USERNAME_LENGTH);
    std::memcpy(log->username, name.c_str(), size);

    bool error = __udp.sendData((void *)log, sizeof(RType::Common::Udp::UsernameRequest));

    delete log;

    if (__engine && error)
        __engine->Stop(true);
}

void Client::sendInput(RType::Common::Rfc::InputCode input)
{
    Common::Udp::InputRequest * log = new Common::Udp::InputRequest();

    log->header.code = RType::Common::Rfc::UdpCode::Input;
    log->header.size = sizeof(RType::Common::Udp::InputRequest);

    log->inputCode = input;

    bool error = __udp.sendData((void *)log, sizeof(RType::Common::Udp::InputRequest));

    delete log;

    if (__engine && error)
        __engine->Stop(true);
}

void Client::sendXYInput(RType::Common::Rfc::InputCode input, float inputX, float inputY)
{
    Common::Udp::InputXYRequest * log = new Common::Udp::InputXYRequest();

    log->header.code = RType::Common::Rfc::UdpCode::InputXY;
    log->header.size = sizeof(RType::Common::Udp::InputXYRequest);

    log->inputCode = input;
    log->inputValue = inputX;
    log->inputValue2 = inputY;

    bool error = __udp.sendData((void *)log, sizeof(RType::Common::Udp::InputXYRequest));

    delete log;

    if (__engine && error)
        __engine->Stop(true);
}

void Client::sendReady()
{
    Common::Udp::ReadyRequest * log = new Common::Udp::ReadyRequest();

    log->header.code = RType::Common::Rfc::UdpCode::ReadyRequest;
    log->header.size = sizeof(RType::Common::Udp::ReadyRequest);

    bool error = __udp.sendData((void *)log, sizeof(RType::Common::Udp::ReadyRequest));

    //TODO call sfml

    delete log;

    if (__engine && !error)
        __engine->Stop(true);
}

/* TCP Receive Request */
void Client::receiveLoginAnswer(char * buffer)
{
    std::cout << "answer" << std::endl;
    RType::Common::Tcp::LoginOkAnswer l;

    l.header.code = RType::Common::Rfc::TcpCode::LoginAnswer;
    l.header.size = sizeof(RType::Common::Tcp::LoginOkAnswer);

    std::memcpy(&l.port , buffer + sizeof(RType::Common::Tcp::Header), sizeof(unsigned short));
    std::memset(&l.roomId, 0, ROOM_ID_SIZE);
    std::memcpy(&l.roomId, buffer + sizeof(RType::Common::Tcp::Header) + sizeof(unsigned short), ROOM_ID_SIZE);

    std::memset(__roomID, 0, ROOM_ID_SIZE);
    std::memcpy(__roomID, buffer + sizeof(RType::Common::Tcp::Header) + sizeof(unsigned short), ROOM_ID_SIZE);

    //TODO call SFML

    __udp.bindSocket(l.port);
    sendReady(); // Ping UDP server;

    __readedTCP -= sizeof(RType::Common::Tcp::LoginOkAnswer);

    if (!__engine)
        throw CRITICAL_EXCEPTION("Engine not accessible");

    __engine->Pause(true);
    __engine->WaitForPause();
    __engine->Clear();
    __engine->CreateEntity<Engine::Controller>(*__engine);
    __engine->Pause(false);
}

void Client::receiveError(char * buffer)
{
    RType::Common::Tcp::ErrorRequest l;

    l.header.code = RType::Common::Rfc::TcpCode::Error;
    l.header.size = sizeof(RType::Common::Tcp::ErrorRequest);

    std::memcpy(&l.commandId, buffer + sizeof(RType::Common::Tcp::Header), sizeof(RType::Common::Rfc::TcpCode));
    std::memset(&l.message, 0, 64);
    std::memcpy(&l.message, buffer + sizeof(RType::Common::Tcp::Header) + sizeof(RType::Common::Rfc::TcpCode), 64);

    //TODO call sfml

    __readedTCP -= sizeof(RType::Common::Tcp::ErrorRequest);
}

void Client::receiveUnknown(char * buffer)
{
    //call SFML
    __readedTCP -= sizeof(RType::Common::Tcp::UnknownRequest);
}

/* UDP Receive Request */

void Client::receiveDelete(char * buffer)
{
    RType::Common::Udp::Entities::DeleteRequest l;

    l.header.code = RType::Common::Rfc::UdpCode::Delete;
    l.header.size = sizeof(RType::Common::Udp::Entities::DeleteRequest);

    std::memcpy(&l.entityId, buffer + sizeof(RType::Common::Udp::Header), sizeof(unsigned int));

    __engine->Pause(true);
    __engine->WaitForPause();
    __engine->DestroyEntityId(l.entityId);
    __engine->Pause(false);
}

void Client::receiveUpdate(char *buffer)
{
    RType::Common::Udp::Entities::UpdateRequest l;

    std::memset(&l, 0, sizeof(RType::Common::Udp::Entities::UpdateRequest));
    std::memcpy(&l.header, buffer, sizeof(RType::Common::Udp::Header));
    std::memcpy(&l.entityId, buffer + sizeof(RType::Common::Udp::Header), sizeof(unsigned int));
    std::memcpy(&l.dataSize, buffer + sizeof(RType::Common::Udp::Header) + sizeof(unsigned int), sizeof(unsigned int));
    std::memcpy(&l.typeId, buffer + sizeof(RType::Common::Udp::Header) + sizeof(unsigned int) + sizeof(unsigned int), sizeof(Rfc::ComponentTypeId));
    std::memcpy(&l.datas, buffer + sizeof(RType::Common::Udp::Header) + sizeof(unsigned int) + sizeof(unsigned int) + sizeof(Rfc::ComponentTypeId), l.dataSize);

    __engine->Pause(true);
    __engine->WaitForPause();
    __engine->UpdateComponent(l.entityId, l.typeId, l.datas);
    __engine->Pause(false);
}

void Client::receiveCreateEntities(char *buffer)
{
    RType::Common::Udp::Entities::CreateEntity l;

    l.header.code = RType::Common::Rfc::UdpCode::CreateEntity;
    l.header.size = sizeof(RType::Common::Udp::Entities::CreateEntity);

    std::memcpy(&l.id, buffer + sizeof(RType::Common::Udp::Header), sizeof(unsigned int));

    __engine->Pause(true);
    __engine->WaitForPause();
    __engine->CreateEntityWithId(l.id);
    __engine->Pause(false);
}

#include "Components/AllComponents.hpp"

void Client::receiveCreateComponents(char *buffer)
{
    RType::Common::Udp::Entities::CreateComponent l;

    l.header.code = RType::Common::Rfc::UdpCode::CreateComponent;
    l.header.size = sizeof(RType::Common::Udp::Entities::CreateComponent);

    std::memcpy(&l.entityId, buffer + sizeof(RType::Common::Udp::Header), sizeof(unsigned int));
    std::memcpy(&l.type, buffer + sizeof(RType::Common::Udp::Header) + sizeof(unsigned int), sizeof(RType::Common::Rfc::ComponentTypeId));
    std::memcpy(&l.dataSize, buffer + sizeof(RType::Common::Udp::Header) + sizeof(unsigned int) + sizeof(RType::Common::Rfc::ComponentTypeId), sizeof(unsigned int));
    std::memcpy(&l.datas, buffer + sizeof(RType::Common::Udp::Header) + sizeof(unsigned int) + sizeof(RType::Common::Rfc::ComponentTypeId) + sizeof(unsigned int), l.dataSize);

    std::map<Rfc::ComponentTypeId, std::function<void()>> constructors = {
        {Rfc::ComponentTypeId::Audio,                    [=]() { __engine->AddComponent(l.entityId, Engine::Audio(*__engine)); }},
        {Rfc::ComponentTypeId::Button,                   [=]() { __engine->AddComponent(l.entityId, Engine::Audio(*__engine)); }},
        {Rfc::ComponentTypeId::CharacterCharacteristics, [=]() { __engine->AddComponent(l.entityId, Engine::Audio(*__engine)); }},
        {Rfc::ComponentTypeId::CircleCollider,           [=]() { __engine->AddComponent(l.entityId, Engine::Audio(*__engine)); }},
        {Rfc::ComponentTypeId::Collider,                 [=]() { __engine->AddComponent(l.entityId, Engine::Audio(*__engine)); }},
        {Rfc::ComponentTypeId::KeyInput,                 [=]() { __engine->AddComponent(l.entityId, Engine::Audio(*__engine)); }},
        {Rfc::ComponentTypeId::RectangleCollider,        [=]() { __engine->AddComponent(l.entityId, Engine::Audio(*__engine)); }},
        {Rfc::ComponentTypeId::Sprite,                   [=]() { __engine->AddComponent(l.entityId, Engine::Audio(*__engine)); }},
        {Rfc::ComponentTypeId::SpriteAnimation,          [=]() { __engine->AddComponent(l.entityId, Engine::Audio(*__engine)); }},
        {Rfc::ComponentTypeId::Text,                     [=]() { __engine->AddComponent(l.entityId, Engine::Audio(*__engine)); }},
        {Rfc::ComponentTypeId::TextInput,                [=]() { __engine->AddComponent(l.entityId, Engine::Audio(*__engine)); }},
        {Rfc::ComponentTypeId::Transform,                [=]() { __engine->AddComponent(l.entityId, Engine::Audio(*__engine)); }},
        {Rfc::ComponentTypeId::UITransform,              [=]() { __engine->AddComponent(l.entityId, Engine::Audio(*__engine)); }},
        {Rfc::ComponentTypeId::Weapon,                   [=]() { __engine->AddComponent(l.entityId, Engine::Audio(*__engine)); }}
    };


    __engine->Pause(true);
    __engine->WaitForPause();
    if (constructors.find(l.type) != constructors.end())
        constructors[l.type]();
    __engine->UpdateComponent(l.entityId, l.type, l.datas);
    __engine->Pause(false);
}

void Client::receiveGameStarted(char *buffer)
{
    //TODO call SFML
}

