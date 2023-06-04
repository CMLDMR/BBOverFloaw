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
    mClose = mSeriList.last()->kLineContainer().last().closePrice().toDouble();

    emit dataUpdated(false);
    mSeriList.append(new Seri(mPair,"3m"));
    emit dataUpdated(false);
    mSeriList.append(new Seri(mPair,"5m"));
    emit dataUpdated(false);
    mSeriList.append(new Seri(mPair,"15m"));
    emit dataUpdated(false);
    mSeriList.append(new Seri(mPair,"30m"));
    emit dataUpdated(false);
    mSeriList.append(new Seri(mPair,"1h"));
    emit dataUpdated(false);
    mSeriList.append(new Seri(mPair,"4h"));
    emit dataUpdated(false);
    mSeriList.append(new Seri(mPair,"1d"));
    emit dataUpdated(false);
    mSeriList.append(new Seri(mPair,"1w"));



    mSocket = Binance::Public::WebSocketAPI::WebSocketAPI::createSocket(mPair);

    QObject::connect(mSocket,&Binance::Public::WebSocketAPI::WebSocketAPI::receivedKLine,[=](const Binance::Public::KLine &kLine ){
        mClose = kLine.closePrice().toDouble();
        mTimeStr = QDateTime::fromMSecsSinceEpoch(kLine.eventTime()).time().toString("hh:mm:ss");


        for( auto &item : mSeriList ){
            if( kLine.eventTime() >= item->kLineContainer().last().closeTime() ){

                auto _kline = kLine;
                auto fark = item->kLineContainer().last().OpenCloseDuration();
                _kline.insert("t",item->kLineContainer().last().closeTime()+1);
                _kline.insert("T",item->kLineContainer().last().closeTime()+fark);


                item->kLineContainer().append(_kline);
                if( item->kLineContainer().size() > 50 ) item->kLineContainer().removeFirst();
            }else{

                auto _kline = kLine;
                _kline.insert("o",item->kLineContainer().last().openPrice());

                if( _kline.highPrice().toDouble() < item->kLineContainer().last().highPrice().toDouble() ){
                    _kline.insert("h",item->kLineContainer().last().highPrice());
                }

                if( _kline.lowPrice().toDouble() > item->kLineContainer().last().lowPrice().toDouble() ){
                    _kline.insert("l",item->kLineContainer().last().lowPrice());
                }

                _kline.insert("t",item->kLineContainer().last().openTime());
                _kline.insert("T",item->kLineContainer().last().closeTime());

                item->kLineContainer().removeLast();
                item->kLineContainer().append(_kline);
            }
        }
        emit dataUpdated(kLine.Is_this_kline_closed());
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
