#include "MainWindow.hpp"
#include "./ui_MainWindow.h"

// Qt includes
#include <QApplication>
#include <QFontDatabase>
#include <QCryptographicHash>
#include <QHostAddress>
#include <QHostInfo>
#include <QDateTime>
#include <QNetworkInterface>

// C++ includes
#include <iostream>

using namespace Babel::Client::UserInterface;

MainWindow::MainWindow(Common::ConnectionCredentials serverCredentials, const std::string & myIp, QWidget * parent)
try : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _voip()
    , _externalIpGetter(false)
    , _ipAdress(QStringFromStdString(myIp))
    , _serverCredentials(serverCredentials)
    , _tcpSocket(QStringFromStdString(_serverCredentials.getIP()), _serverCredentials.getPort())
    , _loginForm(new LoginForm(_tcpSocket))
    , _settingsJsonFile(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation), "config.json")
    , _settingsFilename(_settingsJsonFile.fileName)
{
    ui->setupUi(this);
    setWindowTitle("Babel");
    setWindowIcon(QIcon(":/icons/resources/babel.png"));

    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
            _ipAdress = address.toString().toUtf8().data();
        }
    }

    _voip.setIPandPort(_ipAdress.toLocal8Bit().data(), 0);

    // Applying customized font.
    int fontId = QFontDatabase::addApplicationFont(":/fonts/resources/Ubuntu-Medium.ttf");
    QFont font(QFontDatabase::applicationFontFamilies(fontId).at(0));
    font.setPointSize(10);
    QApplication::setFont(font);

    // Setting Stylesheets.
    settingStylesheets(font);

    setTargetBarVisible(false);
    setCallWindowVisible(false);

    loadConfig();

    _loginForm->setWindowTitle("Login Panel");
    _loginForm->setWindowIcon(QIcon(":/icons/resources/babel.png"));
    _loginForm->show();

    _profileForm.setWindowTitle("Profile");
    _profileForm.setWindowIcon(QIcon(":/icons/resources/babel.png"));

    // Connecting signals and slots.
    QObject::connect(_loginForm, &LoginForm::trySignIn, this, &MainWindow::login);
    QObject::connect(&_incomingCallWindow, &IncomingCallWindow::acceptCall, this, &MainWindow::acceptCall);
    QObject::connect(&_incomingCallWindow, &IncomingCallWindow::refuseCall, this, &MainWindow::refuseCall);
    QObject::connect(&_tcpSocket, &TcpSocket::dataReceived, this, &MainWindow::messageReceivedFromServer);

    // Server connection.
    QObject::connect(_loginForm, &LoginForm::connectionToServerResult, this, &MainWindow::slotServerConnection);
    QCoreApplication::processEvents();
    QMetaObject::invokeMethod(&_tcpSocket, "beginConnect", Qt::QueuedConnection);
}
catch (const std::exception & e)
{
    QMessageBox::warning(this, "EXCEPTION", QStringFromStdString(std::string(e.what())));
    throw EXCEPTION(e.what());
}

MainWindow::~MainWindow()
{
    saveConfig();
    delete _loginForm;
    delete ui;
}

/**
 * @brief Slot used in multithread to react to a potential connection with the server.
 * @param bool result
 */
void MainWindow::slotServerConnection(bool result)
{
    // Connecting to server.
    if (result)
    {
        if (!(_username.isEmpty() || _password.isEmpty()))
        {
            _tcpSocket.sendRequest_Login(_username.toLocal8Bit().data(), _password.data());
        }
    }
    else
    {
        QMessageBox::warning(this, "No server connection", "Couldn't reach server.");
        if (_username.isEmpty() || _password.isEmpty())
        {
            QMessageBox::warning(this, "No account preloaded", "You don't have any account previously loaded.\nSo the client will now close, goodbye !");
            qApp->quit();
            return;
        }
        else
        {
            _loginForm->hide();
            show();
        }
    }
}

/**
 * @brief Sets stylesheets.
 * @param QFont font
 */
void MainWindow::settingStylesheets(QFont font)
{
    setStyleSheet(
        "QMainWindow {\n"
            "background-color: rgb(13, 32, 46);"
            "background-image: url(:/icons/resources/background.png);"
            "background-repeat: no-repeat;"
            "background-position: center;"
            "color: white\n"
        "}"
    );
    ui->centralWidget->setStyleSheet("QToolTip { color: black; } QWidget { color: white; }");
    ui->menubar->setStyleSheet(      "QMenuBar { background-color: rgb(13, 32, 46); background-image: none; color: white; } QMenuBar:hover:pressed { color: black; }");
    ui->statusbar->setStyleSheet(    "background-color: rgb(13, 32, 46); background-image: none; color: white;");
    ui->menuBabel->setStyleSheet(    "background-color: rgb(13, 32, 46); background-image: none;");
    ui->messagePanel->setStyleSheet( //"background-image: url(:/icons/resources/background.png);"
                                     //"background-repeat: no-repeat;"
                                     //"background-position: center;\n"
                                     "background-color: rgba(0, 0, 0, 0);");
    ui->leftWidget->setStyleSheet   ("background-color: rgba(24, 38, 48, 155);");
    ui->messageLine->setStyleSheet  ("background-color: rgba(24, 38, 48, 155);");
    ui->addFriendLine->setStyleSheet("background-color: rgba(24, 38, 48, 155);");
    ui->addFriendLine->setFont(font);
    ui->friendListLabel->setStyleSheet("background-color: transparent;");

    _loginForm->setStyleSheet(
        "QWidget {\n"
            "background-color: rgb(13, 32, 46);"
            //"background-image: url(:/icons/resources/background.png);"
            //"background-repeat: no-repeat;"
            //"background-position: center;"
            "color: white\n"
        "};");
    _profileForm.setStyleSheet(
        "QWidget {\n"
            "background-color: rgb(13, 32, 46);"
            //"background-image: url(:/icons/resources/background.png);"
            //"background-repeat: no-repeat;"
            //"background-position: center;"
            "color: white\n"
        "};");
}

/**
 * @brief Sets the target bar visible or not.
 * @param bool b
 */
void MainWindow::setTargetBarVisible(bool b)
{
    ui->callButton->setVisible(b);
    ui->currentFriendLabel->setVisible(b);
    ui->atLabel->setVisible(b);
    ui->messageLine->setEnabled(b);
}

/**
 * @brief Sets the call window visible or not.
 * @param bool b
 */
void MainWindow::setCallWindowVisible(bool b)
{
    static QLayoutItem * spacer1 = nullptr;
    static QLayoutItem * spacer2 = nullptr;

    ui->CallLabel->setVisible(b);
    ui->muteButton->setVisible(b);
    ui->hangUpButton->setVisible(b);
    if (b)
    {
        if (spacer1 != nullptr) ui->CallButtonsLayout->insertItem(0, spacer1);
        if (spacer2 != nullptr) ui->CallButtonsLayout->insertItem(3, spacer1);
    }
    else
    {
        spacer1 = ui->CallButtonsLayout->takeAt(0);
        spacer2 = ui->CallButtonsLayout->takeAt(2);
    }
}

/**
 * @brief Loads the config file and sets the data contained in it to the attributes of MainWindow.
 */
void MainWindow::loadConfig()
{
    if (!_settingsJsonFile.opened) return;

    QJsonObject mainBodyObject = _settingsJsonFile.jsonDocument.object();

    // Loading contact list.
    if (mainBodyObject.find(QtConstants::JsonKeys::contactList) == mainBodyObject.end()) return;
    QJsonArray contactListArray = mainBodyObject.find(QtConstants::JsonKeys::contactList)->toArray();

    for (const auto & contact : contactListArray)
    {
        const auto & contactObject = contact.toObject();
        bool valid = true;

        for (auto & key : QtConstants::JsonKeys::contactInfoList)
        {
            if (contactObject.find(key) == contactObject.end())
            {
                valid = false;
                break;
            }
        }
        if (!valid) continue;

        addUser(contactObject.find(QtConstants::JsonKeys::id)->toString().toLocal8Bit().data(),
                contactObject.find(QtConstants::JsonKeys::username)->toString().toLocal8Bit().data(),
                Babel::Rfc::State::Disconnected,
                contactObject.find(QtConstants::JsonKeys::ip)->toString().toLocal8Bit().data(),
                contactObject.find(QtConstants::JsonKeys::port)->toInt(),
                contactObject.find(QtConstants::JsonKeys::conversation)->toString().toLocal8Bit().data());
    }

    // Loading credentials.
    if (mainBodyObject.find(QtConstants::JsonKeys::credentials) == mainBodyObject.end()) return;
    QJsonObject credentialsObject = mainBodyObject.find(QtConstants::JsonKeys::credentials)->toObject();

    for (auto & key : QtConstants::JsonKeys::credentialsList)
    {
        if (credentialsObject.find(key) == credentialsObject.end())
        {
            return;
        }
    }

    setInformations(
        credentialsObject.find(QtConstants::JsonKeys::username)->toString().toLocal8Bit().data(),
        QByteArray::fromBase64(credentialsObject.find(QtConstants::JsonKeys::password)->toString().toLatin1()),
        credentialsObject.find(QtConstants::JsonKeys::id)->toString().toLocal8Bit().data(),
        credentialsObject.find(QtConstants::JsonKeys::ip)->toString().toLocal8Bit().data(),
        credentialsObject.find(QtConstants::JsonKeys::port)->toInt()
    );
}

/**
 * @brief Saves the config data to the config file (contained in %localappdata%/babel_client/config.json (WIN), and ~/.config/babel_client/config.json (UNIX))
 */
void MainWindow::saveConfig()
{
    QJsonDocument newDocument;
    QJsonObject fileJsonObject;

    // Contact List.
    QJsonArray contactsArray;

    for (auto & contact : contactList)
    {
        QJsonObject contactObject;

        contactObject.insert(QtConstants::JsonKeys::username, contact->username);
        contactObject.insert(QtConstants::JsonKeys::id, contact->id);
        contactObject.insert(QtConstants::JsonKeys::ip, QStringFromStdString(contact->connectionCredentials.getIP()));
        contactObject.insert(QtConstants::JsonKeys::port, contact->connectionCredentials.getPort());
        contactObject.insert(QtConstants::JsonKeys::conversation, contact->conversation);

        contactsArray.append(contactObject);
    }

    // Credentials.
    QJsonObject credentialsObject;

    credentialsObject.insert(QtConstants::JsonKeys::username, _username);
    credentialsObject.insert(QtConstants::JsonKeys::password, QString::fromLatin1(_password.toBase64()));
    credentialsObject.insert(QtConstants::JsonKeys::id, _id);
    credentialsObject.insert(QtConstants::JsonKeys::ip, QStringFromStdString(_serverCredentials.getIP()));
    credentialsObject.insert(QtConstants::JsonKeys::port, _serverCredentials.getPort());

    // Writing to config file.
    fileJsonObject.insert(QtConstants::JsonKeys::contactList, contactsArray);
    fileJsonObject.insert(QtConstants::JsonKeys::credentials, credentialsObject);

    newDocument.setObject(fileJsonObject);

    _settingsJsonFile.jsonDocument = newDocument;
}

//-----------------------------------------------------------------------------------------------------------------
//
//                                  SERVER --> CLIENT
//
//-----------------------------------------------------------------------------------------------------------------

/**
 * @brief Adds a contact to the contact list, the 3 first parameters are mandatory, but conversation and notification are not.
 * conversion represents the messages between the user and the contact.
 * notification just pops up a QMessageBox if set to true.
 * @param const std::string & userID
 * @param const std::string & username
 * @param const Babel::Rfc::State state
 * @param const std::string & conversation
 * @param bool notification
 */
void MainWindow::addUser(const std::string & userID, const std::string & username, const Babel::Rfc::State state, const std::string &conversation, bool notification)
{
    for (auto & contact : contactList)
    {
        if (contact->id.toLocal8Bit().data() == userID)
        {
            if (state != contact->state)
                contact->changeState(state);

            if (!conversation.empty())
                contact->conversation = QStringFromStdString(conversation);

            if (notification)
                QMessageBox::information(this, "User info", "User " + QStringFromStdString(username) + " updated.");
            return;
        }
    }

    contactList.append(new Contact(QStringFromStdString(userID), username, state));
    QObject::connect(contactList.last(), &Contact::contactClicked, this, &MainWindow::focusContact);
    ui->friendsLayout->addWidget(contactList.last());

    if (notification)
        QMessageBox::information(this, "Contact added.", QStringFromStdString(username) + " added to the contact list !");
    if (!conversation.empty())
        contactList.last()->conversation = QStringFromStdString(conversation);
}

/**
 * @brief Just addUser but with ip and port if needed.
 * @param const std::string & userID
 * @param const std::string & username
 * @param const Babel::Rfc::State state
 * @param const std::string & ip
 * @param const uint16_t port
 * @param const std::string & conversation
 * @param bool notification (to show a popup or not of what's happening)
 */
void MainWindow::addUser(const std::string & userID, const std::string &username, const Babel::Rfc::State state, const std::string &ip, const uint16_t port, const std::string & conversation, bool notification)
{
    addUser(userID, username, state, conversation, notification);

    contactList.last()->connectionCredentials.setIP(ip);
    contactList.last()->connectionCredentials.setPort(port);
}

/**
 * @brief Removes the contact having userID as its id from the contact list of the user.
 * @param const std::string & userID
 * @param bool notification
 */
void MainWindow::removeUser(const std::string & userID, bool notification)
{
    for (auto & contact : contactList)
    {
        if (contact->id.toLocal8Bit().data() == userID)
        {
            auto username = contact->username;

            if (ui->currentFriendLabel->text() == username)
                setTargetBarVisible(false);

            ui->friendsLayout->removeWidget(contact);
            contactList.removeOne(contact);
            if (notification) QMessageBox::information(this, "Contact removed.", username + " has been removed from your contact list !");
            return;
        }
    }
}

/**
 * @brief Clears the contact list.
 */
void MainWindow::clearContactList()
{
    for (QLayoutItem * item = ui->friendsLayout->takeAt(0); item != nullptr; item = ui->friendsLayout->takeAt(0))
    {
        delete item->widget();
        delete item;
    }
    contactList.clear();
    QMessageBox::information(this, "Contact List cleared", "The contact list has been cleared ");
}

/**
 * @brief This function has to be called when an incoming call from a contact is being received.
 * @param const std::string & userID
 * @param const std::string & ipAdress
 * @param const uint16_t port
 */
void MainWindow::callFromUser(const std::string & userID, const std::string & ipAdress, const uint16_t port)
{
    QString callerName = "Unknown Person";

    try
    {
        auto & contact = searchForContactWithId(userID);
        contact->connectionCredentials.setIP(ipAdress);
        contact->connectionCredentials.setPort(port);
        callerName = contact->username;
    }
    catch (const std::exception & e)
    {
        QMessageBox::information(this, "Call from User Error", e.what());
        return;
    }

    _incomingCallWindow.setCallerName(callerName);
    _incomingCallWindow.show();
    setEnabled(false);
}

/**
 * @brief This function has to be called when a call with a contact just started.
 * @param const std::string & userID
 * @param const std::string & ipAdress
 * @param const uint16_t port
 */
void MainWindow::callStarted(const std::string & userID, const std::string & ipAdress, const uint16_t port)
{
    _incomingCallWindow.hide();

    try
    {
        auto & contact = searchForContactWithId(userID);
        focusContact(QStringFromStdString(userID), contact->username);
        _voip.setTargetIPandPort(ipAdress, port);
        _voip.startStream();

        contact->conversation += ((contact->conversation.isEmpty()) ? "" : "\n\n");
        contact->conversation += "Call started with " + contact->username + "...";
        if (contact->username == ui->currentFriendLabel->text())
            refreshConversation();
    }
    catch (const std::exception & e)
    {
        QMessageBox::information(this, "Starting Call Error", e.what());
        return;
    }
    setCallWindowVisible(true);
}

/**
 * @brief This function has to be called when a call with a contact has just finished.
 * @param const std::string & userID
 */
void MainWindow::callEnded(const std::string & userID)
{
    auto & contact = searchForContactWithId(userID);

    contact->conversation += ((contact->conversation.isEmpty()) ? "" : "\n\n");
    contact->conversation += "Call ended with " + contact->username + ".";
    if (contact->username == ui->currentFriendLabel->text())
        refreshConversation();

    _voip.stopStream();
    _muteState = false;
    setCallWindowVisible(false);
}

/**
 * @brief This function has to be called when a message from a user has been received.
 * @param const std::string & userID
 * @param const std::string & message
 */
void MainWindow::receiveMessageFromUser(const std::string & userID, const std::string & message)
{
    try
    {
        auto & contact = searchForContactWithId(userID);
        contact->conversation += ((contact->conversation.isEmpty()) ? "" : "\n\n");
        contact->conversation += QDateTime::currentDateTime().toString(QtConstants::dateTimeFormat) + "\n";
        contact->conversation += contact->username + " : " + QStringFromStdString(message);
        if (contact->username == ui->currentFriendLabel->text())
            refreshConversation();
        else {

        }
    }
    catch (const std::exception & e)
    {
        QMessageBox::information(this, "Receive Message Error", e.what());
        return;
    }
}

//-----------------------------------------------------------------------------------------------------------------
//
//                                  CLIENT --> SERVER
//
//-----------------------------------------------------------------------------------------------------------------

/**
 * @brief Gets username & password from the login form, encrypts the password to SHA256 and sends the request.
 * @param const QString & username
 * @param const QString & password
 */
void MainWindow::login(const QString & username, const QString & password)
{
    auto encryptedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Algorithm::Sha256);
    _password = encryptedPassword;

    _tcpSocket.sendRequest_Login(username.toLocal8Bit().data(), encryptedPassword.data());
}

/**
 * @brief Sends a logout request and adapts the UI.
 */
void MainWindow::logout()
{
    _tcpSocket.sendRequest_Logout();

    _id = "";
    _username = "";
    QLayoutItem * item = nullptr;
    while ((item = ui->friendsLayout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
    contactList.clear();
    hide();
    _loginForm->show();
}

/**
 * @brief Deprecated method meant to delete a user from the contact list.
 */
void MainWindow::deleteUser()
{

}

/**
 * @brief Sends a call request.
 */
void MainWindow::sendCallRequest()
{
    try {
        auto & contact = searchForContactWithUsername(ui->currentFriendLabel->text());

        _tcpSocket.sendRequest_Call(contact->id.toLocal8Bit().data(), _ipAdress.toLocal8Bit().data(), _voip.getPort());
    }
    catch (const std::exception & e)
    {
        QMessageBox::information(this, "Call Request Error", e.what());
        return;
    }

}

/**
 * @brief Answers the call request (approving it and starting the call after that)
 */
void MainWindow::answerCallRequest()
{
    try {
        auto & contact = searchForContactWithUsername(_incomingCallWindow.callerName);

        _tcpSocket.sendRequest_CallAnswer(contact->id.toLocal8Bit().data(), _ipAdress.toLocal8Bit().data(), _voip.getPort());
        callStarted(contact->id.toLocal8Bit().data(), contact->connectionCredentials.getIP(), contact->connectionCredentials.getPort());
    }
    catch (const std::exception & e)
    {
        QMessageBox::information(this, "Call Request Error", e.what());
        return;
    }
}

/**
 * @brief Ends the call request or hangs up directly.
 */
void MainWindow::endCallRequest()
{
    try {
        auto & contact = searchForContactWithUsername(_incomingCallWindow.callerName);

        _tcpSocket.sendRequest_CallEnd(contact->id.toLocal8Bit().data());
        callEnded(contact->id.toLocal8Bit().data());
    }
    catch (const std::exception & e)
    {
        QMessageBox::information(this, "Call Request Error", e.what());
        return;
    }
}

/**
 * @brief Ends the call request or hangs up directly.
 */
void MainWindow::endCallRequest2()
{
    try {
        auto& contact = searchForContactWithUsername(ui->currentFriendLabel->text());

        _tcpSocket.sendRequest_CallEnd(contact->id.toLocal8Bit().data());
        callEnded(contact->id.toLocal8Bit().data());
    }
    catch (const std::exception& e)
    {
        QMessageBox::information(this, "Call Request Error", e.what());
        return;
    }
}


/**
 * @brief Sents a contact request for the username sent.
 * @param const QString & username
 */
void MainWindow::askForNewContact(const QString & username)
{
    _tcpSocket.sendRequest_Contact(username.toLocal8Bit().data());
    ui->addFriendLine->setText("");
}

/**
 * @brief Sends a message to the userID.
 * @param const QString & userID
 * @param const QString & message
 */
void MainWindow::sendMessageTo(const QString & userID, const QString & message)
{
    if (ui->messageLine->text().isEmpty()) return;

    try
    {
        auto & contact = searchForContactWithId(userID);
        contact->conversation += ((contact->conversation.isEmpty()) ? "" : "\n\n");
        contact->conversation += QDateTime::currentDateTime().toString(QtConstants::dateTimeFormat) + "\n";
        contact->conversation += _username + " : " + message;
        _tcpSocket.sendRequest_Msg(userID.toLocal8Bit().data(), message.toLocal8Bit().data());
        refreshConversation();
        ui->messageLine->setText("");
    }
    catch (const std::exception & e)
    {
        QMessageBox::information(this, "Receive Message Error", e.what());
        return;
    }
}

//-----------------------------------------------------------------------------------------------------------------
//
//                                  SLOTS
//
//-----------------------------------------------------------------------------------------------------------------

/**
 * @brief Reacts to a message received.
 */
void MainWindow::messageReceivedFromServer()
{
    static QMap<Babel::Rfc::Code, void (MainWindow::*)(const Babel::Common::PacketsDataBinary &)> reactions =
    {
        {Babel::Rfc::Code::UNKNOWN,         &MainWindow::handleUnknown},
        {Babel::Rfc::Code::SC_OK,           &MainWindow::handleOk},
        {Babel::Rfc::Code::SC_ERROR,        &MainWindow::handleError},
        {Babel::Rfc::Code::SC_DELETE,       &MainWindow::handleDelete},
        {Babel::Rfc::Code::SC_USER,         &MainWindow::handleUser},
        {Babel::Rfc::Code::SC_CALL,         &MainWindow::handleCall},
        {Babel::Rfc::Code::SC_CALL_ANSWER,  &MainWindow::handleCallAnswer},
        {Babel::Rfc::Code::SC_CALL_END,     &MainWindow::handleCallEnd},
        {Babel::Rfc::Code::SC_CONTACT,      &MainWindow::handleContact},
        {Babel::Rfc::Code::SC_MSG,          &MainWindow::handleMsg},
        {Babel::Rfc::Code::SC_PING,         &MainWindow::handlePing}
    };

    while (!_tcpSocket.requests.empty())
    {
        const auto & request = _tcpSocket.requests.first();
        if (reactions.contains(request.getCommandType()))
        {
            try
            {
                const auto & reaction = reactions.value(request.getCommandType());
                (this->*reaction)(request);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
                std::cerr << "Command " << request.getCommandType() << " crashed " << "with parameters : ";
                for (auto & str : request.getArguments())
                {
                    std::cerr << str << (str == *request.getArguments().end()) ? "" : ", ";
                }
                std::cerr << std::endl;
            }
        }
        _tcpSocket.requests.removeFirst();
    }
}

void MainWindow::handleUnknown(const Babel::Common::PacketsDataBinary &)
{
    qDebug() << "/!\\ Server sent Unknown command.";
    QMessageBox::warning(this, "Unknown command sent to server", "Server responded UNKNOWN to client request");
}

void MainWindow::handleOk(const Babel::Common::PacketsDataBinary & packet)
{
    qDebug() << "Server sent OK for command(" << QStringFromStdString(packet.getArguments().at(0)) << ").";
}

void MainWindow::handleError(const Babel::Common::PacketsDataBinary &packet)
{
    qDebug() << "Server sent Error for command(" << QStringFromStdString(packet.getArguments().at(0)) << "with message" << QStringFromStdString(packet.getArguments().at(1)) << ").";
    QMessageBox::warning(this, "Error", QStringFromStdString(packet.getArguments().at(0)) + " : " + QStringFromStdString(packet.getArguments().at(1)));
}

void MainWindow::handleDelete(const Babel::Common::PacketsDataBinary &packet)
{
    std::string userID = packet.getArguments().at(0);
    qDebug() << "Removing user n." << QStringFromStdString(userID) << ".";
    removeUser(userID);
}

void MainWindow::handleUser(const Babel::Common::PacketsDataBinary &packet)
{
    std::string userID = packet.getArguments().at(0);
    std::string username = packet.getArguments().at(1);
    Babel::Rfc::State state = Babel::Rfc::State(std::stoi(packet.getArguments().at(2)));

    _id = QStringFromStdString(userID);
    _username = QStringFromStdString(username);
    _state = state;
    show();
    _loginForm->hide();
    qDebug() << "Adding/Refreshing user n." << QStringFromStdString(userID) << " : '" << QStringFromStdString(username) << "', " << state << ".";
}

void MainWindow::handleCall(const Babel::Common::PacketsDataBinary &packet)
{
    std::string userID = packet.getArguments().at(0);
    std::string ip = packet.getArguments().at(1);
    uint16_t port = std::stoi(packet.getArguments().at(2));

    callFromUser(userID, ip, port);
    qDebug() << "Call request from user n." << QStringFromStdString(userID) << ": " << QStringFromStdString(ip) << ":" << port << ".";
}

void MainWindow::handleCallAnswer(const Babel::Common::PacketsDataBinary &packet)
{
    std::string userID = packet.getArguments().at(0);
    std::string ip = packet.getArguments().at(1);
    uint16_t port = std::stoi(packet.getArguments().at(2));

    callStarted(userID, ip, port);
    qDebug() << "Call answer request from user n." << QStringFromStdString(userID) << ": " << QStringFromStdString(ip) << ":" << port << ".";
}

void MainWindow::handleCallEnd(const Babel::Common::PacketsDataBinary &packet)
{
    std::string userID = packet.getArguments().at(0);

    callEnded(userID);
    qDebug() << "Call end request from user n." << QStringFromStdString(userID) << ".";
}

void MainWindow::handleContact(const Babel::Common::PacketsDataBinary &packet)
{
    std::string userID = packet.getArguments().at(0);
    std::string username = packet.getArguments().at(1);
    Babel::Rfc::State state = Babel::Rfc::State(std::stoi(packet.getArguments().at(2)));

    addUser(userID, username, state);
    qDebug() << "Adding/Refreshing user n." << QStringFromStdString(userID) << " : '" << QStringFromStdString(username) << "', " << state << ".";
}

void MainWindow::handleMsg(const Babel::Common::PacketsDataBinary &packet)
{
    std::string userID = packet.getArguments().at(0);
    std::string message = packet.getArguments().at(1);

    receiveMessageFromUser(userID, message);
    qDebug() << "Received message '" << QStringFromStdString(message) << "' from user n." << QStringFromStdString(userID) << "'.";
}

void MainWindow::handlePing(const Babel::Common::PacketsDataBinary &)
{
    _tcpSocket.sendRequest_Ok(Babel::Rfc::Code::SC_PING);
    qDebug() << "Responding to ping from server.";
}

void MainWindow::focusContact(QString id, QString username)
{
    for (auto & contact : contactList)
    {
        if (id == contact->id && username == contact->username)
        {
            if (contact->state == Babel::Rfc::State::Disconnected)
            {
                QMessageBox::warning(this, "Contact disonnected", contact->username + " is disconnected.");
                return;
            }
            ui->messagePanel->setText(contact->conversation);
            goto noError;
        }
    }
    return;

    noError:

    ui->currentFriendLabel->setText(username);
    setTargetBarVisible(true);
}

void MainWindow::acceptCall()
{
    try
    {
        answerCallRequest();
        closeIncomingCallWindow();
    }
    catch (const std::exception & e)
    {
        QMessageBox::information(this, "Accept Call Error", e.what());
        return;
    }
}

void MainWindow::refuseCall()
{
    try
    {
        endCallRequest();
        closeIncomingCallWindow();
    }
    catch (const std::exception & e)
    {
        QMessageBox::information(this, "Refuse Call Error", e.what());
        return;
    }
}

void MainWindow::on_actionLogout_triggered(bool)
{
    logout();
}

void MainWindow::on_actionQuit_triggered(bool)
{
    qApp->quit();
}

void MainWindow::on_messageLine_returnPressed()
{
    try {
        if (!ui->messageLine->text().isEmpty())
            sendMessageTo(searchForContactWithUsername(ui->currentFriendLabel->text())->id, ui->messageLine->text());
    } catch (const std::exception & e) {
        QMessageBox::information(this, "Send Message Error", e.what());
        return;
    }
}

void MainWindow::on_sendMsgButton_released()
{
    on_messageLine_returnPressed();
}

void MainWindow::on_addFriendButton_released()
{
    if (!ui->addFriendLine->text().isEmpty())
        askForNewContact(ui->addFriendLine->text());
}

void MainWindow::on_addFriendLine_returnPressed()
{
    on_addFriendButton_released();
}

void MainWindow::on_callButton_released()
{
    sendCallRequest();
}

void MainWindow::on_profileButton_released()
{
    _profileForm.show();
    _profileForm.setProfile(_id, _username);
}

void MainWindow::on_hangUpButton_released()
{
    endCallRequest2();
}

void MainWindow::on_muteButton_released()
{
    static const QMap<bool, QString> iconStates = {
        {true,  ":/icons/resources/mutedIcon.png"},
        {false, ":/icons/resources/unmutedIcon.png"}
    };

    _muteState = !_muteState;
    _voip.setMicrophoneState(!_muteState);
    ui->muteButton->setIcon(QIcon(iconStates[_muteState]));
}

//-----------------------------------------------------------------------------------------------------------------
//
//                                  UTILITY
//
//-----------------------------------------------------------------------------------------------------------------

Contact *& MainWindow::searchForContactWithId(const QString & userId)
{
    for (auto & contact : contactList)
    {
        if (contact->id == userId)
            return contact;
    }
    throw EXCEPTION("Contact not found.");
}

Contact *& MainWindow::searchForContactWithId(const std::string & userId)
{
    return searchForContactWithId(QStringFromStdString(userId));
}

Contact *& MainWindow::searchForContactWithUsername(const QString &username)
{
    for (auto & contact : contactList)
    {
        if (contact->username == username)
            return contact;
    }
    throw EXCEPTION("Contact not found.");
}

Contact *& MainWindow::searchForContactWithUsername(const std::string & username)
{
    return searchForContactWithUsername(QStringFromStdString(username));
}

void MainWindow::refreshConversation()
{
    auto & contact = searchForContactWithUsername(ui->currentFriendLabel->text());
    ui->messagePanel->setText(contact->conversation);
    auto newCursor = ui->messagePanel->textCursor();
    newCursor.setPosition(ui->messagePanel->toPlainText().size());
    ui->messagePanel->setTextCursor(newCursor);
}

void MainWindow::closeIncomingCallWindow()
{
    _incomingCallWindow.hide();
    setEnabled(true);
}

void MainWindow::setInformations(const std::string &username, const QByteArray &password, const std::string & userId, const std::string &ipAdress, const int port)
{
    _username = QStringFromStdString(username);
    _password = password;
    _id = QStringFromStdString(userId);
    _serverCredentials.setIP(ipAdress);
    _serverCredentials.setPort(port);
}
