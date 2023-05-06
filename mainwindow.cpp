#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "info/exchangeinfo.h"
#include "main/viewport.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mExchangeInfo = new ExchangeInfo::ExchangeInfo();

    ui->exchangeVLayout->addWidget(mExchangeInfo);

    mViewPort = new Main::ViewPort();

    ui->verticalGraphLayout->addWidget(mViewPort);

}

MainWindow::~MainWindow()
{
    delete ui;
}

