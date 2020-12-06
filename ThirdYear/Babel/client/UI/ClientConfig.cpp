#include "ClientConfig.hpp"

using namespace Babel::Client::UserInterface;

#include <iostream>

ClientConfig::ClientConfig(const QString & dirName, const QString & filename)
    : fileName(dirName + "/" + filename)
    , _file(fileName)
{
    QDir dir(dirName);

    if (!dir.exists())
    {
        if (!dir.mkdir(dir.absolutePath()))
        {
            std::string errorMsg = "Can't create config folder in ";
            errorMsg += dir.absolutePath().toLocal8Bit().data();
            throw EXCEPTION(errorMsg.c_str());
            return;
        }
    }

    opened = _file.open(QIODevice::ReadOnly);

    if (!opened) return;

    _content = _file.readAll();
    jsonDocument = QJsonDocument::fromJson(_content.toUtf8());
}

ClientConfig::~ClientConfig()
{
    _file.close();

    _file.setFileName(fileName);

    if (_file.open(QIODevice::WriteOnly | QFile::Truncate))
        _file.write(jsonDocument.toJson());
}
