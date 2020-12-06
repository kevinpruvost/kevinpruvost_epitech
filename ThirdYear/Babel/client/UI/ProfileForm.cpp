#include "ProfileForm.hpp"
#include "ui_ProfileForm.h"

using namespace Babel::Client::UserInterface;

ProfileForm::ProfileForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileForm)
{
    ui->setupUi(this);
}

ProfileForm::~ProfileForm()
{
    delete ui;
}

/**
 * @brief Sets profile informations.
 * @param const QString & userId
 * @param const QString & username
 */
void ProfileForm::setProfile(const QString &userId, const QString &username)
{
    ui->usernameLabel->setText("Username : " + username);
    ui->userIdLabel->setText("User ID : " + userId);
}
