#pragma once

// Project includes
#include "PacketsDataBinary.hpp"
#include "NewConversionFromStdStringToQString.hpp"
#include "ConnectionCredentials.hpp"

// Qt includes
#include <QMap>
#include <QMessageBox>
#include <QPixmap>
#include <QStandardPaths>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonArray>

namespace Babel
{
namespace Client
{
namespace UserInterface
{
namespace QtConstants
{
    constexpr const auto dateTimeFormat = "[dd/MM/yyyy hh:mm]";

    const QMap<Babel::Rfc::State, QString> iconPerContactStates =
    {
        {Babel::Rfc::State::Connected,    ":/icons/resources/connectedIcon.png"},
        {Babel::Rfc::State::Disconnected, ":/icons/resources/disconnectedIcon.png"},
        {Babel::Rfc::State::Occupied,     ":/icons/resources/occupiedIcon.png"}
    };

    const QMap<Babel::Rfc::State, QString> stringPerContactStates =
    {
        {Babel::Rfc::State::Connected,    "Connected"},
        {Babel::Rfc::State::Disconnected, "Disconnected"},
        {Babel::Rfc::State::Occupied,     "Occupied"}
    };

    namespace JsonKeys
    {
        constexpr const auto contactList = "contactList";
        constexpr const auto credentials = "credentials";
        constexpr const auto username = "username";
        constexpr const auto password = "password";
        constexpr const auto id = "id";
        constexpr const auto conversation = "conversation";
        constexpr const auto ip = "ip";
        constexpr const auto port = "port";

        const QList<const char *> contactInfoList = {
            username, id, conversation, ip, port
        };
        const QList<const char *> credentialsList = {
            username, password, ip, port
        };
    }
}; // !Babel::Client::UserInterface::QtConstants
}; // !Babel::Client::UserInterface
}; // !Babel::Client
}; // !Babel
