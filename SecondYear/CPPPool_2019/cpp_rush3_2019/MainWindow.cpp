/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/1
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QLayout>
#include <QHBoxLayout>
#include <QProgressBar>

MainWindow::MainWindow(Htop & core, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    , _core { core }
    , _delay { 1500 }
    , _timer (new QTimer(this))
{
    ui->setupUi(this);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);

    setWindowTitle("MyGKrellm gras-thick");

    createTabs();

    QObject::connect(_timer, &QTimer::timeout,
                     this,   &MainWindow::refresh);
    _timer->start(_delay);
    show();
}

MainWindow::~MainWindow()
{
    _timer->deleteLater();
    delete ui;

    for (const auto tab : _tabs)
        if (tab)
            tab->deleteLater();

    if (_cpu)
        _cpu->deleteLater();
    if (_network)
        _network->deleteLater();
    if (_kernel)
        _kernel->deleteLater();
    if (_process)
        _process->deleteLater();
    if (_ram)
        _ram->deleteLater();
    if (_swap)
        _swap->deleteLater();
    if (_timeModule)
        _timeModule->deleteLater();
    if (_user)
        _user->deleteLater();
}

void MainWindow::refresh()
{
    if (_cpu)
        _cpu->refresh();
    if (_timeModule)
        _timeModule->refresh();
    if (_user)
        _user->refresh();
    if (_swap)
        _swap->refresh();
    if (_ram)
        _ram->refresh();
    if (_network)
        _network->refresh();
    if (_process && ui->tabWidget->currentIndex() == ui->tabWidget->count() - 1)
        _process->refresh();
}



void MainWindow::createTabs()
{
    QObject::connect(ui->tabWidget, &QTabWidget::tabCloseRequested, ui->tabWidget, [=](int id) {
        ui->tabWidget->removeTab(id);
        if (ui->tabWidget->count() <= 0)
            close();
    });
    ui->tabWidget->setTabsClosable(true);
    if (_core.getBool(Htop::enum_module::CPU))
    {
        _cpu = new QtCPUModule(_core.getCpu());
        _tabs.append(_cpu);
        ui->tabWidget->addTab(_cpu, "CPU");
    }

    if (_core.getBool(Htop::enum_module::MEMORY))
    {
        _ram = new QtRamModule(_core.getRam());
        _tabs.append(_ram);
        ui->tabWidget->addTab(_ram, "MEMORY");
    }

    if (_core.getBool(Htop::enum_module::NETWORK))
    {
        _network = new QtNetworkModule(_core.getNetwork());
        _tabs.append(_network);
        ui->tabWidget->addTab(_network, "NETWORK");
    }

    if (_core.getBool(Htop::enum_module::SWAP))
    {
        _swap = new QtSwapModule(_core.getSwap());
        _tabs.append(_swap);
        ui->tabWidget->addTab(_swap, "SWAP");
    }

    if (_core.getBool(Htop::enum_module::USER))
    {
        _user = new QtUserModule(_core.getUser());
        _tabs.append(_user);
        ui->tabWidget->addTab(_user, "USER");
    }

    if (_core.getBool(Htop::enum_module::TIME))
    {
        _timeModule = new QtTimeModule(_core.getTime());
        _tabs.append(_timeModule);
        ui->tabWidget->addTab(_timeModule, "TIME");
    }

    if (_core.getBool(Htop::enum_module::KERNEL))
    {
        _kernel = new QtKernelModule(_core.getKernel());
        _tabs.append(_kernel);
        ui->tabWidget->addTab(_kernel, "KERNEL");
    }

    if (_core.getBool(Htop::enum_module::PROCESS))
    {
        _process = new QtProcessModule(_core.getProcess());
        _tabs.append(_process);
        ui->tabWidget->addTab(_process, "PROCESSES");
    }
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_D)
    {
        if (ui->tabWidget->currentIndex() + 1 == ui->tabWidget->count())
            ui->tabWidget->setCurrentIndex(0);
        else
            ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex() + 1);
    }

    if (ev->key() == Qt::Key_Q)
    {
        if (ui->tabWidget->currentIndex() == 0)
            ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
        else
            ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex() - 1);
    }
}
