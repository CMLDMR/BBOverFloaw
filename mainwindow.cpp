#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "info/exchangeinfo.h"
#include "main/viewport.h"

#include "info/exchangemodel.h"

#include "session/sessionmanager.h"
#include <QUrl>
#include <QThread>
#include <iostream>

#include "binance/restapi/restapi.h"

#include "global/alarmwidget.h"
#include "binance/kline.h"
#include "series/seri.h"
#include "Logger.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BBOverFloaw");

    LOG_DEBUG("{}" , "." );
    Binance::Public::RestAPI::RestAPI::instance();


    ///////////////////////////
    mExchangeInfo = new ExchangeInfo::ExchangeInfo();
    ui->exchangeVLayout->addWidget(mExchangeInfo);

    mViewPort = new Main::ViewPort();

    ui->verticalGraphLayout->addWidget(mViewPort);

    QObject::connect(mExchangeInfo,&ExchangeInfo::ExchangeInfo::selectedPair,[=, this](const QString mPairName){
                mViewPort->addItem(mPairName);
    });

    QObject::connect(ui->actionSound_Test,&QAction::triggered,[=, this](){
        qDebug() << ui->actionSound_Test->text();
    });

    QObject::connect(ui->actionSave_As,&QAction::triggered,[=]( const bool &val){
        Session::SessionManager::instance()->saveDialog();
    });

    QObject::connect(ui->actionLoad,&QAction::triggered,[=, this]( const bool &val){
        if( Session::SessionManager::instance()->openSessionDialog() ){

            QTimer* mTimer = new QTimer();
            int count = 0;
            QObject::connect(mTimer,&QTimer::timeout,[=, this]()mutable{
                if( count < Session::SessionManager::instance()->pairListSize() ){
                    mViewPort->addItem(Session::SessionManager::instance()->pairName(count));
                    mExchangeInfo->append(Session::SessionManager::instance()->pairName(count++));
                    if( count >= Session::SessionManager::instance()->pairListSize() ){
                        mTimer->stop();
                    }
                }else{
                    mTimer->stop();
                    mTimer->deleteLater();
                }

            });

            mTimer->start(2000);

//            for( int i = 0 ; i < Session::SessionManager::instance()->pairListSize() ; i++ ){
//                QThread::currentThread()->wait(500);
//                mViewPort->setPairItem(Session::SessionManager::instance()->pairName(i));
//                mExchangeInfo->append(Session::SessionManager::instance()->pairName(i));
//            }
            mExchangeInfo->update();
        }

    });
    std::cout << __FILE__ << " " <<__LINE__ << "\n";

    QObject::connect(ui->actionSound_Test,&QAction::triggered,[=](){

        Global::Alarm::AlarmWidget::instance()->popUpMessage("Test");

    });



//    Binance::Public::Future::RestAPI::instance()->exchangeInfo();

}

MainWindow::~MainWindow()
{
    delete ui;
}

