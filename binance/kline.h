#ifndef BINANCE_PUBLIC_RESTAPI_KLINE_H
#define BINANCE_PUBLIC_RESTAPI_KLINE_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

namespace Binance {
namespace Public {

class KLine : public QJsonObject
{
public:
    KLine();
    KLine( const QJsonArray &other ); //From Get Method
    KLine( const QJsonObject &object ); // From Websocket

    qint64 eventTime() const;
    qint64 openTime() const;
    double openPrice() const;
    double highPrice() const;
    double lowPrice() const;
    double closePrice() const;
    double volume() const;
    qint64 closeTime() const;
    double quoteAssetVolume() const;
    qint64 numberOfTrades() const;
    double takerBuyBaseAssetVolume() const;
    double takerBuyQuoteAssetVolume() const;
    bool Is_this_kline_closed() const;

    qint64 OpenCloseDuration();


    KLine& operator=(const Binance::Public::KLine &other );

    void setEventTime(qint64 newEventTime);

    void setOpenTime(qint64 newOpenTime);

    void setCloseTime(qint64 newCloseTime);
    void setOpenPrice(double newOpenPrice);
    void setHighPrice(double newHighPrice);
    void setLowPrice(double newLowPrice);
    void setClosePrice(double newClosePrice);
    void setVolume(double newVolume);
    void setAssetVolume(double newAssetVolume);
    void setNumberOfTrade(qint64 newNumberOfTrade);
    void setTakerBaseAssetVolume(double newTakerBaseAssetVolume);
    void setTakerQuotaAseetVolume(double newTakerQuotaAseetVolume);

private:

    friend QDebug operator<<(QDebug debug,const KLine &line ){
        debug << "T:"+QDateTime::fromMSecsSinceEpoch(line.closeTime()).time().toString("hh:mm:ss")
              << "O:"<<line.openPrice() << "H:"<<line.highPrice() << "L:"<<line.lowPrice() << "C:"<<line.closePrice()
              << "VOL:" << line.mVolume << "\n";
        return debug;
    }

    qint64 mEventTime;
    qint64 mOpenTime;
    qint64 mCloseTime;
    double mOpenPrice;
    double mHighPrice;
    double mLowPrice;
    double mClosePrice;

    double mVolume;
    double mAssetVolume;
    qint64 mNumberOfTrade;
    double mTakerBaseAssetVolume;
    double mTakerQuotaAseetVolume;

    bool mIs_this_kline_closed;

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





} // namespace Public
} // namespace Binance

#endif // BINANCE_PUBLIC_RESTAPI_KLINE_H
