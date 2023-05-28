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

const QString Seri::interval() const
{
    return mInterval;
}

Seri::iterator Seri::begin()
{
    return iterator(mKLineContainer.begin());
}

Seri::iterator Seri::end()
{
    return iterator(mKLineContainer.end());
}

Binance::Public::KLine &Seri::iterator::operator*() const
{
    return *current;
}

Seri::iterator &Seri::iterator::operator++()
{
    ++current;
    return *this;
}

bool Seri::iterator::operator!=(const iterator &other)
{
    return current != other.current;
}










} // namespace Series
