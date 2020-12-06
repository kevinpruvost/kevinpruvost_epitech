#pragma once

// Qt includes
#include <QJsonDocument>
#include <QJsonObject>
#include <QHostAddress>
#include <QNetworkReply>

namespace Babel
{
namespace Client
{
namespace UserInterface
{
    /**
     * @brief Gets the public external ip using API requests.
     */
    class ExternalIpGetter : public QObject
    {
        Q_OBJECT

    public:
        ExternalIpGetter(bool active);
        ~ExternalIpGetter();

    public:
        QString getIp() const;

    private slots:
        void gotReply(QNetworkReply* networkReply);

    private:
        QString _ip;
        bool _active;

    private:
        QNetworkAccessManager * _manager;
    };
}; // !Babel::Client::UserInterface
}; // !Babel::Client
}; // !Babel
