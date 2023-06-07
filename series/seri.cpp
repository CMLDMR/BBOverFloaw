#include "seri.h"
#include "binance/restapi/restapi.h"

namespace Series {

Seri::Seri(const QString &pair, const QString &interval, QObject *parent)
    : QObject{parent},mPair(pair),mInterval(interval)
{
    mKLineContainer = Binance::Public::RestAPI::RestAPI::instance()->getCandles(mPair,mInterval,150);
    qDebug() << mPair << mInterval << " Completed" << mKLineContainer.constLast().closeTime();

    const qint64 baseDuration = 60000;
    if( interval == "1m" ) mDuration = baseDuration;
    if( interval == "3m" ) mDuration = baseDuration*3;
    if( interval == "5m" ) mDuration = baseDuration*5;
    if( interval == "15m" ) mDuration = baseDuration*15;
    if( interval == "30m" ) mDuration = baseDuration*30;
    if( interval == "45m" ) mDuration = baseDuration*45;
    if( interval == "1h" ) mDuration = baseDuration*60;
    if( interval == "2h" ) mDuration = baseDuration*120;
    if( interval == "3h" ) mDuration = baseDuration*180;
    if( interval == "4h" ) mDuration = baseDuration*240;
    if( interval == "6h" ) mDuration = baseDuration*360;
    if( interval == "8h" ) mDuration = baseDuration*480;
    if( interval == "12h" ) mDuration = baseDuration*720;
    if( interval == "1d" ) mDuration = baseDuration*1440;
    if( interval == "3d" ) mDuration = baseDuration*1440*3;
    if( interval == "1w" ) mDuration = baseDuration*1440*7;

}

QString Seri::pair() const
{
    return mPair;
}

QVector<Binance::Public::KLine> &Seri::kLineContainer()
{
    return mKLineContainer;
}

void Seri::append(const Binance::Public::KLine &kline)
{
    this->mKLineContainer.append(kline);
}

void Seri::removelast()
{
    this->mKLineContainer.removeLast();
}

void Seri::removeFirst()
{
    mKLineContainer.removeFirst();
}

void Seri::replacelast(const Binance::Public::KLine &kline)
{
    this->mKLineContainer.replace(mKLineContainer.capacity(),kline);
}

const QString Seri::interval() const
{
    return mInterval;
}

const double Seri::close(const int &index)
{
    if( index == -1 ) return mKLineContainer.last().closePrice();
    return mKLineContainer.at(index).closePrice();
}

const double Seri::open(const int &index)
{
    if( index == -1 ) return mKLineContainer.last().openPrice();

    return mKLineContainer.at(index).openPrice();
}

const double Seri::high(const int &index)
{
    if( index == -1 ) return mKLineContainer.last().highPrice();

    return mKLineContainer.at(index).highPrice();
}

const double Seri::low(const int &index)
{
    if( index == -1 ) return mKLineContainer.last().lowPrice();
    return mKLineContainer.at(index).lowPrice();
}

const qint64 Seri::openTime(const int &index)
{
    if( index == -1 ) return mKLineContainer.last().openTime();

    return mKLineContainer.at(index).openTime();
}

const qint64 Seri::closeTime(const int &index)
{
    if( index == -1 ) return mKLineContainer.last().closeTime();

    return mKLineContainer.at(index).closeTime();
}

const double Seri::volume(const int &index)
{
    if( index == -1 ) return mKLineContainer.last().volume();
    return mKLineContainer.at(index).volume();
}

const double Seri::takerVolume(const int &index)
{
    if( index == -1 ) return mKLineContainer.last().takerBuyBaseAssetVolume();
    return mKLineContainer.at(index).takerBuyBaseAssetVolume();
}

Binance::Public::KLine Seri::last() const
{
    return mKLineContainer.last();
}

std::size_t Seri::size() const
{
    return mKLineContainer.size();
}

const Binance::Public::KLine &Seri::at(const int &index) const
{

    return mKLineContainer.at(index);
}

const double Seri::maxPrice() const
{
    double maxprice = mKLineContainer.first().highPrice();
    for( const auto &item : mKLineContainer ){
        if( item.highPrice() > maxprice ){
            maxprice = item.highPrice();
        }
    }
    return maxprice;
}

const double Seri::minPrice() const
{
    double minprice = mKLineContainer.first().lowPrice();
    for( const auto &item : mKLineContainer ){
        if( item.lowPrice() < minprice ){
            minprice = item.lowPrice();
        }
    }
    return minprice;
}

Seri::iterator Seri::begin()
{
    return iterator(mKLineContainer.begin());
}

Seri::iterator Seri::end()
{
    return iterator(mKLineContainer.end());
}

qint64 Seri::duration() const
{
    return mDuration;
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
