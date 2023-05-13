#include "viewport.h"

#include "viewscene.h"

#include "orderbookitem.h"
#include "tradelistitem.h"
#include "rangevolume.h"
#include "pairtableitem.h"
#include "widget/candlestickwindow.h"

#include "session/sessionmanager.h"

#include <QScreen>
#include <QMouseEvent>

namespace Main {

ViewPort::ViewPort()
{
    mScene = new ViewScene();
    setScene(mScene);
    //    auto orderBook = new Main::OrderBookItem(pair);
//        auto tradeListItem = new Main::TradeListItem(pair);
    //    auto rangeVolumeItem = new Main::RangeVolume();

    ////    QObject::connect(tradeListItem,&TradeListItem::ticker,rangeVolumeItem,&RangeVolume::addTicker);


    ////    mScene->addItem(orderBook);
//        mScene->addItem(tradeListItem);
    ////    mScene->addItem(rangeVolumeItem);



    ////    orderBook->setPos(0,100);
//        tradeListItem->setPos(550,100);
    ////    rangeVolumeItem->setPos(1000,100);


    //    addItem("TOMOUSDT");


}

void ViewPort::addItem(const QString &pairName)
{

    if( Session::SessionManager::instance()->pairContains(pairName) ){
        return;
    }

    Session::SessionManager::instance()->addPair(pairName);

    this->setPairItem(pairName);
}

void ViewPort::setPairItem(const QString &pairName)
{
    auto btcTableItem = new Main::PairTableItem(pairName);
    mScene->addItem(btcTableItem);
    btcTableItem->setPos(rowCount*(btcTableItem->boundingRect().width()+5),mAddedInternal*(btcTableItem->boundingRect().height()+5));

    //TODO:  remove Item Crashed
    QObject::connect(btcTableItem,&Main::AbtractItem::deleteClicked,[=](){
        btcTableItem->setWillRemove(true);

        if( !Session::SessionManager::instance()->removePair(btcTableItem->pair()) ){
            qDebug() << "did not remove or pair exist!";
        }
        mScene->removeItem(btcTableItem);

    });


    QObject::connect(btcTableItem,&Main::AbtractItem::openCandled,[=](const QPoint &point){

        if( mWindowList.size() ){
            for( auto &item : mWindowList ){
                delete item;
            }
            mWindowList.clear();
        }

        Screen::CandleStickWindow* mWidget = new Screen::CandleStickWindow();

        mWidget->setGeometry(this->screen()->geometry().width()/2-mWidget->width()/2,
                             this->screen()->geometry().height()/2-mWidget->height()/2,
                             mWidget->width(),
                             mWidget->height());

        mWidget->setWindowTitle(btcTableItem->pair() + " CandleStick");

        mWidget->setSeries(btcTableItem->seriesList());

        mWidget->setFocus();
        mWidget->show();

        mWindowList.push_back(mWidget);

    });
    mAddedInternal++;
    if( mAddedInternal >= 15 ){
        rowCount++;
        mAddedInternal = 0;
    }
}



} // namespace Main


void Main::ViewPort::mousePressEvent(QMouseEvent *event)
{


    for( const auto &item : mScene->items() ){

        qDebug() << item->boundingRect() << item->pos() << item->scenePos() << event->pos();

    }



    QGraphicsView::mousePressEvent(event);
}
