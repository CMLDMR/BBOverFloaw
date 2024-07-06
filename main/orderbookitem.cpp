#include "orderbookitem.h"
#include <QPainter>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QThread>
#include <QMutex>


namespace Main {

QMutex mutex;


OrderBookItem::OrderBookItem(const QString &_mPair)
    :mPair(_mPair)
{

    mSocket = new QWebSocket();

    mAskOrders = new Orders();
    mBidOrders = new Orders();

    QObject::connect(mSocket,&QWebSocket::textMessageReceived,[=](const QString &msg){
        auto obj = QJsonDocument::fromJson(msg.toUtf8()).object();
        *mAskOrders = obj.value("a").toArray();
        *mBidOrders = obj.value("b").toArray();
        this->update();
    });

    QObject::connect(mSocket,&QWebSocket::connected,[=](){
        qDebug() << "Socket Connectted";
    });

    mSocket->open(QUrl("wss://fstream.binance.com/ws/"+mPair.toLower()+"@depth20@100ms"));
//    mSocket->open(QUrl("wss://fstream.binance.com/stream?streams=iotxusdt@depth"));

}

Orders::Orders()
{

}

Orders::Orders(const QJsonArray &other)
{
    while( this->size() ){
        this->removeFirst();
    }

    for( const auto &item : other ){
        this->append(item);
    }

}

double Orders::price(const int &index) const
{
    return this->at(index).toArray().at(0).toVariant().toDouble();
}

QString Orders::priceStr(const int &index) const
{
    return this->at(index).toArray().at(0).toString();
}

double Orders::qty(const int &index) const
{
    return this->at(index).toArray().at(1).toVariant().toDouble();
}

QString Orders::qtyStr(const int &index) const
{
    return this->at(index).toArray().at(1).toString();

}

double Orders::volDollar(const int &index) const
{
    return price(index) * qty(index);
}

double Orders::maxVol() const
{
    double max = 0;
    for( const auto &item : *this ){
        max = max < item.toArray().at(1).toVariant().toDouble() ? item.toArray().at(1).toVariant().toDouble() : max;
    }
    return max;
}




} // namespace Main


QRectF Main::OrderBookItem::boundingRect() const
{
    return QRectF(0,0,500,350);
}

void Main::OrderBookItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    auto fontMetric = painter->fontMetrics();
    qreal height = fontMetric.height();
    painter->fillRect(boundingRect(),QColor(245,245,245));

    painter->drawRect(boundingRect());

    painter->drawLine(boundingRect().width()/2,0,boundingRect().width()/2,boundingRect().height());

    auto yOffset = 15;

    painter->drawText(65 -fontMetric.boundingRect("Vol$").width(),yOffset-2,"Vol$");
    painter->drawText(145-fontMetric.boundingRect("Qty").width(),yOffset-2,"Qty");
    painter->drawText(240-fontMetric.boundingRect("Price").width(),yOffset-2,"Price");

    painter->drawText(261,yOffset-2,"Price");
    painter->drawText(336,yOffset-2,"Qty");
    painter->drawText(406,yOffset-2,"Vol$");

    auto bidObj = *mBidOrders;
    auto askObj = *mAskOrders;

    auto bidMax = bidObj.maxVol();
    auto askMax = askObj.maxVol();

    auto maxVol = bidMax < askMax ? askMax : bidMax;

    qreal totalBuySideDollar  = 0;
    qreal totalSellSideDollar = 0;


    for( int i = 0 ; i < bidObj.size() ; i++ ){
        auto xWidth = bidObj.qty(i)/maxVol*200;

        painter->fillRect(QRectF(245-xWidth,i*height+yOffset,xWidth,height-1),QColor(255,200,200));

        auto bidText = bidObj.priceStr(i);
        painter->drawText(240-fontMetric.boundingRect(bidText).width(),(i+1)*height-3+yOffset,bidText);

        bidText = bidObj.qtyStr(i);
        painter->drawText(145-fontMetric.boundingRect(bidText).width(),(i+1)*height-3+yOffset,bidText);

        bidText =QString("%1").arg(bidObj.volDollar(i),6,'f',0);
        painter->drawText(65-fontMetric.boundingRect(bidText).width(),(i+1)*height-3+yOffset,bidText);

        totalBuySideDollar += bidObj.price( i ) * bidObj.qty( i );
    }



    for( int i = 0 ; i < askObj.size() ; i++ ){
        auto xWidth = askObj.qty(i)/maxVol*200;

        painter->fillRect(QRectF(256,i*height+yOffset,xWidth,height-1),QColor(255,200,200));

        auto bidText = askObj.priceStr(i);
        painter->drawText(261,(i+1)*height-3+yOffset,bidText);

        bidText = askObj.qtyStr(i);
        painter->drawText(336,(i+1)*height-3+yOffset,bidText);

        bidText =QString("%1").arg(askObj.volDollar(i),6,'f',0);
        painter->drawText(406,(i+1)*height-3+yOffset,bidText);

        totalSellSideDollar += askObj.price( i ) * askObj.qty( i );
    }


    emit updatedOrderBookVol( totalBuySideDollar , totalSellSideDollar );

//    for( int i = 0 ; i < askObj.size() ; i++ ){
//        painter->fillRect(QRectF(250,i*12,askObj.qty(i)/maxVol*150,11),Qt::red);

//        painter->drawText(250,i*12+15,QString("%1").arg(askObj.price(i)));
//        painter->drawText(325,i*12+15,QString("%1").arg(askObj.qty(i)));
//        painter->drawText(400,i*12+15,QString("%1").arg(askObj.volDollar(i),6,'f',0));
//    }
//    for( int i = 0 ; i < askObj.size() ; i++ ){

//    }


}
