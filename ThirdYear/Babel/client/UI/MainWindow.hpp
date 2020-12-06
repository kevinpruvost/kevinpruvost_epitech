#pragma once

// Project UI includes
#include "Contact.hpp"
#include "ExternalIpGetter.hpp"
#include "IncomingCallWindow.hpp"
#include "ClientConfig.hpp"
#include "LoginForm.hpp"
#include "ProfileForm.hpp"

#include "VOIP.hpp"

// Qt includes
#include <QMainWindow>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace Babel
{
/**
 * @brief Contains Client's code.
 */
namespace Client
{
/**
 * @brief Contains the Client::UserInterface's code.
 */
namespace UserInterface
{
    /**
     * @brief Contains the main window, where everything is regrouped and used.
     */
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(Common::ConnectionCredentials serverCredentials, const std::string & myIP, QWidget * parent = nullptr);
        ~MainWindow();

    public:
        // Server To Client
        /**
         * @brief Does the same thing as addUser.
         * @param userID
         * @param username
         * @param state
         */
        void refreshUser(const std::string & userID, const std::string & username, const Babel::Rfc::State state) {addUser(userID, username, state, "", false);}
        void addUser(const std::string & userID, const std::string & username, const Babel::Rfc::State state, const std::string &conversation = "", bool notification = false);
        void addUser(const std::string & userID, const std::string & username, const Babel::Rfc::State state, const std::string & ip, const uint16_t port, const std::string &conversation = "", bool notification = false);
        void removeUser(const std::string & userID, bool notification = false);
        void clearContactList();
        void callFromUser(const std::string & userID, const std::string & ipAdress, const uint16_t port);
        void callStarted(const std::string & userID, const std::string & ipAdress, const uint16_t port);
        void callEnded(const std::string & userID);
        void receiveMessageFromUser(const std::string & userID, const std::string & message);

    private:
        // Client To Server
        void login(const QString & username, const QString & password);
        void logout();
        void deleteUser();
        void sendCallRequest();
        void answerCallRequest();
        void endCallRequest();
        void endCallRequest2();
        void askForNewContact(const QString & username);
        void sendMessageTo(const QString & userID, const QString & message);

    private:
        // Slots.
        void focusContact(QString id, QString username);
        void acceptCall();
        void refuseCall();

        void messageReceivedFromServer();
        void handleUnknown(const Babel::Common::PacketsDataBinary& packet);
        void handleOk(const Babel::Common::PacketsDataBinary & packet);
        void handleError(const Babel::Common::PacketsDataBinary& packet);
        void handleDelete(const Babel::Common::PacketsDataBinary& packet);
        void handleUser(const Babel::Common::PacketsDataBinary& packet);
        void handleCall(const Babel::Common::PacketsDataBinary& packet);
        void handleCallAnswer(const Babel::Common::PacketsDataBinary& packet);
        void handleCallEnd(const Babel::Common::PacketsDataBinary& packet);
        void handleContact(const Babel::Common::PacketsDataBinary& packet);
        void handleMsg(const Babel::Common::PacketsDataBinary& packet);
        void handlePing(const Babel::Common::PacketsDataBinary& packet);

    private:
        Contact *& searchForContactWithId(const QString & userId);
        Contact *& searchForContactWithId(const std::string & userId);
        Contact *& searchForContactWithUsername(const QString & username);
        Contact *& searchForContactWithUsername(const std::string & username);
        void settingStylesheets(QFont font);
        void setTargetBarVisible(bool b);
        void setCallWindowVisible(bool b);

        void setInformations(const std::string & username, const QByteArray & password, const std::string &userId, const std::string & ipAdress, const int port);

        void loadConfig();
        void saveConfig();

        void refreshConversation();
        void closeIncomingCallWindow();

        void slotServerConnection(bool result);

    private slots:
        void on_actionLogout_triggered(bool checked);
        void on_actionQuit_triggered(bool checked);
        void on_messageLine_returnPressed();
        void on_sendMsgButton_released();
        void on_addFriendButton_released();
        void on_addFriendLine_returnPressed();
        void on_callButton_released();
        void on_profileButton_released();
        void on_hangUpButton_released();
        void on_muteButton_released();

    public:
        /**
         * @brief contactList
         * QList<Contact *>, contains every contact, their username, password, ip, port, id, ...
         */
        QList<Contact *> contactList;

    private:
        Ui::MainWindow * ui;

        VOIP _voip;
        ExternalIpGetter _externalIpGetter;
        bool _muteState = false;

        QString _ipAdress;

        Babel::Common::ConnectionCredentials _serverCredentials;
        TcpSocket _tcpSocket;

        QString _id = 0;
        QString _username = "";
        Babel::Rfc::State _state;
        QByteArray _password = "";

        LoginForm * _loginForm;
        IncomingCallWindow _incomingCallWindow;

        ClientConfig _settingsJsonFile;
        QString _settingsFilename;

        ProfileForm _profileForm;
    };
}; // !Babel::Client::UserInterface
}; // !Babel::Client
}; // !Babel
