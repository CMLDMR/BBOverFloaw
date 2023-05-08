#include "series.h"

namespace Main {

Series::Series(const QString pair, const QString &interval)
    :mTimeInterval(interval),
    mPair(pair)
{
    mAccessManager = new QNetworkAccessManager();

    QObject::connect(mAccessManager,&QNetworkAccessManager::finished,[=](QNetworkReply* reply){
        auto array = QJsonDocument::fromJson(reply->readAll()).array();
        mSeries.clear();
        for( const auto &item : array ){
            CandleItem _item = item.toArray();
            mSeries.push_back(_item);
        }
        emit ready();
    });
}

const QVector<CandleItem> &Series::getSeries() const
{
    return mSeries;
}

QString Series::timeInterval() const
{
    return mTimeInterval;
}

const CandleItem &Series::lastCandle() const
{
    return mSeries.last();
}

void Series::update(const QString &pair, const QString &interval)
{
    mTimeInterval = interval;
    mAccessManager->get(QNetworkRequest(QUrl("https://fapi.binance.com/fapi/v1/continuousKlines?pair="+pair+"&contractType=PERPETUAL&interval="+interval+"&limit=50")));
}



} // namespace Main
