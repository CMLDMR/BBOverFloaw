#include "series.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>

#include "indicator/bollinger.h"


namespace Main {

Series_Legacy::Series_Legacy(const QString pair, const QString &interval)
    :mTimeInterval(interval),
    mPair(pair)
{


    mBollinger = new Indicator::Bollinger(this);

    mAccessManager = new QNetworkAccessManager();

    QObject::connect(mAccessManager,&QNetworkAccessManager::finished,[=](QNetworkReply* reply){
        auto array = QJsonDocument::fromJson(reply->readAll()).array();
        mSeries.clear();
        for( const auto &item : array ){
            CandleItem _item = item.toArray();
            mSeries.push_back(_item);

        }
        emit ready();

        QTimer::singleShot(1000,[=](){
//            mSocket->open(QUrl("wss://fstream.binance.com/ws/"+mPair.toLower()+"@kline_"+mTimeInterval));
            mThread->start();
        });
    });





    mThread = new QThread();
    QObject::connect(mThread,&QThread::started,this,&Series_Legacy::startSocket);



    mAccessManager->get(QNetworkRequest(QUrl("https://fapi.binance.com/fapi/v1/continuousKlines?pair="+pair+"&contractType=PERPETUAL&interval="+interval+"&limit=50")));

}

Series_Legacy::~Series_Legacy()
{
    qDebug() << "Delete Series";
    mSocket->close(QWebSocketProtocol::CloseCode::CloseCodeNormal);
    delete mSocket;
    mSocket = nullptr;
    delete mBollinger;
    delete mAccessManager;
    mThread->deleteLater();
}

const QVector<CandleItem> &Series_Legacy::getSeries() const
{
    return mSeries;
}

QString Series_Legacy::timeInterval() const
{
    return mTimeInterval;
}

const CandleItem &Series_Legacy::lastCandle() const
{
    return mSeries.last();
}

void Series_Legacy::update(const QString &pair, const QString &interval)
{
    //    mTimeInterval = interval;
//    mAccessManager->get(QNetworkRequest(QUrl("https://fapi.binance.com/fapi/v1/continuousKlines?pair="+pair+"&contractType=PERPETUAL&interval="+interval+"&limit=50")));

}

Indicator::Bollinger *Series_Legacy::bollinger() const
{
    return mBollinger;
}

std::unordered_map<QString, std::tuple<double, double, double> > Series_Legacy::valueList() const
{
    return mValueList;
}

void Series_Legacy::replaceLastCandle(const QString &msg)
{
    auto obj = QJsonDocument::fromJson(msg.toLatin1()).object();
    auto kLineObj = obj["k"].toObject();

    if( mSeries.size() <= 0 ) return;

    CandleItem Candle = mSeries.last();
    Candle.replace(1,kLineObj["o"]);
    Candle.replace(2,kLineObj["h"]);
    Candle.replace(3,kLineObj["l"]);
    Candle.replace(4,kLineObj["c"]);

    mLastCloseTimeEpoch = obj["E"].toVariant().toLongLong();

    if( kLineObj["x"].toBool() ){
        mSeries.removeFirst();
//        qDebug() << "New Candle " << mPair << mTimeInterval;
    }else{
        mSeries.removeLast();
    }
    mSeries.append(Candle);


    if( this->getSeries().size() ){
        auto [upper,mid,down] = this->bollinger()->getLast();
        auto close = this->lastCandle().close();
        mValueList[this->timeInterval()] = std::make_tuple(upper,down,close);
        emit ready();
    }
}

void Series_Legacy::startSocket()
{

    mSocket = new QWebSocket();

    QObject::connect(mSocket,&QWebSocket::textMessageReceived,this,&Series_Legacy::replaceLastCandle);

    QObject::connect(mSocket,&QWebSocket::connected,[=](){
        //        qDebug() << "Socket Connected" << mPair << mTimeInterval;
    });

    mSocket->open(QUrl("wss://fstream.binance.com/ws/"+mPair.toLower()+"@kline_"+mTimeInterval));


}

qulonglong Series_Legacy::lastCloseTimeEpoch() const
{
    return mLastCloseTimeEpoch;
}

QString Series_Legacy::pair() const
{
    return mPair;
}



} // namespace Main
