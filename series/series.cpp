#include "series.h"

#include "binance/kline.h"
#include "indicator/bollinger.h"
#include "global/utility.h"
#include "global/alarmwidget.h"

#include <QMutex>

namespace Series {

QMutex mutex;

Series::Series(const QString &_mPair, QObject *parent)
    : QObject{parent},mPair(_mPair)
{

    mImage = new QImage(316,140,QImage::Format_RGB888);
    mImage->fill(Qt::white);

    mThread = new QThread();
    this->moveToThread(mThread);
    QObject::connect(mThread,&QThread::started,this,&Series::SocketWorker);
    mThread->start(QThread::LowPriority);
}



QVector<Seri *> Series::seriList() const
{
    return mSeriList;
}

const double &Series::close() const
{
    return mClose;
}

void Series::SocketWorker()
{
    qDebug() << "Start Series";


    mPainter = new QPainter();
    mPainter->begin(mImage);
    mPainter->drawText(10,20,this->pair()+" Loading...");
    mPainter->drawRect(0,0,mImage->rect().width()-1,mImage->height()-1);
    mPainter->end();

    mSeriList.append(new Seri(mPair,"1m"));
    mClose = mSeriList.last()->kLineContainer().last().closePrice();

//    emit dataUpdated(false);
//    mSeriList.append(new Seri(mPair,"3m"));
//    emit dataUpdated(false);
    mSeriList.append(new Seri(mPair,"5m"));
    mClose = mSeriList.last()->close();

    emit dataUpdated(false);
    mSeriList.append(new Seri(mPair,"15m"));
    emit dataUpdated(false);
//    mSeriList.append(new Seri(mPair,"30m"));
//    emit dataUpdated(false);
    mSeriList.append(new Seri(mPair,"1h"));
    emit dataUpdated(false);
    mSeriList.append(new Seri(mPair,"4h"));
    emit dataUpdated(false);
    mSeriList.append(new Seri(mPair,"1d"));
//    emit dataUpdated(false);
//    mSeriList.append(new Seri(mPair,"1w"));



    mSocket = Binance::Public::WebSocketAPI::WebSocketAPI::createSocket(mPair);

    QObject::connect(mSocket,&Binance::Public::WebSocketAPI::WebSocketAPI::receivedAggregate,[=](const Binance::Public::WebSocketAPI::Aggregate aggregate ){
        mClose = aggregate.price();
        mTimeStr = QDateTime::fromMSecsSinceEpoch(aggregate.eventTime()).time().toString("hh:mm:ss");

        bool Is_this_kline_closed = false;

        for( auto &item : mSeriList ){

            auto kline = item->last();
            kline.setEventTime(aggregate.eventTime());

            if( aggregate.eventTime() > kline.closeTime() ){

                kline.setOpenTime(item->openTime()+item->duration());
                kline.setCloseTime(item->closeTime()+item->duration());
                kline.setHighPrice(aggregate.price());
                kline.setLowPrice(aggregate.price());
                kline.setClosePrice(aggregate.price());
                kline.setOpenPrice(aggregate.price());
                kline.setVolume(aggregate.quantity());
                kline.setNumberOfTrade(1);

                if( !aggregate.isMaker() ){
                    kline.setTakerQuotaAseetVolume(aggregate.price()*aggregate.quantity());
                    kline.setTakerBaseAssetVolume(aggregate.quantity());

                }else{
                    kline.setTakerQuotaAseetVolume(0);
                    kline.setTakerBaseAssetVolume(0);

                }

                item->append(kline);
                item->removeFirst();

                Is_this_kline_closed = true;
            }else{


                kline.setClosePrice(aggregate.price());


                if( aggregate.price() > kline.highPrice() ){
                    kline.setHighPrice(aggregate.price());
                }

                if( aggregate.price() < kline.lowPrice() ){
                    kline.setLowPrice(aggregate.price());
                }

                kline.setVolume(kline.volume()+aggregate.quantity());
                kline.setAssetVolume(kline.quoteAssetVolume()+aggregate.quantity()*aggregate.price());
                if( !aggregate.isMaker() ){
                    kline.setTakerBaseAssetVolume(kline.takerBuyBaseAssetVolume()+aggregate.quantity());
                    kline.setTakerQuotaAseetVolume(kline.takerBuyQuoteAssetVolume()+aggregate.price()*aggregate.quantity());
                }
                kline.setNumberOfTrade(kline.numberOfTrades()+1);
                item->removelast();
                item->append(kline);
            }
            prePareImage(mPainter);

//            emit item->updated();

        }


        emit dataUpdated(Is_this_kline_closed);


    });

    mSocket->startAggregateStream();
}

QImage *Series::image() const
{
    return mImage;
}

void Series::prePareImage(QPainter *painter)
{


    mImage->fill(Qt::white);
    painter->begin(mImage);


    painter->drawRect(0,0,mImage->rect().width()-1,mImage->height()-1);
    //    auto fontMetric = painter->fontMetrics();

    {// Pair name
        //        auto rect = fontMetric.boundingRect(mSeries->pair());
        painter->drawText(5,15 ,this->pair().mid(0,this->pair().size()-4));
    }

    {// Last Price
        //        auto rect = fontMetric.boundingRect(QString::number(mSeries->close()));
        painter->drawText(50, 15 ,QString::number(this->close()));
//        painter->drawText(5, 15+15 ,"U% 2.38");
        painter->drawText(5, 15+30 ,"U% 3.18");
        painter->drawText(5, 15+45 ,"U% 5.00");
        painter->drawText(5, 15+60 ,"U% 6.18");
//        painter->drawText(5, 15+75 ,"D% 2.38");
        painter->drawText(5, 15+90 ,"D% 3.18");
        painter->drawText(5, 15+105 ,"D% 5.00");
        painter->drawText(5, 15+120 ,"D% 6.18");

    }



    {// intervals
        int xPos = 110;
        mAllUpperPercent = 0;
        for( const auto &seri : this->seriList() ){

            auto rect = QRectF(0,0,0,15);
            auto pen = painter->pen();
            painter->setPen(QPen(Qt::white));
//            painter->setBackground(Qt::gray);
            painter->fillRect(xPos-1,0,35,rect.height()+2,Qt::darkGray);
            painter->drawText(xPos, rect.height() ,seri->interval());
            painter->setPen(pen);
//            painter->setBackground(Qt::white);

            int yPos = rect.height();

            mAllUpperPercent = 0;
            mAllDownPercent = 0;

            {// Bollinger Percent 2.38

                auto [upper,down] = Indicator::Bollinger::bollingerPercent(*seri,60,2.38);

//                painter->drawText(5, 15+75 ,"D% 2.38 "+Global::getFixedPrecision(down));

                if( seri->interval() == "5m" ){
                    m5MinunteUpperPercent = upper;
                    m5MDownPercent = down;
                    auto [u,m,d] = Indicator::Bollinger::bollinger(*seri,60,2.38);
                    painter->drawText(5, 15+75 ,"D% 2.38 "+Global::getFixedPrecision(d));
                    painter->drawText(5, 15+15 ,"U% 2.38 "+Global::getFixedPrecision(u));

                }

                if( seri->interval() == "15m" ){
                    m15MinunteUpperPercent = upper;
                    m15MDownPercent = down;
                }

                if( seri->interval() == "1h" ){
                    m1HinunteUpperPercent = upper;
                    m1HDownPercent = down;
                }

                if( seri->interval() == "4h" ){
                    m4HinunteUpperPercent = upper;
                    m4HDownPercent = down;
                }


                if( seri->interval() == "1d" ){
                    m1DinunteUpperPercent = upper;
                    m1DDownPercent = down;
                }


                mAllUpperPercent += upper;
                mAllDownPercent += down;

                if( upper > 0 ){
                    painter->fillRect(QRectF(xPos+1,yPos+2,33,rect.height()),Qt::green);
//                    Global::Alarm::AlarmWidget::instance()->popUpMessage(mPair + " SHORT " + QString("%1").arg(2.38));
                    mAlarmActivated = true;
                }
                if( down > 0 ){
                    painter->fillRect(QRectF(xPos+1,yPos+2+60,33,rect.height()),Qt::green);
                    mAlarmActivated = true;
                }
                painter->drawText(xPos, yPos+75 ,Global::getFixedPrecision(down));

                painter->drawText(xPos, yPos+15 ,Global::getFixedPrecision(upper)); yPos += 15;

            }

            {// Bollinger Percent 3.82

                auto [upper,down] = Indicator::Bollinger::bollingerPercent(*seri,60,3.82);
                if( upper > 0 ){
                    painter->fillRect(QRectF(xPos+1,yPos+2,33,rect.height()),Qt::green);
//                    Global::Alarm::AlarmWidget::instance()->popUpMessage(mPair + " SHORT " + QString("%1").arg(3.82));
                    mAlarmActivated = true;
                }
                if( down > 0 ){
                    painter->fillRect(QRectF(xPos+1,yPos+2+60,33,rect.height()),Qt::green);
                    mAlarmActivated = true;
                }
                painter->drawText(xPos, yPos+75 ,Global::getFixedPrecision(down));
                painter->drawText(xPos, yPos+15 ,Global::getFixedPrecision(upper)); yPos += 15;
            }

            {// Bollinger Percent 5

                auto [upper,down] = Indicator::Bollinger::bollingerPercent(*seri,60,5);
                if( upper > 0 ){
                    painter->fillRect(QRectF(xPos+1,yPos+2,33,rect.height()),Qt::green);
//                    Global::Alarm::AlarmWidget::instance()->popUpMessage(mPair + " SHORT " + QString("%1").arg(5));
                    mAlarmActivated = true;
                }
                if( down > 0 ){
                    painter->fillRect(QRectF(xPos+1,yPos+2+60,33,rect.height()),Qt::green);
                    mAlarmActivated = true;
                }
                painter->drawText(xPos, yPos+75 ,Global::getFixedPrecision(down));
                painter->drawText(xPos, yPos+15 ,Global::getFixedPrecision(upper)); yPos += 15;
            }

            {// Bollinger Percent 6.18

                auto [upper,down] = Indicator::Bollinger::bollingerPercent(*seri,60,6.18);

                if( upper > 0 ){
                    painter->fillRect(QRectF(xPos+1,yPos+2,33,rect.height()),Qt::green);
                    mAlarmActivated = true;
                }

                if( down > 0 ){
                    painter->fillRect(QRectF(xPos+1,yPos+2+60,33,rect.height()),Qt::green);
                    mAlarmActivated = true;
                }
                painter->drawText(xPos, yPos+75 ,Global::getFixedPrecision(down));
                painter->drawText(xPos, yPos+15 ,Global::getFixedPrecision(upper)); yPos += 15;
            }


            pen = painter->pen();
            painter->setPen(QPen(Qt::gray,1,Qt::DotLine));
            painter->drawLine(xPos-2,1,xPos-2,mImage->height()-2);

            painter->setPen(pen);
            xPos += 35;
        }
    }

    painter->end();

}

double Series::getM15MDownPercent() const
{
    return m15MDownPercent;
}

double Series::getM1HDownPercent() const
{
    return m1HDownPercent;
}

double Series::getM4HDownPercent() const
{
    return m4HDownPercent;
}

double Series::getM1DDownPercent() const
{
    return m1DDownPercent;
}

double Series::allDownPercent() const
{
    return mAllDownPercent;
}

void Series::setM15MinunteUpperPercent(double newM15MinunteUpperPercent)
{
    m15MinunteUpperPercent = newM15MinunteUpperPercent;
}

double Series::getM5MDownPercent() const
{
    return m5MDownPercent;
}

double Series::getM1DinunteUpperPercent() const
{
    return m1DinunteUpperPercent;
}

double Series::getM4HinunteUpperPercent() const
{
    return m4HinunteUpperPercent;
}

double Series::getM1HinunteUpperPercent() const
{
    return m1HinunteUpperPercent;
}

double Series::getM15MinunteUpperPercent() const
{
    return m15MinunteUpperPercent;
}

double Series::allUpperPercent() const
{
    return mAllUpperPercent;
}

double Series::getM5MinunteUpperPercent() const
{
    return m5MinunteUpperPercent;
}

QString Series::timeStr() const
{
    return mTimeStr;
}

QString Series::pair() const
{
    return mPair;
}

std::optional<Seri *> Series::getSeri(const QString &interval)
{
    Seri* seri{nullptr};

    for( const auto &item : mSeriList ){
        if( item->interval() == interval ){
            seri = item;
            break;
        }
    }


    return seri;
}

} // namespace Series
