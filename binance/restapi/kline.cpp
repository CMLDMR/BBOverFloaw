#include "kline.h"

namespace Binance {
namespace Public {
namespace RestAPI {

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
    :QJsonArray(other)
{

}

qulonglong KLine::openTime() const
{
    if( size() ){
        return at(0).toVariant().toULongLong();
    }else{
        return 0;
    }
}

QString KLine::openPrice() const
{
    if( size() ){
        return at(1).toString();
    }else{
        return "";
    }
}

QString KLine::highPrice() const
{
    if( size() ){
        return at(2).toString();
    }else{
        return "";
    }
}

QString KLine::lowPrice() const
{
    if( size() ){
        return at(3).toString();
    }else{
        return "";
    }
}

QString KLine::closePrice() const
{
    if( size() ){
        return at(4).toString();
    }else{
        return "";
    }
}

QString KLine::volume() const
{
    if( size() ){
        return at(5).toString();
    }else{
        return "";
    }
}

qulonglong KLine::closeTime() const
{
    if( size() ){
        return at(6).toVariant().toULongLong();
    }else{
        return 0;
    }
}

QString KLine::quoteAssetVolume() const
{
    if( size() ){
        return at(7).toString();
    }else{
        return "";
    }
}

qulonglong KLine::numberOfTrades() const
{
    if( size() ){
        return at(8).toVariant().toULongLong();
    }else{
        return 0;
    }
}

QString KLine::takerBuyBaseAssetVolume() const
{
    if( size() ){
        return at(9).toString();
    }else{
        return 0;
    }
}

QString KLine::takerBuyQuoteAssetVolume() const
{
    if( size() ){
        return at(10).toString();
    }else{
        return 0;
    }
}

KLineContainer::KLineContainer(const QByteArray &array)
{
    mKCandles.clear();
    auto _array = QJsonDocument::fromJson(array).array();
    for( const auto &item : _array ){
        KLine line(item.toArray());
        mKCandles.push_back(line);
    }
}

int KLineContainer::size() const
{
    return mKCandles.size();
}

} // namespace RestAPI
} // namespace Public
} // namespace Binance
