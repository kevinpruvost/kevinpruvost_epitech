#include "ATcpSocket.hpp"

#include <iostream>

ATcpSocket::ATcpSocket(const QString &targetIpAdress, const quint16 targetPort)
    : ipAdress(targetIpAdress)
    , port(targetPort)
    , _tcpSocket(new QTcpSocket)
{
    QObject::connect(_tcpSocket, &QAbstractSocket::readyRead, this, &ATcpSocket::readIncomingData);
}

ATcpSocket::~ATcpSocket()
{

}

bool ATcpSocket::connectToServer()
{
    _tcpSocket->connectToHost(ipAdress, port);
    connected = _tcpSocket->waitForConnected(10000);
    return connected;
}

bool ATcpSocket::isConnected()
{
    return connectToServer();
}

bool ATcpSocket::sendData(const QString &data)
{
    if (_tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        _tcpSocket->write(data.toLocal8Bit().data());
        return _tcpSocket->waitForBytesWritten();
    }
    else {
        qDebug() << "Didn't manage to send data, socket state is not equal to connected";
        return false;
    }
}

bool ATcpSocket::sendData(const std::string &data)
{
    if (_tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        std::cout << data.c_str() << std::endl;
        _tcpSocket->write(data.c_str());
        return _tcpSocket->waitForBytesWritten();
    }
    else {
        qDebug() << "Didn't manage to send data, socket state is not equal to connected";
        return false;
    }
}
