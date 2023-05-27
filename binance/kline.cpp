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
    insert("e",other.at(6));   //Open Time
    insert("t",other.at(0));   //Open Time
    insert("o",other.at(1));   //Open Price
    insert("c",other.at(4));   //Close Price
    insert("h",other.at(2));   //High Price
    insert("l",other.at(3));   //Low Price
    insert("v",other.at(5));   //Volume
    insert("T",other.at(6));   //Close Time
    insert("q",other.at(7));   //asset Volume
    insert("n",other.at(8));   //number of Trade
    insert("V",other.at(9));   //base Asset Volume
    insert("Q",other.at(10));   //quota Asset Volume
    insert("x",true);   //new Candle

}

KLine::KLine(const QJsonObject &object)
{
    auto kObj = object.value("k").toObject();
    insert("t",kObj.value("t"));   //Open Time
    insert("o",kObj.value("o"));   //Open Price
    insert("c",kObj.value("c"));   //Close Price
    insert("h",kObj.value("h"));   //High Price
    insert("l",kObj.value("l"));   //Low Price
    insert("v",kObj.value("v"));   //Volume
    insert("T",kObj.value("T"));   //Close Time
    insert("q",kObj.value("q"));   //asset Volume
    insert("n",kObj.value("n"));   //number of Trade
    insert("V",kObj.value("V"));   //base Asset Volume
    insert("Q",kObj.value("Q"));   //quota Asset Volume
    insert("x",kObj.value("x"));   //new Candle
    insert("e",object.value("E")); //new Candle

}

qint64 KLine::eventTime() const
{
    return value("e").toVariant().toLongLong();
}

qint64 KLine::openTime() const
{
    return value("t").toVariant().toLongLong();
}

QString KLine::openPrice() const
{
    return value("o").toString();
}

QString KLine::highPrice() const
{
    return value("h").toString();
}

QString KLine::lowPrice() const
{
    return value("l").toString();
}

QString KLine::closePrice() const
{
    return value("c").toString();
}

QString KLine::volume() const
{
    return value("v").toString();
}

qint64 KLine::closeTime() const
{
    return value("T").toVariant().toLongLong();
}

QString KLine::quoteAssetVolume() const
{
    return value("q").toString();
}

qint64 KLine::numberOfTrades() const
{
    return value("n").toVariant().toLongLong();
}

QString KLine::takerBuyBaseAssetVolume() const
{
    return value("V").toString();
}

QString KLine::takerBuyQuoteAssetVolume() const
{
    return value("Q").toString();
}

bool KLine::Is_this_kline_closed() const
{
    return value("x").toBool();
}

qint64 KLine::OpenCloseDuration()
{
    auto fark = this->closeTime()-this->openTime();
    return fark;
}

KLine &KLine::operator=(const KLine &other)
{
    insert("t",other.value("t"));   //Open Time
    insert("o",other.value("o"));   //Open Price
    insert("c",other.value("c"));   //Close Price
    insert("h",other.value("h"));   //High Price
    insert("l",other.value("l"));   //Low Price
    insert("v",other.value("v"));   //Volume
    insert("T",other.value("T"));   //Close Time
    insert("q",other.value("q"));   //asset Volume
    insert("n",other.value("n"));   //number of Trade
    insert("V",other.value("V"));   //base Asset Volume
    insert("Q",other.value("Q"));   //quota Asset Volume
    insert("x",other.value("x"));   //new Candle
    insert("x",other.Is_this_kline_closed());   //new Candle
    insert("e",other.value("e"));   //event Time

    return *this;
}


} // namespace Public
} // namespace Binance
