#include "series.h"

#include "binance/kline.h"

namespace Series {

Series::Series(const QString &_mPair, QObject *parent)
    : QObject{parent},mPair(_mPair)
{
    mThread = new QThread();
    this->moveToThread(mThread);
    QObject::connect(mThread,&QThread::started,this,&Series::SocketWorker);

    qDebug() << "Start Series";
    mSeriList.append(new Seri(_mPair,"1m"));
    mSeriList.append(new Seri(_mPair,"3m"));
    mSeriList.append(new Seri(_mPair,"5m"));
    mSeriList.append(new Seri(_mPair,"15m"));
    mSeriList.append(new Seri(_mPair,"30m"));
    mSeriList.append(new Seri(_mPair,"1h"));
    mSeriList.append(new Seri(_mPair,"4h"));
    mSeriList.append(new Seri(_mPair,"1d"));
    mSeriList.append(new Seri(_mPair,"1w"));

    qDebug() << "All Get Completed";

    mThread->start(QThread::LowPriority);

}



QVector<Seri *> Series::seriList() const
{
    return mSeriList;
}

void Series::SocketWorker()
{
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


//        qDebug() << QDateTime::fromMSecsSinceEpoch(kLine.closeTime()).time().toString("hh:mm:ss")
//                 << QDateTime::fromMSecsSinceEpoch(kLine.eventTime()).time().toString("hh:mm:ss");

//        for( int i = 0 ; i < mSeriList.size() ; i++ ){
//            auto item = mSeriList[i];
//            qDebug()  << item->pair()<< item->interval() <<
//                QDateTime::fromMSecsSinceEpoch(item->kLineContainer().last().closeTime()).time().toString("hh:mm:ss") <<
//                item->kLineContainer().last().closeTime();
//        }
        emit dataUpdated();
    });

    mSocket->startAggregateStream();
}


} // namespace Series
