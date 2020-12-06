#pragma once

// Project includes
#include "Exception.hpp"

// Qt includes
#include <QFile>
#include <QDir>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

namespace Babel
{
namespace Client
{
namespace UserInterface
{
    /**
     * @brief Contains every client config informations (json, filename, ...).
     */
    class ClientConfig
    {
    public:
        ClientConfig(const QString & dirName, const QString & fileName);
        ~ClientConfig();

    public:
        QJsonDocument jsonDocument;
        bool opened = false;
        QString fileName;

    private:
        QString _content;
        QFile _file;
    };
}; // !Babel::Client::UserInterface
}; // !Babel::Client
}; // !Babel
