// Project includes
#include "ITcpSocket.hpp"

// Qt includes
#include <QTcpSocket>
#include <QHash>
#include <QHostAddress>
#include <QDataStream>

// C++ includes
#include <string>

/**
 * @brief Abstract class of Tcp Sockets based on QtNetwork.
 */
class ATcpSocket : public ITcpSocket
{
    Q_OBJECT

public:
    ATcpSocket(const QString& targetIpAdress, const quint16 targetPort);
    virtual ~ATcpSocket();

public:
    bool connectToServer() override;
    bool isConnected() override;

signals:
    void dataReceived();

protected:
    bool sendData(const QString& data) override;
    bool sendData(const std::string& data) override;

public:
    const QString ipAdress;
    const quint16 port;

    bool connected = false;

protected:
    QTcpSocket * _tcpSocket;
    QByteArray _buffer;
    bool _reading = false;
};
