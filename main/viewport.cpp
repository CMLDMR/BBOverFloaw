#include "viewport.h"

#include "viewscene.h"

#include "orderbookitem.h"

namespace Main {

ViewPort::ViewPort()
{

    mScene = new ViewScene();
    setScene(mScene);
    auto orderBook = new Main::OrderBookItem();
    mScene->addItem(orderBook);
}

} // namespace Main
