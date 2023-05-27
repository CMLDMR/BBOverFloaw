#ifndef BINANCE_PUBLIC_WEBSOCKETAPI_KLINE_H
#define BINANCE_PUBLIC_WEBSOCKETAPI_KLINE_H

#include <QJsonObject>

#include "binance/kline.h"

namespace Binance {
namespace Public {
namespace WebSocketAPI {

//class KLine : public QJsonObject
//{
//public:
//    KLine();
//    KLine( const QJsonObject &object );

//    qint64 openTime() const;
//    QString openPrice() const;
//    QString highPrice() const;
//    QString lowPrice() const;
//    QString closePrice() const;
//    QString volume() const;
//    qint64 closeTime() const;
//    QString quoteAssetVolume() const;
//    qint64 numberOfTrades() const;
//    QString takerBuyBaseAssetVolume() const;
//    QString takerBuyQuoteAssetVolume() const;
//    bool Is_this_kline_closed() const;


//    KLine& operator=(const Binance::Public::RestAPI::KLine &other ){
//        insert("t",other.openTime());   //Open Time
//        insert("o",other.openPrice());   //Open Price
//        insert("c",other.closePrice());   //Close Price
//        insert("h",other.highPrice());   //High Price
//        insert("l",other.lowPrice());   //Low Price
//        insert("v",other.volume());   //Volume
//        insert("T",other.closeTime());   //Close Time
//        insert("q",other.quoteAssetVolume());   //asset Volume
//        insert("n",other.numberOfTrades());   //number of Trade
//        insert("V",other.takerBuyBaseAssetVolume());   //base Asset Volume
//        insert("Q",other.takerBuyQuoteAssetVolume());   //quota Asset Volume
//        insert("x",true);   //new Candle
//        return *this;
//    }

//};

} // namespace WebSocketAPI
} // namespace Public
} // namespace Binance


/*
"e": "kline",         // Event type
"E": 1672515782136,   // Event time
"s": "BNBBTC",        // Symbol
"k": {
"t": 1672515780000, // Kline start time ***
"T": 1672515839999, // Kline close time
"s": "BNBBTC",      // Symbol
"i": "1m",          // Interval
"f": 100,           // First trade ID
"L": 200,           // Last trade ID
"o": "0.0010",      // Open price ***
"c": "0.0020",      // Close price ***
"h": "0.0025",      // High price ***
"l": "0.0015",      // Low price ***
"v": "1000",        // Base asset volume
"n": 100,           // Number of trades
"x": false,         // Is this kline closed?
"q": "1.0000",      // Quote asset volume
"V": "500",         // Taker buy base asset volume

"Q": "0.500",       // Taker buy quote asset volume
"B": "123456"       // Ignore
}
 * */

#endif // BINANCE_PUBLIC_WEBSOCKETAPI_KLINE_H
