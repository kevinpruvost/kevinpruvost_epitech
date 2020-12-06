#include <QObject>
#include <QString>
#include <string>

/**
 * @brief Interface class of Tcp Sockets based on QtNetwork.
 */
class ITcpSocket : public QObject
{
    Q_OBJECT

public:
    virtual bool connectToServer() = 0;
    virtual bool isConnected() = 0;

protected:
    virtual void readIncomingData() = 0;

    virtual bool sendData(const QString& data) = 0;
    virtual bool sendData(const std::string& data) = 0;
};
