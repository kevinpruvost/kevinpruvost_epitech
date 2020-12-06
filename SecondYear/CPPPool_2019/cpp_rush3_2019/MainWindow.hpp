/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/1
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QList>

#include "qtmodules/QtCPUModule.hpp"
#include "qtmodules/QtKernelModule.hpp"
#include "qtmodules/QtNetworkModule.hpp"
#include "qtmodules/QtProcessModule.hpp"
#include "qtmodules/QtRamModule.hpp"
#include "qtmodules/QtSwapModule.hpp"
#include "qtmodules/QtTimeModule.hpp"
#include "qtmodules/QtUserModule.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(Htop & core, QWidget * parent = nullptr);
    ~MainWindow();

    void createTabs();
    void modifyTimer(const int delay) { _delay = delay; _timer->setInterval(delay); }

    void refresh();

    void keyPressEvent(QKeyEvent *ev) override;

private:
    Ui::MainWindow *ui;
    Htop & _core;

    int _delay;
    QTimer * _timer = nullptr;
    QList<QWidget *> _tabs;
    QtCPUModule * _cpu = nullptr;
    QtKernelModule * _kernel = nullptr;
    QtNetworkModule * _network = nullptr;
    QtProcessModule * _process = nullptr;
    QtRamModule * _ram       = nullptr;
    QtSwapModule * _swap      = nullptr;
    QtTimeModule * _timeModule = nullptr;
    QtUserModule * _user = nullptr;
};

#endif // MAINWINDOW_HPP
