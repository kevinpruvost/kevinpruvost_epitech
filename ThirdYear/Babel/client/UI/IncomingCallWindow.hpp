#pragma once

#include <QWidget>

namespace Ui {
class IncomingCallWindow;
}

namespace Babel
{
namespace Client
{
namespace UserInterface
{
    /**
     * @brief Meant to indicate who is calling and lets the user chose between hanging up or responding.
     */
    class IncomingCallWindow : public QWidget
    {
        Q_OBJECT

    public:
        explicit IncomingCallWindow(QWidget *parent = nullptr);
        ~IncomingCallWindow();

        void setCallerName(const QString & name);

    signals:
        void acceptCall();
        void refuseCall();

    private slots:
        void on_acceptButton_released();
        void on_refuseButton_released();

    public:
        QString callerName;

    private:
        Ui::IncomingCallWindow *ui;
    };
}; // !Babel::Client::UserInterface
}; // !Babel::Client
}; // !Babel
