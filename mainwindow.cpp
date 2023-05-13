#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "info/exchangeinfo.h"
#include "main/viewport.h"

#include "info/exchangemodel.h"

#include "session/sessionmanager.h"


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

    QObject::connect(ui->actionSave_As,&QAction::triggered,[=]( const bool &val){
        Session::SessionManager::instance()->saveDialog();
    });

    QObject::connect(ui->actionLoad,&QAction::triggered,[=]( const bool &val){
        if( Session::SessionManager::instance()->openSessionDialog() ){
            for( int i = 0 ; i < Session::SessionManager::instance()->pairListSize() ; i++ ){
                mViewPort->setPairItem(Session::SessionManager::instance()->pairName(i));
            }
        }

    });



}

MainWindow::~MainWindow()
{
    delete ui;
}

