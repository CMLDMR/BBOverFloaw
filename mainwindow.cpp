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


//        for( int i = 0 ; i < mExchangeInfo->model()->rowCount() ; i++ ){
//            if( i >= 50 ) break;
//            mViewPort->addItem(mExchangeInfo->model()->index(i,0).data().toString());
//        }

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

