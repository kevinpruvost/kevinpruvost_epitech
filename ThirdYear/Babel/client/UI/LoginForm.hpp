#pragma once

// Project includes
#include "TcpSocket.hpp"

#include <QWidget>

namespace Ui {
class LoginForm;
}

namespace Babel
{
namespace Client
{
namespace UserInterface
{
    /**
     * @brief Contains a login form, letting the client put his username & password and signing in/loging in or just quit.
     */
    class LoginForm : public QWidget
    {
        Q_OBJECT

    public:
        explicit LoginForm(TcpSocket & tcpSocket, QWidget *parent = nullptr);
        ~LoginForm();

        void signIn();
        void quit();

        void beginConnect();

    signals:
        void trySignIn(QString username, QString password);
        void signalBeginConnect();
        void connectionToServerResult(bool result);

    private slots:
        void on_quitButton_released();
        void on_signInButton_released();
        void on_usernameBar_returnPressed();
        void on_passwordBar_returnPressed();
        void performConnectionToServer();

    public:
        QString username;
        QString password;
        TcpSocket & _tcpSocket;

    private:
        Ui::LoginForm *ui;
    };
}; // !Babel::Client::UserInterface
}; // !Babel::Client
}; // !Babel
