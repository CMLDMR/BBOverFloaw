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

void Series::SocketWorker()
{
    qDebug() << "Start Series";

    mSeriList.append(new Seri(mPair,"1m"));
    emit dataUpdated();
    mSeriList.append(new Seri(mPair,"3m"));
    emit dataUpdated();
    mSeriList.append(new Seri(mPair,"5m"));
    emit dataUpdated();
    mSeriList.append(new Seri(mPair,"15m"));
    emit dataUpdated();
    mSeriList.append(new Seri(mPair,"30m"));
    emit dataUpdated();
    mSeriList.append(new Seri(mPair,"1h"));
    emit dataUpdated();
    mSeriList.append(new Seri(mPair,"4h"));
    emit dataUpdated();
    mSeriList.append(new Seri(mPair,"1d"));
    emit dataUpdated();
    mSeriList.append(new Seri(mPair,"1w"));



    mSocket = Binance::Public::WebSocketAPI::WebSocketAPI::createSocket(mPair);

    QObject::connect(mSocket,&Binance::Public::WebSocketAPI::WebSocketAPI::receivedKLine,[=](const Binance::Public::KLine &kLine ){

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
                _kline.insert("t",item->kLineContainer().last().openTime());
                _kline.insert("T",item->kLineContainer().last().closeTime());

                item->kLineContainer().removeLast();
                item->kLineContainer().append(_kline);
            }
        }
        emit dataUpdated();
    });

    mSocket->startAggregateStream();
}


} // namespace Series
