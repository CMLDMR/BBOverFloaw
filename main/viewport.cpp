#include "viewport.h"

#include "viewscene.h"

#include "orderbookitem.h"
#include "tradelistitem.h"

namespace Main {

ViewPort::ViewPort()
{

    mScene = new ViewScene();
    setScene(mScene);
    auto orderBook = new Main::OrderBookItem();
    auto tradeListItem = new Main::TradeListItem();


    mScene->addItem(orderBook);
    mScene->addItem(tradeListItem);
    tradeListItem->setPos(550,0);


}

} // namespace Main
