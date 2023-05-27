#include "seri.h"
#include "binance/restapi/restapi.h"

namespace Series {

Seri::Seri(const QString &pair, const QString &interval, QObject *parent)
    : QObject{parent},mPair(pair),mInterval(interval)
{
    mKLineContainer = Binance::Public::RestAPI::RestAPI::instance()->getCandles(mPair,mInterval,50);
    qDebug() << mPair << mInterval << " Completed" << mKLineContainer.constLast().closeTime();
}

QString Seri::pair() const
{
    return mPair;
}

QVector<Binance::Public::KLine> &Seri::kLineContainer()
{
    return mKLineContainer;
}

QString Seri::interval() const
{
    return mInterval;
}










} // namespace Series
