#include "kline.h"

namespace Binance {
namespace Public {

//    1499040000000,      0 // Kline open time
//    "0.01634790",       1 // Open price
//    "0.80000000",       2 // High price
//    "0.01575800",       3 // Low price
//    "0.01577100",       4 // Close price
//    "148976.11427815",  5 // Volume
//    1499644799999,      6 // Kline Close time
//    "2434.19055334",    7 // Quote asset volume
//    308,                8 // Number of trades
//    "1756.87402397",    9 // Taker buy base asset volume
//    "28.46694368",      10 // Taker buy quote asset volume
//    "0"                 11 // Unused field, ignore.



KLine::KLine()
{

}

KLine::KLine(const QJsonArray &other)
{
//    insert("e",other.at(6));   //Open Time
//    insert("t",other.at(0));   //Open Time
//    insert("o",other.at(1));   //Open Price
//    insert("c",other.at(4));   //Close Price
//    insert("h",other.at(2));   //High Price
//    insert("l",other.at(3));   //Low Price
//    insert("v",other.at(5));   //Volume
//    insert("T",other.at(6));   //Close Time
//    insert("q",other.at(7));   //asset Volume
//    insert("n",other.at(8));   //number of Trade
//    insert("V",other.at(9));   //taker base Asset Volume
//    insert("Q",other.at(10));   //taker quota Asset Volume
//    insert("x",true);   //new Candle

    mEventTime = other.at(6).toVariant().toLongLong();
    mOpenTime = other.at(0).toVariant().toLongLong();
    mCloseTime = other.at(6).toVariant().toLongLong();

    mOpenPrice = other.at(1).toVariant().toDouble();
    mHighPrice = other.at(2).toVariant().toDouble();
    mLowPrice = other.at(3).toVariant().toDouble();
    mClosePrice = other.at(4).toVariant().toDouble();

    mVolume = other.at(5).toVariant().toDouble();
    mAssetVolume = other.at(7).toVariant().toDouble();
    mNumberOfTrade = other.at(8).toVariant().toLongLong();
    mTakerBaseAssetVolume = other.at(9).toVariant().toDouble();
    mTakerQuotaAseetVolume = other.at(10).toVariant().toDouble();
    mIs_this_kline_closed = true;

}

KLine::KLine(const QJsonObject &object)
{
    auto kObj = object.value("k").toObject();
//    insert("t",kObj.value("t"));   //Open Time *
//    insert("o",kObj.value("o"));   //Open Price *
//    insert("c",kObj.value("c"));   //Close Price
//    insert("h",kObj.value("h"));   //High Price
//    insert("l",kObj.value("l"));   //Low Price
//    insert("v",kObj.value("v"));   //Volume
//    insert("T",kObj.value("T"));   //Close Time
//    insert("q",kObj.value("q"));   //asset Volume
//    insert("n",kObj.value("n"));   //number of Trade
//    insert("V",kObj.value("V"));   //base Asset Volume
//    insert("Q",kObj.value("Q"));   //quota Asset Volume
//    insert("x",kObj.value("x"));   //new Candle
//    insert("e",object.value("E")); //new Candle

    mEventTime = object.value("E").toVariant().toLongLong();
    mOpenTime = kObj.value("t").toVariant().toLongLong();
    mCloseTime = kObj.value("T").toVariant().toLongLong();

    mOpenPrice = kObj.value("o").toVariant().toDouble();
    mHighPrice = kObj.value("h").toVariant().toDouble();
    mLowPrice = kObj.value("l").toVariant().toDouble();
    mClosePrice = kObj.value("c").toVariant().toDouble();

    mVolume = kObj.value("v").toVariant().toDouble();
    mAssetVolume = kObj.value("q").toVariant().toDouble();
    mNumberOfTrade = kObj.value("n").toVariant().toLongLong();
    mTakerBaseAssetVolume = kObj.value("V").toVariant().toDouble();
    mTakerQuotaAseetVolume = kObj.value("Q").toVariant().toDouble();

    mIs_this_kline_closed = object.value("x").toBool();

}

qint64 KLine::eventTime() const
{
    return mEventTime;
}

qint64 KLine::openTime() const
{
    return mOpenTime;
}

double KLine::openPrice() const
{
    return mOpenPrice;
}

double KLine::highPrice() const
{
    return mHighPrice;
}

double KLine::lowPrice() const
{
    return mLowPrice;
}

double KLine::closePrice() const
{
    return mClosePrice;
}

double KLine::volume() const
{
    return mVolume;
}

qint64 KLine::closeTime() const
{
    return mCloseTime;
}

double KLine::quoteAssetVolume() const
{
    return mAssetVolume;
}

qint64 KLine::numberOfTrades() const
{
    return mNumberOfTrade;
}

double KLine::takerBuyBaseAssetVolume() const
{
    return mTakerBaseAssetVolume;
}

double KLine::takerBuyQuoteAssetVolume() const
{
    return mTakerQuotaAseetVolume;
}

bool KLine::Is_this_kline_closed() const
{
    return mIs_this_kline_closed;
}

double KLine::quotaOpen() const
{
    return mQuotaAssetVolumeOpen;
}

double KLine::quotaHigh() const
{
    return mQuotaAssetVolumeHigh;
}

double KLine::quotaLow() const
{
    return mQuotaAssetVolumeLow;
}

double KLine::quotaClose() const
{
    return mQuotaAssetVolumeClose;
}

qint64 KLine::OpenCloseDuration()
{
    auto fark = this->closeTime()-this->openTime();
    return fark;
}

KLine &KLine::operator=(const KLine &other)
{
    mEventTime = other.mEventTime;
    mOpenTime = other.mOpenTime;
    mCloseTime = other.mCloseTime;

    mOpenPrice = other.mOpenPrice;
    mHighPrice = other.mHighPrice;
    mLowPrice = other.mLowPrice;
    mClosePrice = other.mClosePrice;

    mVolume = other.mVolume;
    mAssetVolume = other.mAssetVolume;
    mNumberOfTrade = other.mNumberOfTrade;
    mTakerBaseAssetVolume = other.mTakerBaseAssetVolume;
    mTakerQuotaAseetVolume = other.mTakerQuotaAseetVolume;
    mIs_this_kline_closed = other.mIs_this_kline_closed;
    return *this;
}

void KLine::setEventTime(qint64 newEventTime)
{
    mEventTime = newEventTime;
}

void KLine::setOpenTime(qint64 newOpenTime)
{
    mOpenTime = newOpenTime;
}

void KLine::setCloseTime(qint64 newCloseTime)
{
    mCloseTime = newCloseTime;
}

void KLine::setOpenPrice(double newOpenPrice)
{
    mOpenPrice = newOpenPrice;
}

void KLine::setHighPrice(double newHighPrice)
{
    mHighPrice = newHighPrice;
}

void KLine::setLowPrice(double newLowPrice)
{
    mLowPrice = newLowPrice;
}

void KLine::setClosePrice(double newClosePrice)
{
    mClosePrice = newClosePrice;
}

void KLine::setVolume(double newVolume)
{
    mVolume = newVolume;
}

void KLine::setAssetVolume(double newAssetVolume)
{
    mAssetVolume = newAssetVolume;
}

void KLine::setNumberOfTrade(qint64 newNumberOfTrade)
{
    mNumberOfTrade = newNumberOfTrade;
}

void KLine::setTakerBaseAssetVolume(double newTakerBaseAssetVolume)
{
    mTakerBaseAssetVolume = newTakerBaseAssetVolume;
}

void KLine::setTakerQuotaAseetVolume(double newTakerQuotaAseetVolume)
{
    mTakerQuotaAseetVolume = newTakerQuotaAseetVolume;
}

void KLine::setQuotaAssetVolume(const bool isMaker, const double quotaVolume, bool newCandle)
{
    if( newCandle ) {
        mQuotaAssetVolumeOpen = mQuotaAssetVolumeClose;
        mQuotaAssetVolumeLow = mQuotaAssetVolumeClose;
        mQuotaAssetVolumeHigh = mQuotaAssetVolumeClose;
    }

    {
        if( ! isMaker ) {
            mQuotaAssetVolumeClose += quotaVolume;
        }
        else{
            mQuotaAssetVolumeClose -= quotaVolume;
        }

        if( mQuotaAssetVolumeHigh < mQuotaAssetVolumeClose ) mQuotaAssetVolumeHigh = mQuotaAssetVolumeClose;
        if( mQuotaAssetVolumeLow > mQuotaAssetVolumeClose )  mQuotaAssetVolumeLow = mQuotaAssetVolumeClose;
    }


}

void KLine::setQuotaAssetVolumeHigh(double newQuotaAssetVolumeHigh)
{
    mQuotaAssetVolumeHigh = newQuotaAssetVolumeHigh;
}

void KLine::setQuotaAssetVolumeLow(double newQuotaAssetVolumeLow)
{
    mQuotaAssetVolumeLow = newQuotaAssetVolumeLow;
}

void KLine::setQuotaAssetVolumeOpen(double newQuotaAssetVolumeOpen)
{
    mQuotaAssetVolumeOpen = newQuotaAssetVolumeOpen;
}

void KLine::setQuotaAssetVolumeClose(double newQuotaAssetVolumeClose)
{
    mQuotaAssetVolumeClose = newQuotaAssetVolumeClose;
}


} // namespace Public
} // namespace Binance
