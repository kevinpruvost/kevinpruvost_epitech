#include "IncomingCallWindow.hpp"
#include "ui_IncomingCallWindow.h"

using namespace Babel::Client::UserInterface;

IncomingCallWindow::IncomingCallWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IncomingCallWindow)
{
    ui->setupUi(this);

    setStyleSheet(
        "QWidget {"
            "background-color: rgb(49, 58, 71);"
            "color: white;"
        "}"
    );
    ui->callerNameLabel->setStyleSheet("color: white;");
    setWindowTitle("Call");
    setWindowIcon(QIcon(":/icons/resources/babel.png"));
    setWindowFlags(Qt::WindowTitleHint);
}

IncomingCallWindow::~IncomingCallWindow()
{
    delete ui;
}

/**
 * @brief Sets the caller name.
 * @param const QString & name
 */
void IncomingCallWindow::setCallerName(const QString & name)
{
    ui->callerNameLabel->setText("Call from " + name);
    callerName = name;
}

void IncomingCallWindow::on_acceptButton_released()
{
    emit acceptCall();
}

void IncomingCallWindow::on_refuseButton_released()
{
    emit refuseCall();
}
