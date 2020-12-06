#include "ExternalIpGetter.hpp"

using namespace Babel::Client::UserInterface;

ExternalIpGetter::ExternalIpGetter(bool active)
    : _active(active)
{
    if (!active)
        return;
    _manager = new QNetworkAccessManager(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), SLOT(gotReply(QNetworkReply*)));
    _manager->get(QNetworkRequest(QUrl("https://api.ipify.org?format=json")));
}

ExternalIpGetter::~ExternalIpGetter()
{
    if (_active)
        delete _manager;
}

/**
 * @brief Gets the external ip.
 * @return QString
 */
QString ExternalIpGetter::getIp() const
{
    return _ip;
}

void ExternalIpGetter::gotReply(QNetworkReply * networkReply)
{
    networkReply->deleteLater();
    _ip = QJsonDocument::fromJson(networkReply->readAll()).object().value("ip").toString();
}
