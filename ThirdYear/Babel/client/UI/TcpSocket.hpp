#pragma once

// Project includes
#include "ATcpSocket.hpp"
#include "QtConstants.hpp"

// Qt includes
#include <QTcpSocket>
#include <QHash>
#include <QHostAddress>
#include <QDataStream>

// C++ includes
#include <string>

namespace Babel
{
namespace Client
{
namespace UserInterface
{
    /**
     * @brief Reads and writes every data between itself and a server socket.
     */
    class TcpSocket : public ATcpSocket
    {
        Q_OBJECT

    public:
        TcpSocket(const QString & ipAdress, const quint16 port);
        ~TcpSocket();

        void sendRequest_Unknown();
        void sendRequest_Ok(const Babel::Rfc::Code commandId);
        void sendRequest_Error(const Babel::Rfc::Code commandId, const std::string &message);
        void sendRequest_Login(const std::string & username, const std::string & password);
        void sendRequest_Logout();
        void sendRequest_Call(const std::string &userId, const std::string & ip, const uint16_t port);
        void sendRequest_CallAnswer(const std::string & userId, const std::string & ip, const uint16_t port);
        void sendRequest_CallEnd(const std::string & userId);
        void sendRequest_Contact(const std::string & username);
        void sendRequest_Msg(const std::string & userId, const std::string & message);
        void sendRequest_Ping();

    public slots:
        void beginConnect();

    signals:
        void dataReceived();
        void signalBeginConnect();
        void lostConnectionWithServer();

    private:
        void readIncomingData() override;

        bool sendData(const Babel::Common::PacketsDataBinarySerialized &data);
        void sendRequest(const Babel::Rfc::Code code, const std::vector<std::string> &arguments = std::vector<std::string>());

    public:
        QList<Babel::Common::PacketsDataBinary> requests;
    };
}; // !Babel::Client::UserInterface
}; // !Babel::Client
}; // !Babel


