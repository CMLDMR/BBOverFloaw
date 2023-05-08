#include "pairtableitem.h"

#include <QPainter>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

namespace Main {

PairTableItem::PairTableItem(const QString &pair)
    :mPair(pair)
{

//    mBollingerIntervalList.append("1m");
//    mBollingerIntervalList.append("3m");
//    mBollingerIntervalList.append("5m");
    mBollingerIntervalList.append("15m");   // 1x
    mBollingerIntervalList.append("30m");   // 2x
    mBollingerIntervalList.append("1h");    // 4x
    mBollingerIntervalList.append("2h");    // 8x
    mBollingerIntervalList.append("4h");    // 16x
    mBollingerIntervalList.append("6h");    // 24x
    mBollingerIntervalList.append("8h");    // 32x
    mBollingerIntervalList.append("12h");   // 48x
    mBollingerIntervalList.append("1d");    // 96x
    mBollingerIntervalList.append("3d");    // 288x
    mBollingerIntervalList.append("1w");    // 672x

    for( const auto &item : mBollingerIntervalList ){
        mValueList[item] = std::make_tuple(0,0,0);
    }

    mSeris = new Series(mPair,"15m");


    mBollinger = new Indicator::Bollinger(mSeris);


    QObject::connect(mSeris,&Series::ready,[=](){
        if( !canRequst ){
            if( mSeris->getSeries().size() ){
                auto [upper,mid,down] = mBollinger->getLast();
                auto close = mSeris->lastCandle().close();
                mValueList[mSeris->timeInterval()] = std::make_tuple(upper,down,close);
                this->update();
            }
            canRequst = true;
        }
    });


    canRequst = true;

    this->startTimer(500);

}




QRectF PairTableItem::boundingRect() const
{
    return QRectF(-1,-1,800,60);
}

void PairTableItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(boundingRect());

    painter->setPen(QPen(Qt::black));


    auto fontMetric = painter->fontMetrics();
    QRectF symbolRect(0,0,fontMetric.boundingRect(mPair).width(),fontMetric.boundingRect(mPair).height());
    painter->fillRect(symbolRect,QColor(190,190,190));
    painter->drawText(symbolRect,mPair);

    if( mSeris->getSeries().size() ){
        auto pen = painter->font();
        painter->setFont(QFont("Tahoma",18));
//        QRectF bolligerDown(0,0,50,15);
//        painter->fillRect(bolligerDown,QColor(190,190,190));
        painter->drawText(0,50,mSeris->lastCandle().closeStr());
        painter->setFont(pen);
    }




    int i = 1;
    double upperPercent = 0;
    double downPercent = 0;

    for( const auto &StaticInterval : mBollingerIntervalList ){

        for( const auto &[interval,tup] : mValueList ){

            if( interval == StaticInterval ){
                auto &[upper,down,close] = tup;


                QRectF bolliger1m(i*51+70,0,50,15);
                if( interval == mLastInterval ){
                    painter->fillRect(bolliger1m,QColor(255,190,190));
                }else{
                    painter->fillRect(bolliger1m,QColor(190,190,190));
                }

                painter->drawText(bolliger1m,interval);

                auto _upper = (close - upper)/upper*100;
                QRectF bolligerUpper(i*51+70,20,50,15);
                painter->fillRect(bolligerUpper,_upper> 0 ? QColor(150,255,150) : QColor(255,150,150));
                painter->drawText(bolligerUpper,QString::number(_upper));

                auto _down = (down - close)/down*100;
                QRectF bolligerDown(i*51+70,40,50,15);
                painter->fillRect(bolligerDown,_down> 0 ? QColor(150,255,150) : QColor(255,150,150));
                painter->drawText(bolligerDown,QString::number(_down));
                i++;

                if( interval == "15m" ){
                    upperPercent += _upper;
                    downPercent += _down;
                }else if( interval == "30m" ){
                    upperPercent += _upper*2;
                    downPercent += _down*2;
                }else if( interval == "1h" ){
                    upperPercent += _upper*4;
                    downPercent += _down*4;
                }else if( interval == "2h" ){
                    upperPercent += _upper*8;
                    downPercent += _down*8;
                }else if( interval == "4h" ){
                    upperPercent += _upper*16;
                    downPercent += _down*16;
                }else if( interval == "6h" ){
                    upperPercent += _upper*24;
                    downPercent += _down*24;
                }else if( interval == "8h" ){
                    upperPercent += _upper*32;
                    downPercent += _down*32;
                }else if( interval == "12h" ){
                    upperPercent += _upper*48;
                    downPercent += _down*48;
                }else if( interval == "1d" ){
                    upperPercent += _upper*96;
                    downPercent += _down*96;
                }else if( interval == "3d" ){
                    upperPercent += _upper*288;
                    downPercent += _down*288;
                }else if( interval == "1w" ){
                    upperPercent += _upper*672;
                    downPercent += _down*672;
                }
            }


        }
    }


    QRectF bolligerUpper(i*51+70,20,50,15);
    painter->fillRect(bolligerUpper,upperPercent > 0 ? QColor(150,255,150) : QColor(255,150,150));
    painter->drawText(bolligerUpper,QString::number(upperPercent/20));

    QRectF bolligerDown(i*51+70,40,50,15);
    painter->fillRect(bolligerDown,downPercent > 0 ? QColor(150,255,150) : QColor(255,150,150));
    painter->drawText(bolligerDown,QString::number(downPercent/20));
    i++;

    QRectF upperRect(i*51+70,20,fontMetric.boundingRect(mPair).width(),fontMetric.boundingRect("Upper").height());
    painter->fillRect(upperRect,QColor(190,190,190));
    painter->drawText(upperRect,"Upper");

    QRectF downRect(i*51+70,40,fontMetric.boundingRect(mPair).width(),fontMetric.boundingRect("Down").height());
    painter->fillRect(downRect,QColor(190,190,190));
    painter->drawText(downRect,"Down");

}


} // namespace Main




void Main::PairTableItem::timerEvent(QTimerEvent *event)
{
    if( canRequst ){
        canRequst = false;
        requestIntervalIndex = requestIntervalIndex % mBollingerIntervalList.size();
        mLastInterval = mBollingerIntervalList.at(requestIntervalIndex);
        mSeris->update(mPair,mLastInterval);
        requestIntervalIndex++;
    }
}
