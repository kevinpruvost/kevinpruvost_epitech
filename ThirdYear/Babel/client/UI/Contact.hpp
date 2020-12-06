#pragma once

// Project includes
#include "QtConstants.hpp"

// Qt includes
#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Contact; }
QT_END_NAMESPACE

namespace Babel
{
namespace Client
{
namespace UserInterface
{
    /**
     * @brief Contains every informations of a contact like username, userId, credentials, and the conversation between the client and him.
     */
    class Contact : public QWidget
    {
        Q_OBJECT

    public:
        explicit Contact(const QString & userID, const std::string & username, const Babel::Rfc::State state, QWidget * parent = nullptr);
        ~Contact();

        void changeState(const Babel::Rfc::State newState);

    signals:
        void contactClicked(QString id, QString username);

    private slots:
        void on_friendNameButton_released();

    public:
        Babel::Common::ConnectionCredentials connectionCredentials;
        const QString id;
        QString username;
        Babel::Rfc::State state;

        QString conversation;

    private:
        Ui::Contact * ui;
    };
}; // !Babel::Client::Ui
}; // !Babel::Client
}; // !Babel
