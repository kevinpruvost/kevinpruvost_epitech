#pragma once

#include <QWidget>

namespace Ui {
class ProfileForm;
}


namespace Babel
{
namespace Client
{
namespace UserInterface
{
    /**
     * @brief Contains a profile form, showing the userId and the username of the client.
     */
    class ProfileForm : public QWidget
    {
        Q_OBJECT

    public:
        explicit ProfileForm(QWidget *parent = nullptr);
        ~ProfileForm();

        void setProfile(const QString & userId, const QString & username);

    private:
        Ui::ProfileForm *ui;
    };
}; // !Babel::Client::UserInterface
}; // !Babel::Client
}; // !Babel
