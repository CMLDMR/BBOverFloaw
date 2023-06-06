#include "series.h"

#include "binance/kline.h"

namespace Series {

Series::Series(const QString &_mPair, QObject *parent)
    : QObject{parent},mPair(_mPair)
{
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

    mSeriList.append(new Seri(mPair,"1m"));
    mClose = mSeriList.last()->kLineContainer().last().closePrice();

    emit dataUpdated(false);
//    mSeriList.append(new Seri(mPair,"3m"));
//    emit dataUpdated(false);
//    mSeriList.append(new Seri(mPair,"5m"));
//    emit dataUpdated(false);
//    mSeriList.append(new Seri(mPair,"15m"));
//    emit dataUpdated(false);
//    mSeriList.append(new Seri(mPair,"30m"));
//    emit dataUpdated(false);
//    mSeriList.append(new Seri(mPair,"1h"));
//    emit dataUpdated(false);
//    mSeriList.append(new Seri(mPair,"4h"));
//    emit dataUpdated(false);
//    mSeriList.append(new Seri(mPair,"1d"));
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

                if( aggregate.isMaker() ){
                    kline.setTakerQuotaAseetVolume(aggregate.price()*aggregate.quantity());
                }else{
                    kline.setTakerQuotaAseetVolume(0);
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
                kline.setTakerBaseAssetVolume(kline.takerBuyBaseAssetVolume()+aggregate.quantity());
                kline.setTakerQuotaAseetVolume(kline.takerBuyQuoteAssetVolume()+aggregate.price()*aggregate.quantity());
                kline.setNumberOfTrade(kline.numberOfTrades()+1);
                item->removelast();
                item->append(kline);
            }

//            qDebug() <<"LAST: " << item->last();



            emit item->updated();

        }
        emit dataUpdated(Is_this_kline_closed);


    });

    mSocket->startAggregateStream();
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
