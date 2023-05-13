#include "viewport.h"

#include "viewscene.h"

#include "orderbookitem.h"
#include "tradelistitem.h"
#include "rangevolume.h"
#include "pairtableitem.h"
#include "widget/candlestickwindow.h"


namespace Main {

ViewPort::ViewPort()
{

    const QString pair("btcusdt");

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

    if( pairList.contains(pairName) ){
        return;
    }

    pairList.push_back(pairName);

    auto btcTableItem = new Main::PairTableItem(pairName);
    mScene->addItem(btcTableItem);
    btcTableItem->setPos(rowCount*(btcTableItem->boundingRect().width()+5),mAddedInternal*(btcTableItem->boundingRect().height()+5));

    //TODO:  remove Item Crashed
    QObject::connect(btcTableItem,&Main::AbtractItem::deleteClicked,[=](){

        qDebug() << "Before: "<<mScene->items().size();

        Main::PairTableItem *item = qgraphicsitem_cast<Main::PairTableItem *>(btcTableItem);

//        int index = pairList.indexOf(item->pair());





        mScene->removeItem(item);
        this->update();
        qDebug() << mScene->items().size();

    });


    QObject::connect(btcTableItem,&Main::AbtractItem::openCandled,[=](const QPoint &point){
        Screen::CandleStickWindow* mWidget = new Screen::CandleStickWindow();

        mWidget->setGeometry(point.x()-mWidget->width()/2,
                             point.y()-mWidget->height()/2,
                             mWidget->width(),
                             mWidget->height());

        mWidget->setWindowTitle(btcTableItem->pair() + " CandleStick");

        mWidget->setSeries(btcTableItem->seriesList());

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
