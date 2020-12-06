// Project includes
#include "MainWindow.hpp"

// Qt includes
#include <QApplication>

using namespace Babel::Client::UserInterface;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w((Babel::Common::ConnectionCredentials()));
    return a.exec();
}
