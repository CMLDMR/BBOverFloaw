#include "tradelistitem.h"
#include <QPainter>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDateTime>


namespace Main {

TradeListItem::TradeListItem(const QString &_mPair)
    :mPair(_mPair)
{

    mSocket = new QWebSocket();


    QObject::connect(mSocket,&QWebSocket::textMessageReceived,[=](const QString &msg){
        TradeItem item = QJsonDocument::fromJson(msg.toUtf8()).object();
        emit ticker(item,mAverage1000Ticker);

        mItemList.push_front(item);

        mMaxDollar = item.volDollar() > mMaxDollar ? item.volDollar() : mMaxDollar;

        while (mItemList.size() > 1000 ) {
            mItemList.pop_back();
        }
        this->update();
    });

    QObject::connect(mSocket,&QWebSocket::connected,[=](){
        qDebug() << "Socket Connectted";
    });

    mSocket->open(QUrl("wss://fstream.binance.com/ws/" + mPair.toLower() + "@aggTrade"));

}

} // namespace Main


QRectF Main::TradeListItem::boundingRect() const
{
    return QRectF(0,0,350,850);
}

void Main::TradeListItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),QColor(125,150,175));

    auto fontMetric = painter->fontMetrics();

    auto yOffset = 50.0;

    auto maxBuy = 0.0;
    auto maxSell = 0.0;

    int i = 1;
    for( const auto &item : mItemList ){
        if( item.isSell() ){
            maxSell += item.volDollar();
        }else{
            maxBuy += item.volDollar();
        }

        if( i > 50 ){
            continue;
        }

        painter->fillRect(QRectF(0,i*14-12+yOffset,boundingRect().width(),13),item.isSell() ? QColor(250,200,200) : QColor(200,250,200));

        auto percent = (item.volDollar()/mMaxDollar);
        painter->fillRect(QRectF(0,i*14-12+yOffset, boundingRect().width()* percent,13) ,item.isSell() ? QColor(255,25,25) : QColor(25,255,25));


        painter->drawText(0,i*14+yOffset,item.priceStr());
        painter->drawText(100,i*14+yOffset,item.qtyStr());

        painter->drawText(200-fontMetric.boundingRect(item.volDollarStr()).width(),i*14+yOffset,item.volDollarStr()+"$");

        painter->drawText(300,i*14+yOffset,item.timeStr());

        i++;
    }

    if( maxSell > 0 && maxBuy > 0 ){
        mAverage1000Ticker = (maxSell+maxBuy)/1000.0;
        painter->drawText(0,13,"Last " + QString::number(mItemList.size()) + " Trade Distrubution: "+ QString::number(mAverage1000Ticker));
        painter->fillRect(QRectF(0,15,boundingRect().width()*maxSell/(maxBuy+maxSell),15),QColor(250,100,100));
        painter->fillRect(QRectF(0,30,boundingRect().width()*maxBuy/(maxBuy+maxSell),15),QColor(100,250,100));
        painter->drawText(0,28,QString("%1").arg(maxSell/(maxBuy+maxSell)*100.0));
    }




}
