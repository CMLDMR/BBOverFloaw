#include "kline.h"

//namespace Binance {
//namespace Public {
//namespace WebSocketAPI {

//KLine::KLine()
//{

//}

//KLine::KLine(const QJsonObject &object)
//{
//    insert("t",object.value("t"));   //Open Time
//    insert("o",object.value("o"));   //Open Price
//    insert("c",object.value("c"));   //Close Price
//    insert("h",object.value("h"));   //High Price
//    insert("l",object.value("l"));   //Low Price
//    insert("v",object.value("v"));   //Volume
//    insert("T",object.value("T"));   //Close Time
//    insert("q",object.value("q"));   //asset Volume
//    insert("n",object.value("n"));   //number of Trade
//    insert("V",object.value("V"));   //base Asset Volume
//    insert("Q",object.value("Q"));   //quota Asset Volume
//    insert("x",object.value("x"));   //new Candle

//}

//qint64 KLine::openTime() const
//{
//    return value("t").toVariant().toLongLong();
//}

//QString KLine::openPrice() const
//{
//    return value("o").toString();
//}

//QString KLine::highPrice() const
//{
//    return value("h").toString();
//}

//QString KLine::lowPrice() const
//{
//    return value("l").toString();
//}

//QString KLine::closePrice() const
//{
//    return value("c").toString();
//}

//QString KLine::volume() const
//{
//    return value("v").toString();
//}

//qint64 KLine::closeTime() const
//{
//    return value("T").toVariant().toLongLong();
//}

//QString KLine::quoteAssetVolume() const
//{
//    return value("q").toString();
//}

//qint64 KLine::numberOfTrades() const
//{
//    return value("n").toVariant().toLongLong();
//}

//QString KLine::takerBuyBaseAssetVolume() const
//{
//    return value("V").toString();
//}

//QString KLine::takerBuyQuoteAssetVolume() const
//{
//    return value("Q").toString();
//}

//bool KLine::Is_this_kline_closed() const
//{
//    return value("x").toBool();
//}

//} // namespace WebSocketAPI
//} // namespace Public
//} // namespace Binance
