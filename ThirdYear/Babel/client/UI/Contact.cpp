#include "Contact.hpp"
#include "./ui_Contact.h"

using namespace Babel::Client::UserInterface;

Contact::Contact(const QString & userID, const std::string & un, const Babel::Rfc::State userState, QWidget * parent)
    : QWidget(parent)
    , id(userID)
    , username(QStringFromStdString(un))
    , state(userState)
    , ui(new Ui::Contact)
{
    ui->setupUi(this);

    changeState(state);
    ui->friendNameButton->setText(username);
}

Contact::~Contact()
{
    delete ui;
}

/**
 * @brief Changes its state.
 * @param const Babel::Rfc::State newState
 */
void Contact::changeState(const Babel::Rfc::State newState)
{
    state = newState;

    ui->friendStateIcon->setPixmap(QtConstants::iconPerContactStates[state]);
    ui->friendStateIcon->setToolTip(QtConstants::stringPerContactStates[state]);
}

void Contact::on_friendNameButton_released()
{
    emit contactClicked(id, username);
}
