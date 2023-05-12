#include "viewport.h"

#include "viewscene.h"

#include "orderbookitem.h"
#include "tradelistitem.h"
#include "rangevolume.h"
#include "pairtableitem.h"

namespace Main {

ViewPort::ViewPort()
{

    const QString pair("btcusdt");

    mScene = new ViewScene();
    setScene(mScene);
//    auto orderBook = new Main::OrderBookItem(pair);
//    auto tradeListItem = new Main::TradeListItem(pair);
//    auto rangeVolumeItem = new Main::RangeVolume();

////    QObject::connect(tradeListItem,&TradeListItem::ticker,rangeVolumeItem,&RangeVolume::addTicker);


////    mScene->addItem(orderBook);
////    mScene->addItem(tradeListItem);
////    mScene->addItem(rangeVolumeItem);



////    orderBook->setPos(0,100);
////    tradeListItem->setPos(550,100);
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
    mAddedInternal++;
    if( mAddedInternal >= 15 ){
        rowCount++;
        mAddedInternal = 0;
    }
}

} // namespace Main
