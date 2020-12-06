#include "TcpSocket.hpp"

// Qt includes
#include <QApplication>
#include <QMessageBox>
#include <QThread>

using namespace Babel::Common;
using namespace Babel::Client::UserInterface;

TcpSocket::TcpSocket(const QString &ipAdresss, const quint16 portt)
    : ATcpSocket(ipAdresss, portt)
{
}

TcpSocket::~TcpSocket()
{
}

/**
 * @brief Sends a seralized packet.
 * @param const Babel::Common::PacketsDataBinarySerialized & packet
 * @return bool
 */
bool TcpSocket::sendData(const Babel::Common::PacketsDataBinarySerialized & packet)
{
    if (_tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        _tcpSocket->write((char *)(&packet), packet.size);
        return _tcpSocket->waitForBytesWritten();
    }
    else
    {
        qDebug() << "Didn't manage to send data, socket state is not equal to connected";
        return false;
    }
}

/**
 * @brief Depending on a command id and arguments, it will traduce it to the tcp socket then send the data to the server.
 * @param const Babel::Rfc::Code code
 * @param const std::vector<std::string> & arguments
 */
void TcpSocket::sendRequest(const Babel::Rfc::Code code, const std::vector<std::string> &arguments)
{
    Babel::Common::PacketsDataBinary dataPacket(code, arguments);
    auto packetSerialized = dataPacket.serializeData();
    if (!sendData(packetSerialized))
        QMessageBox::warning(nullptr, "Request error", "Couldn't send request to server.");
}

//-----------------------------------------------------------------------------------------------------------------
//
//                                  SEND
//
//-----------------------------------------------------------------------------------------------------------------

/**
 * @brief Sends an OK request.
 * @param const Babel::Rfc::Code commandId
 */
void TcpSocket::sendRequest_Ok(const Babel::Rfc::Code commandId)
{
    sendRequest(Babel::Rfc::Code::CS_OK, {std::to_string(commandId)});
    qDebug() << "Sent OK Request to Server.";
}

/**
 * @brief Sends an Error request.
 * @param const std::string & commandId
 * @param const std::string & message
 */
void TcpSocket::sendRequest_Error(const Babel::Rfc::Code commandId, const std::string & message)
{
    sendRequest(Babel::Rfc::Code::CS_ERROR, {std::to_string(commandId), message});
    qDebug() << "Sent Error Request to Server.";
}

/**
 * @brief Sends a Login request.
 * @param const std::string & username
 * @param const std::string & password
 */
void TcpSocket::sendRequest_Login(const std::string &username, const std::string &password)
{
    sendRequest(Babel::Rfc::Code::CS_LOGIN, {username, password});
    std::cerr << "Sent Login Request to Server with parameters : " << username << " and (in hash SHA-256) " << password << ".";
}

/**
 * @brief Sends a Logout request.
 */
void TcpSocket::sendRequest_Logout()
{
    sendRequest(Babel::Rfc::Code::CS_LOGOUT);
    qDebug() << "Sent Logout Request to Server.";
}

/**
 * @brief Sends a Call request.
 * @param const std::string & userId
 * @param const std::string & ip
 * @param const uint16_t port
 */
void TcpSocket::sendRequest_Call(const std::string & userId, const std::string &ip, const uint16_t port)
{
    sendRequest(Babel::Rfc::Code::CS_CALL, {userId, ip, std::to_string(port)});
    qDebug() << "Sent Call Request to Server with paramters :" << QStringFromStdString(userId) << "," << QStringFromStdString(ip) << "and" << port << ".";
}

/**
 * @brief Sends a Call_Answer request.
 * @param const QString & userId
 * @param const QString & ip
 * @param const uint16_t port
 */
void TcpSocket::sendRequest_CallAnswer(const std::string & userId, const std::string &ip, const uint16_t port)
{
    sendRequest(Babel::Rfc::Code::CS_CALL_ANSWER, {userId, ip, std::to_string(port)});
    qDebug() << "Sent Call Answer Request to Server with paramters :" << QStringFromStdString(userId) << "," << QStringFromStdString(ip) << "and" << port << ".";
}

/**
 * @brief Sends a Call_End request.
 * @param const QString & userId
 */
void TcpSocket::sendRequest_CallEnd(const std::string &userId)
{
    sendRequest(Babel::Rfc::Code::CS_CALL_END, {userId});
    qDebug() << "Sent Call End to Server with paramters :" << QStringFromStdString(userId) << ".";
}

/**
 * @brief Sends a Contact request.
 * @param const QString & username
 */
void TcpSocket::sendRequest_Contact(const std::string &username)
{
    sendRequest(Babel::Rfc::Code::CS_CONTACT, {username});
    qDebug() << "Sent Contact Request to Server with parameters :" << QStringFromStdString(username) << ".";
}

/**
 * @brief Sends a Msg request.
 * @param const QString & userId
 * @param const QString & message
 */
void TcpSocket::sendRequest_Msg(const std::string & userId, const std::string &message)
{
    sendRequest(Babel::Rfc::Code::CS_MSG, {userId, message});
    qDebug() << "Sent Msg Request to Server with parameters :" << QStringFromStdString(userId) << "and" << QStringFromStdString(message) << ".";
}

/**
 * @brief Sends a Ping request.
 */
void TcpSocket::sendRequest_Ping()
{
    sendRequest(Babel::Rfc::Code::CS_PING);
    qDebug() << "Sent Ping Request to Server.";
}

/**
 * @brief Sends an Unknown request.
 */
void TcpSocket::sendRequest_Unknown()
{
    sendRequest(Babel::Rfc::Code::UNKNOWN);
    qDebug() << "Sent Unknown Request to Server.";
}

//-----------------------------------------------------------------------------------------------------------------
//
//                                  READ
//
//-----------------------------------------------------------------------------------------------------------------

/**
 * @brief Reads data, stores the requests into a vector, and emits a signal to let other objects know that requests just arrived.
 */
void TcpSocket::readIncomingData()
{
    if (_reading)
        return;

    _reading = true;

    // Reads socket.
    while (_tcpSocket->bytesAvailable() > 0 && _buffer.size() < (int)Babel::Common::PacketsDataBinary::PacketsDataBinarySerializedMinimumSize)
    {
        if (_tcpSocket->bytesAvailable() <= 0)
            _tcpSocket->waitForReadyRead();
        _buffer += _tcpSocket->readAll();
    }

    if (_buffer.size() < (int)Babel::Common::PacketsDataBinary::PacketsDataBinarySerializedMinimumSize)
        return;

    // Reads all requests and keeping the last part if there's no packet separator at the end.
    while (_buffer.size() >= (int)Babel::Common::PacketsDataBinary::PacketsDataBinarySerializedMinimumSize)
    {
        try
        {
            requests.append(PacketsDataBinary::deserializeData(_buffer.data(), Babel::Common::PacketsDataBinary::PacketsDataBinarySerializedMinimumSize));
        }
        catch (const std::exception &)
        {
            sendRequest_Unknown();
        }
        _buffer = _buffer.right(_buffer.size() - Babel::Common::PacketsDataBinary::PacketsDataBinarySerializedMinimumSize);
    }
    _reading = false;
    emit dataReceived();
}

void TcpSocket::beginConnect()
{
    emit signalBeginConnect();
}
