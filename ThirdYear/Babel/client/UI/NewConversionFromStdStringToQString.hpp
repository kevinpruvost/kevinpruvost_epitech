#pragma once

#include <QString>
#include <string>

namespace Babel
{
namespace Client
{
namespace UserInterface
{
    QString QStringFromStdString(const std::string & str);
    std::string QStringToStdString(const QString & str);
}; // !Babel::Client::UserInterface
}; // !Babel::Client
}; // !Babel
