#include "seri.h"
#include "binance/restapi/restapi.h"

namespace Series {

Seri::Seri(const QString &pair, const QString &interval, QObject *parent)
    : QObject{parent},mPair(pair),mInterval(interval)
{

    // if( interval != "15ms" ) {
        mKLineContainer = Binance::Public::RestAPI::RestAPI::instance()->getCandles(mPair,mInterval,200);
    // }
        if( mKLineContainer.size() )
            qDebug() << mPair << mInterval << " Completed" << mKLineContainer.constLast().closeTime();

    const qint64 baseDuration = 60000;
    // if( interval == "15ms" ) mDuration = baseDuration/4;
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

// void Seri::replacelast(const Binance::Public::KLine &kline)
// {
//     this->mKLineContainer.replace(mKLineContainer.capacity(),kline);
// }

const QString Seri::interval() const
{
    return mInterval;
}

const double Seri::close(const int &index) const
{
    if( index == -1 ) return mKLineContainer.last().closePrice();
    return mKLineContainer.at(index).closePrice();
}

const double Seri::open(const int &index) const
{
    if( index == -1 ) return mKLineContainer.last().openPrice();

    return mKLineContainer.at(index).openPrice();
}

const double Seri::high(const int &index) const
{
    if( index == -1 ) return mKLineContainer.last().highPrice();

    return mKLineContainer.at(index).highPrice();
}

const double Seri::low(const int &index) const
{
    if( index == -1 ) return mKLineContainer.last().lowPrice();
    return mKLineContainer.at(index).lowPrice();
}

const qint64 Seri::openTime(const int &index) const
{
    if( index == -1 ) return mKLineContainer.last().openTime();

    return mKLineContainer.at(index).openTime();
}

const qint64 Seri::closeTime(const int &index) const
{
    if( index == -1 ) return mKLineContainer.last().closeTime();

    return mKLineContainer.at(index).closeTime();
}

const double Seri::volume(const int &index) const
{
    if( index == -1 ) return mKLineContainer.last().volume();
    return mKLineContainer.at(index).volume();
}

const double Seri::takerVolume(const int &index) const
{
    if( index == -1 ) return mKLineContainer.last().takerBuyBaseAssetVolume();
    return mKLineContainer.at(index).takerBuyBaseAssetVolume();
}

const qint64 Seri::numberOfTrade(const int &index) const
{
    if( index == -1 ) return mKLineContainer.last().numberOfTrades();
    return mKLineContainer.at(index).numberOfTrades();
}

const double Seri::percentLastBar(const int &index) const
{
    if( index == -1 ) return (this->close()-this->open())/this->open()*100.;
    return (this->close(index)-this->open(index))/this->open(index)*100.;

}

const double Seri::quotaClose(const int &index) const
{
    if( index == -1 ) return mKLineContainer.last().quotaClose();
    return mKLineContainer.at(index).quotaClose();
}

const double Seri::quotaOpen(const int &index) const
{
    if( index == -1 ) return mKLineContainer.last().quotaOpen();
    return mKLineContainer.at(index).quotaOpen();
}

const double Seri::quotaHigh(const int &index) const
{
    if( index == -1 ) return mKLineContainer.last().quotaHigh();
    return mKLineContainer.at(index).quotaHigh();
}

const double Seri::quotaLow(const int &index) const
{
    if( index == -1 ) return mKLineContainer.last().quotaLow();
    return mKLineContainer.at(index).quotaLow();
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

const double Seri::maxQuotaVolume() const
{

    auto maxElement = std::max_element( mKLineContainer.begin() , mKLineContainer.end() , []( Binance::Public::KLine line1 , Binance::Public::KLine line2 ) {
        return line1.quotaHigh() < line2.quotaHigh();
    });

    if( maxElement != mKLineContainer.end() ) {
        return maxElement->quotaHigh();
    }
    else{
        return 0;
    }
}

const double Seri::minQuotaVolume() const
{

    auto minElement = std::min_element( mKLineContainer.begin() , mKLineContainer.end() , []( Binance::Public::KLine line1 , Binance::Public::KLine line2 ) {
        return line1.quotaLow() < line2.quotaLow();
    });

    if( minElement != mKLineContainer.end() ) {
        return minElement->quotaLow();
    }
    else{
        return 0;
    }
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
