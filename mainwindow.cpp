#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "info/exchangeinfo.h"
#include "main/viewport.h"

#include "info/exchangemodel.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mExchangeInfo = new ExchangeInfo::ExchangeInfo();

    ui->exchangeVLayout->addWidget(mExchangeInfo);

    mViewPort = new Main::ViewPort();
    mViewPort->setDragMode(QGraphicsView::ScrollHandDrag);

    ui->verticalGraphLayout->addWidget(mViewPort);

    QObject::connect(mExchangeInfo,&ExchangeInfo::ExchangeInfo::selectedPair,[=](const QString mPairName){
                mViewPort->addItem(mPairName);
    });

    QObject::connect(ui->actionSound_Test,&QAction::triggered,[=](){
        qDebug() << ui->actionSound_Test->text();
    });



}

MainWindow::~MainWindow()
{
    delete ui;
}

