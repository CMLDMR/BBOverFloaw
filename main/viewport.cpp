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
#include <QDesktopServices>

#include <algorithm>


#include "graphicsItem/pairitem.h"
#include "chart/chartwidget.h"

namespace Main {

ViewPort::ViewPort()
{

    this->setViewportUpdateMode(FullViewportUpdate);
    this->setDragMode(ScrollHandDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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


//        addItem("BTCUSDT");
//        addItem("ETHUSDT");
//        addItem("BCHUSDT");
//        addItem("XRPUSDT");
//        addItem("EOSUSDT");
//        addItem("LTCUSDT");
//        addItem("KAVAUSDT");
//        addItem("TOMOUSDT");
//        addItem("TRXUSDT");



}

void ViewPort::addItem(const QString &pairName)
{


    bool exist = false;
    for( const auto &item : mScene->items() ){
        if( qgraphicsitem_cast<Graphic::PairItem*>(item)->pair() == pairName ){
            exist = true;
            break;
        }
    }

    if( exist ) return;





    auto pairItem = new Graphic::PairItem(pairName);
    mItemList.push_back(pairItem);
    mScene->addItem(pairItem);
    pairItem->setPos(rowCount*(pairItem->boundingRect().width()+3),mAddedInternal*(pairItem->boundingRect().height()+3));
    QObject::connect(pairItem,&Graphic::PairItem::openUrlCliked,[=](){
        QDesktopServices::openUrl(QUrl("http://80.253.245.39:8893/?trade="+pairItem->pair()));
    });

    QObject::connect(pairItem,&Graphic::PairItem::openCandles,[=](const QPoint &point){
        Chart::ChartWidget* mWidget = new Chart::ChartWidget(pairItem->series());
        mWidget->show();
    });


    QObject::connect(pairItem,&Graphic::PairItem::sort,[=](const QString &interval){
        std::sort(mItemList.begin(),mItemList.end(),[&interval](const Graphic::PairItem* a,const Graphic::PairItem* b){

            if( interval == "1du"){
                return a->series()->getM1DinunteUpperPercent() > b->series()->getM1DinunteUpperPercent();
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
            }

            else if( interval == "1dd"){
                return a->series()->getM1DDownPercent() > b->series()->getM1DDownPercent();
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
            }

        });

        int i = 0;
        int j = 0;
        for( const auto &item : mItemList ){
            item->setPos(i*(item->boundingRect().width()+3),j*(item->boundingRect().height()+3));
            j++;
            if( j >= 15 ){
                i++;
                j = 0;
            }
        }
    });

    mAddedInternal++;
    if( mAddedInternal >= 15 ){
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

void ViewPort::setPairItem(const QString &pairName)
{
    auto btcTableItem = new Main::PairTableItem(pairName);
    mScene->addItem(btcTableItem);
    btcTableItem->setPos(rowCount*(btcTableItem->boundingRect().width()+2),mAddedInternal*(btcTableItem->boundingRect().height()+5));

    //TODO:  remove Item Crashed
    QObject::connect(btcTableItem,&Main::AbtractItem::deleteClicked,[=](){
        btcTableItem->setWillRemove(true);

        if( !Session::SessionManager::instance()->removePair(btcTableItem->pair()) ){
            qDebug() << "did not remove or pair exist!";
        }
        mScene->removeItem(btcTableItem);

    });

    QObject::connect(btcTableItem,&Main::AbtractItem::openUrlCliked,[=](){

    QDesktopServices::openUrl(QUrl("http://80.253.245.39:8893/?trade="+btcTableItem->pair()));
    });
    QObject::connect(btcTableItem,&Main::AbtractItem::openInTradingView,[=](){
        QDesktopServices::openUrl(QUrl("https://www.tradingview.com/chart/?symbol=BINANCE:"+btcTableItem->pair()+".P"));
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
    if( mAddedInternal >= 12 ){
        rowCount++;
        mAddedInternal = 0;
    }
}



} // namespace Main


void Main::ViewPort::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}
