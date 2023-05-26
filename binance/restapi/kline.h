#ifndef BINANCE_PUBLIC_RESTAPI_KLINE_H
#define BINANCE_PUBLIC_RESTAPI_KLINE_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

namespace Binance {
namespace Public {
namespace RestAPI {

class KLine : public QJsonArray
{
public:
    KLine();
    KLine( const QJsonArray &other );

    qulonglong openTime() const;
    QString openPrice() const;
    QString highPrice() const;
    QString lowPrice() const;
    QString closePrice() const;
    QString volume() const;
    qulonglong closeTime() const;
    QString quoteAssetVolume() const;
    qulonglong numberOfTrades() const;
    QString takerBuyBaseAssetVolume() const;
    QString takerBuyQuoteAssetVolume() const;

};

class KLineContainer{
public:
    KLineContainer( const QByteArray &array );

    int size() const;

private:
    QVector<KLine> mKCandles;
};


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





} // namespace RestAPI
} // namespace Public
} // namespace Binance

#endif // BINANCE_PUBLIC_RESTAPI_KLINE_H
