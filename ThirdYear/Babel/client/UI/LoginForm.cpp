#include "LoginForm.hpp"
#include "ui_LoginForm.h"

// Qt includes
#include <QMessageBox>

using namespace Babel::Client::UserInterface;

LoginForm::LoginForm(TcpSocket &tcpSocket, QWidget *parent) :
    QWidget(parent),
    _tcpSocket(tcpSocket),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    ui->connectionWidget->hide();
    ui->connectingToServerLabel->show();

    QObject::connect(&_tcpSocket, &TcpSocket::signalBeginConnect, this, &LoginForm::performConnectionToServer);
}

LoginForm::~LoginForm()
{
    delete ui;
}

/**
 * @brief Emits the signal trySignIn with username and passwords in parameters.
 */
void LoginForm::signIn()
{
    username = ui->usernameBar->text();
    password = ui->passwordBar->text();

    if (username.isEmpty() && password.isEmpty())
    {
        QMessageBox::warning(this, "No username & password", "Please enter your username and password.");
        return;
    }

    if (password.isEmpty())
    {
        QMessageBox::warning(this, "No password", "Please enter your password.");
        return;
    }

    if (username.isEmpty())
    {
        QMessageBox::warning(this, "No username", "Please enter your username.");
        return;
    }

    emit trySignIn(username, password);
}

/**
 * @brief Connects to the server.
 */
void LoginForm::performConnectionToServer()
{
    bool result = _tcpSocket.connectToServer();
    emit connectionToServerResult(result);
    ui->connectionWidget->show();
    ui->connectingToServerLabel->hide();
}

/**
 * @brief Quits the application.
 */
void LoginForm::quit()
{
    qApp->quit();
}

/**
 * @brief Begins connection, is meant to be used in a multithread way.
 */
void LoginForm::beginConnect()
{
    emit signalBeginConnect();
}

void LoginForm::on_quitButton_released()
{
    quit();
}

void LoginForm::on_signInButton_released()
{
    signIn();
}

void LoginForm::on_usernameBar_returnPressed()
{
    on_signInButton_released();
}

void LoginForm::on_passwordBar_returnPressed()
{
    on_signInButton_released();
}

