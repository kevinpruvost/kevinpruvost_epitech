#include "NewConversionFromStdStringToQString.hpp"

using namespace Babel::Client::UserInterface;

/**
 * @brief Used to get around problems with qt/std libs conflicts.
 * @param const std::string & str
 * @return QString
 */
QString Babel::Client::UserInterface::QStringFromStdString(const std::string & str)
{
    return str.c_str();
}

/**
 * @brief Used to get around problems with qt/std libs conflicts.
 * @param const QString & str
 * @return std::string
 */
std::string QStringToStdString(const QString &str)
{
    return str.toLocal8Bit().data();
}
