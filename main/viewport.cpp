#include "viewport.h"

#include "viewscene.h"

#include "orderbookitem.h"
#include "tradelistitem.h"
#include "rangevolume.h"

namespace Main {

ViewPort::ViewPort()
{

    const QString pair("btcusdt");

    mScene = new ViewScene();
    setScene(mScene);
    auto orderBook = new Main::OrderBookItem(pair);
    auto tradeListItem = new Main::TradeListItem(pair);
    auto rangeVolumeItem = new Main::RangeVolume();

    QObject::connect(tradeListItem,&TradeListItem::ticker,rangeVolumeItem,&RangeVolume::addTicker);


    mScene->addItem(orderBook);
    mScene->addItem(tradeListItem);
    mScene->addItem(rangeVolumeItem);

    tradeListItem->setPos(550,0);
    rangeVolumeItem->setPos(1000,0);


}

} // namespace Main
