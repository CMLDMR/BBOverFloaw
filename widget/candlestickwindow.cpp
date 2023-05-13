#include "candlestickwindow.h"
#include "ui_candlestickwindow.h"
#include "candlestick.h"
#include "main/series.h"
#include "main/candleitem.h"


namespace Screen {

CandleStickWindow::CandleStickWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CandleStickWindow)
{
    ui->setupUi(this);


    mGraphicView = new QGraphicsView();
    ui->mMainLayout->addWidget(mGraphicView);


    mScene = new QGraphicsScene();
    mGraphicView->setScene(mScene);


    this->setWindowFlags(Qt::WindowStaysOnTopHint);


//    mScene->addItem(new CandleStickItem());

    mGraphicView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);


}

CandleStickWindow::~CandleStickWindow()
{
    delete ui;
}

void CandleStickWindow::setSeries(QVector<Main::Series *> *newSeries)
{
    mSeries = newSeries;

    if( mSeries ){
        //        qDebug() << "Bar size: " << item->getSeries().size();

        if( !mScene->items().size() ){
            int i = 0;
            for( auto &item : *mSeries ){
                auto seri = new CandleStickItem();
                seri->setSeries(item);
                seri->setPos(0,i*(seri->boundingRect().height()+10));
                this->mScene->addItem(seri);
                i++;
            }
        }



    }

//    for( const auto &item : *mSeries ){



////        for( const auto &bar : item->getSeries() ){
////            qDebug() << bar;
////        }
//    }
}

void CandleStickWindow::timerEvent(QTimerEvent *event)
{

}

} // namespace Screen
