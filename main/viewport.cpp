#include "viewport.h"

#include "viewscene.h"

#include "orderbookitem.h"
#include "tradelistitem.h"
#include "rangevolume.h"
#include "widget/candlestickwindow.h"

#include "session/sessionmanager.h"

#include <QScreen>
#include <QMouseEvent>
#include <QDesktopServices>

#include <algorithm>


#include "graphicsItem/pairitem.h"
#include "chart/chartwidget.h"
#include "chart/VolumeGraph.h"
#include "OrderBookViewWidget.h"

#include "indicator/Sma.h"

namespace Main {

ViewPort::ViewPort()
{

    this->setViewportUpdateMode(FullViewportUpdate);
    this->setDragMode(ScrollHandDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mScene = new ViewScene();
    setScene(mScene);



    // auto orderBook = new Main::OrderBookItem("DUSKUSDT");
    //    auto tradeListItem = new Main::TradeListItem("DUSKUSDT");
    //    auto rangeVolumeItem = new Main::RangeVolume();

    //    QObject::connect(tradeListItem,&TradeListItem::ticker,rangeVolumeItem,&RangeVolume::addTicker);


    //    mScene->addItem(orderBook);
    //    mScene->addItem(tradeListItem);
    //    mScene->addItem(rangeVolumeItem);



    //    orderBook->setPos(0,100);
    //    tradeListItem->setPos(550,100);
    //    rangeVolumeItem->setPos(1000,100);


    addItem("BTCUSDT");
    addItem("ETHUSDT");
    addItem("SOLUSDT");
    addItem("XRPUSDT");

   addItem("BCHUSDT");
   addItem("LTCUSDT");
   addItem("ETCUSDT");
   addItem("LINKUSDT");
   addItem("ADAUSDT");
   addItem("DASHUSDT");
   addItem("XMRUSDT");
   addItem("ZECUSDT");
   addItem("BNBUSDT");
   addItem("ONTUSDT");



}

void ViewPort::addItem(const QString &pairName)
{


    bool exist = false;
    Graphic::PairItem* _item;
    for( const auto &item : mScene->items() ){


        auto pair_Item = qgraphicsitem_cast<Graphic::PairItem*>(item);
        if( pair_Item ) {
            if( pair_Item->pair() == pairName ){
                _item = qgraphicsitem_cast<Graphic::PairItem*>(item);
                exist = true;
                break;
            }
        }

    }

    if( exist ) {
        this->centerOn(_item);
        _item->setFocusIndicate(true);
        return;
    }





    auto pairItem = new Graphic::PairItem(pairName);
    mItemList.push_back(pairItem);
    mScene->addItem(pairItem);
    pairItem->setPos(rowCount*(pairItem->boundingRect().width()+3),mAddedInternal*(pairItem->boundingRect().height()+3));
    QObject::connect(pairItem,&Graphic::PairItem::openUrlCliked,[=](){
        QDesktopServices::openUrl(QUrl("http://91.151.84.201:8893/?trade="+pairItem->pair()));
    });

    QObject::connect(pairItem,&Graphic::PairItem::openCandles,[=](const QPoint &point){
        Chart::ChartWidget* mWidget = new Chart::ChartWidget(pairItem->series());
        mWidget->show();
    });

    QObject::connect(pairItem,&Graphic::PairItem::openVolumeGraph,[=](){
        Chart::VolumeGraph* mWidget = new Chart::VolumeGraph(pairItem->series());
        mWidget->show();
    });

    QObject::connect( pairItem , &Graphic::PairItem::openOrderTimeLineBook , [=](){
        qDebug() << __LINE__ << __func__ ;
        auto orderBookViewWidget = new OrderBookViewWidget( );
        orderBookViewWidget->setPair( pairItem->pair() );
        orderBookViewWidget->show();
    });


    QObject::connect(pairItem,&Graphic::PairItem::sort,[=](const QString &interval){
        std::sort(mItemList.begin(),mItemList.end(),[&interval](const Graphic::PairItem* a,const Graphic::PairItem* b){

            if( interval == "1du"){
                return a->series()->getM1DinunteUpperPercent() > b->series()->getM1DinunteUpperPercent();
            }else if(interval == "12hu" ){
                return a->series()->getM12HinunteUpperPercent() > b->series()->getM12HinunteUpperPercent();
            }else if(interval == "4hu" ){
                return a->series()->getM4HinunteUpperPercent() > b->series()->getM4HinunteUpperPercent();
            }else if(interval == "1hu" ){
                return a->series()->getM1HinunteUpperPercent() > b->series()->getM1HinunteUpperPercent();
            }else if(interval == "15mu" ){
                return a->series()->getM15MinunteUpperPercent() > b->series()->getM15MinunteUpperPercent();
            }else if(interval == "5mu" ){
                return a->series()->getM5MinunteUpperPercent() > b->series()->getM5MinunteUpperPercent();
            }else if( interval == "U"){
                return a->series()->allUpperPercent() > b->series()->allUpperPercent();
            }else if( interval == "GUC"){
                return a->series()->upperGreenCount() > b->series()->upperGreenCount();
            }else if( interval == "TSU"){
                return a->series()->allUpperSumPercent() > b->series()->allUpperSumPercent();
            }

            else if( interval == "1dd"){
                return a->series()->getM1DDownPercent() > b->series()->getM1DDownPercent();
            }else if( interval == "12hd"){
                return a->series()->getM12HDownPercent() > b->series()->getM12HDownPercent();
            }else if( interval == "4hd"){
                return a->series()->getM4HDownPercent() > b->series()->getM4HDownPercent();
            }else if( interval == "1hd"){
                return a->series()->getM1HDownPercent() > b->series()->getM1HDownPercent();
            }else if( interval == "15md"){
                return a->series()->getM15MDownPercent() > b->series()->getM15MDownPercent();
            }else if( interval == "5md"){
                return a->series()->getM5MDownPercent() > b->series()->getM5MDownPercent();
            }else if( interval == "D"){
                return a->series()->allDownPercent() > b->series()->allDownPercent();
            }else if( interval == "GDC"){
                return a->series()->downGreenCount() > b->series()->downGreenCount();
            }else if( interval == "TSD"){
                return a->series()->allDownSumPercent() > b->series()->allDownSumPercent();
            }

            else if( interval == "1du%"){
                return a->series()->getM1DinuntePercent() > b->series()->getM1DinuntePercent();
            }else if( interval == "12hu%"){
                return a->series()->getM12HinuntePercent() > b->series()->getM12HinuntePercent();
            }else if( interval == "4hu%"){
                return a->series()->getM4HinuntePercent() > b->series()->getM4HinuntePercent();
            }else if( interval == "1hu%"){
                return a->series()->getM1HinuntePercent() > b->series()->getM1HinuntePercent();
            }else if( interval == "15mu%"){
                return a->series()->getM15MinuntePercent() > b->series()->getM15MinuntePercent();
            }else if( interval == "5mu%"){
                return a->series()->getM5MinuntePercent() > b->series()->getM5MinuntePercent();
            }

            else if( interval == "1dd%"){
                return a->series()->getM1DinuntePercent() < b->series()->getM1DinuntePercent();
            }else if( interval == "12hd%"){
                return a->series()->getM12HinuntePercent() < b->series()->getM12HinuntePercent();
            }else if( interval == "4hd%"){
                return a->series()->getM4HinuntePercent() < b->series()->getM4HinuntePercent();
            }else if( interval == "1hd%"){
                return a->series()->getM1HinuntePercent() < b->series()->getM1HinuntePercent();
            }else if( interval == "15md%"){
                return a->series()->getM15MinuntePercent() < b->series()->getM15MinuntePercent();
            }else if( interval == "5md%"){
                return a->series()->getM5MinuntePercent() < b->series()->getM5MinuntePercent();
            }


           else if( interval == "1dsma%"){
                return a->series()->getM1DinunteSMA200Percent() < b->series()->getM1MinunteSMA200Percent();

            }else if( interval == "12hsma%"){
                return a->series()->getM12HinunteSMA200Percent() < b->series()->getM12HinunteSMA200Percent();

            }else if( interval == "4hsma%"){
                return a->series()->getM4HinunteSMA200Percent() < b->series()->getM4HinunteSMA200Percent();

            }else if( interval == "1hsma%"){
                return a->series()->getM1HinunteSMA200Percent() < b->series()->getM1HinunteSMA200Percent();

            }else if( interval == "15sma%"){
                return a->series()->getM15MinunteSMA200Percent() < b->series()->getM15MinunteSMA200Percent();

            }else if( interval == "5sma%"){
                return a->series()->getM5MinunteSMA200Percent() < b->series()->getM5MinunteSMA200Percent();

            }else if( interval == "1sma%"){
                return a->series()->getM1MinunteSMA200Percent() < b->series()->getM1MinunteSMA200Percent();
            }

            else if( interval == "1dsmaa%"){
                return a->series()->getM1DinunteSMA200Percent() > b->series()->getM1MinunteSMA200Percent();

            }else if( interval == "12hsmaa%"){
                return a->series()->getM12HinunteSMA200Percent() > b->series()->getM12HinunteSMA200Percent();

            }else if( interval == "4hsmaa%"){
                return a->series()->getM4HinunteSMA200Percent() > b->series()->getM4HinunteSMA200Percent();

            }else if( interval == "1hsmaa%"){
                return a->series()->getM1HinunteSMA200Percent() > b->series()->getM1HinunteSMA200Percent();

            }else if( interval == "15smaa%"){
                return a->series()->getM15MinunteSMA200Percent() > b->series()->getM15MinunteSMA200Percent();

            }else if( interval == "5smaa%"){
                return a->series()->getM5MinunteSMA200Percent() > b->series()->getM5MinunteSMA200Percent();

            }else if( interval == "1smaa%"){
                return a->series()->getM1MinunteSMA200Percent() > b->series()->getM1MinunteSMA200Percent();
            }


            else if( interval == "1dema20%"){
                return a->series()->getM1DinunteEMA20Percent() > b->series()->getM1MinunteEMA20Percent();

            }else if( interval == "12hema20%"){
                return a->series()->getM12HinunteEMA20Percent() > b->series()->getM12HinunteEMA20Percent();

            }else if( interval == "4hema20%"){
                return a->series()->getM4HinunteEMA20Percent() > b->series()->getM4HinunteEMA20Percent();

            }else if( interval == "1hema20%"){
                return a->series()->getM1HinunteEMA200Percent() > b->series()->getM1HinunteEMA20Percent();

            }else if( interval == "15ema20%"){
                return a->series()->getM15MinunteEMA20Percent() > b->series()->getM15MinunteEMA20Percent();

            }else if( interval == "5ema20%"){
                return a->series()->getM5MinunteEMA20Percent() > b->series()->getM5MinunteEMA20Percent();

            }else if( interval == "1ema20%"){
                return a->series()->getM1MinunteEMA20Percent() > b->series()->getM1MinunteEMA20Percent();
            }


            else if( interval == "1dema20A%"){
                return a->series()->getM1DinunteEMA20Percent() < b->series()->getM1MinunteEMA20Percent();

            }else if( interval == "12hema20A%"){
                return a->series()->getM12HinunteEMA20Percent() < b->series()->getM12HinunteEMA20Percent();

            }else if( interval == "4hema20A%"){
                return a->series()->getM4HinunteEMA20Percent() < b->series()->getM4HinunteEMA20Percent();

            }else if( interval == "1hema20A%"){
                return a->series()->getM1HinunteEMA200Percent() < b->series()->getM1HinunteEMA20Percent();

            }else if( interval == "15ema20A%"){
                return a->series()->getM15MinunteEMA20Percent() < b->series()->getM15MinunteEMA20Percent();

            }else if( interval == "5ema20A%"){
                return a->series()->getM5MinunteEMA20Percent() < b->series()->getM5MinunteEMA20Percent();

            }else if( interval == "1ema20A%"){
                return a->series()->getM1MinunteEMA20Percent() < b->series()->getM1MinunteEMA20Percent();
            }


            else if( interval == "fullgreen"){
                auto [percenta,greenCounta,redCounta] = a->series()->getAllBarPercentAndColorCount();
                auto [percentb,greenCountb,redCountb] = b->series()->getAllBarPercentAndColorCount();

                if( greenCounta > greenCountb ){
                    return true;
                }else if(greenCounta == greenCountb ){
                    return percenta > percentb;
                }else{
                    return false;
                }

            }else if( interval == "fullred"){
                auto [percenta,greenCounta,redCounta] = a->series()->getAllBarPercentAndColorCount();
                auto [percentb,greenCountb,redCountb] = b->series()->getAllBarPercentAndColorCount();

                if( redCounta < redCountb ){
                    return true;
                }else if(redCounta == redCountb ){
                    return percenta < percentb;
                }else{
                    return false;
                }
            }else if( interval == "fullbarpercentA"){
                auto [percenta,greenCounta,redCounta] = a->series()->getAllBarPercentAndColorCount();
                auto [percentb,greenCountb,redCountb] = b->series()->getAllBarPercentAndColorCount();
                return percenta < percentb;
            }else if( interval == "fullbarpercentD"){
                auto [percenta,greenCounta,redCounta] = a->series()->getAllBarPercentAndColorCount();
                auto [percentb,greenCountb,redCountb] = b->series()->getAllBarPercentAndColorCount();
                return percenta > percentb;
            }

            return false;

        });

        int i = 0;
        int j = 0;
        for( const auto &item : mItemList ){
            item->setPos(i*(item->boundingRect().width()+3),j*(item->boundingRect().height()+3));
            j++;
            if( j >= mMaxRowCount ){
                i++;
                j = 0;
            }
        }
    });

    mAddedInternal++;
    if( mAddedInternal >= mMaxRowCount ){
        rowCount++;
        mAddedInternal = 0;
    }

    if( Session::SessionManager::instance()->pairContains(pairName) ){
        return;
    }

    Session::SessionManager::instance()->addPair(pairName);



    return;

//    this->setPairItem(pairName);


}




} // namespace Main


void Main::ViewPort::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}
