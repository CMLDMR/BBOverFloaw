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
//    auto btcTableItem = new Main::PairTableItem("BTCUSDT");
//    auto ethTableItem = new Main::PairTableItem("ETHUSDT");
//    auto xrpTableItem = new Main::PairTableItem("XRPUSDT");
//    auto ltcTableItem = new Main::PairTableItem("LTCUSDT");
//    auto xmrTableItem = new Main::PairTableItem("XMRUSDT");
//    auto dashTableItem = new Main::PairTableItem("DASHUSDT");

////    QObject::connect(tradeListItem,&TradeListItem::ticker,rangeVolumeItem,&RangeVolume::addTicker);


////    mScene->addItem(orderBook);
////    mScene->addItem(tradeListItem);
////    mScene->addItem(rangeVolumeItem);

//    mScene->addItem(btcTableItem);
//    mScene->addItem(ethTableItem);
//    mScene->addItem(xrpTableItem);
//    mScene->addItem(ltcTableItem);
//    mScene->addItem(xmrTableItem);
//    mScene->addItem(dashTableItem);

////    orderBook->setPos(0,100);
////    tradeListItem->setPos(550,100);
////    rangeVolumeItem->setPos(1000,100);
//    btcTableItem->setPos(0,0);
//    ethTableItem->setPos(0,60);
//    xrpTableItem->setPos(0,120);
//    xmrTableItem->setPos(0,180);
//    ltcTableItem->setPos(0,240);
//    dashTableItem->setPos(0,300);

    addItem("BTCUSDT");
    addItem("ETHUSDT");
    addItem("XRPUSDT");
    addItem("LTCUSDT");
    addItem("XMRUSDT");
    addItem("DASHUSDT");
    addItem("EOSUSDT");
    addItem("ZECUSDT");
    addItem("XLMUSDT");
    addItem("ETCUSDT");
    addItem("NEOUSDT");
    addItem("ONTUSDT");
    addItem("OMGUSDT");
    addItem("QTUMUSDT");
    addItem("ALGOUSDT");
    addItem("BNBUSDT");
    addItem("ADAUSDT");
    addItem("IOTXUSDT");

}

void ViewPort::addItem(const QString &pairName)
{
    auto btcTableItem = new Main::PairTableItem(pairName);
    mScene->addItem(btcTableItem);
    btcTableItem->setPos(0,mScene->items().size()*62);
}

} // namespace Main
