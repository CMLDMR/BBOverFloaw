#ifndef MAIN_CANDLEITEM_H
#define MAIN_CANDLEITEM_H

#include <QJsonArray>

namespace Main {

class CandleItem : public QJsonArray
{
public:
    CandleItem(){};
    CandleItem( const QJsonArray &other );

    qulonglong openTime() const;
    QString openStr() const;
    double open() const;
    QString highStr() const;
    double high() const;
    QString lowStr() const;
    double low() const;
    QString closeStr() const;
    double close() const;
    QString volumeStr() const;
    QString assetVolume() const;

    qulonglong closeTimeLong() const;
    QTime closeTime() const;
    qulonglong numberOfTrade() const;
    QString buyVolumeStr() const;
    QString buyAssetVolumeStr() const;

    void setOpenTime( const qulonglong &time );



    /// GET Method RESPONSE
    //    1607444700000,          // 0 Open time
    //    "18879.99",             // 1 Open
    //    "18900.00",             // 2 High
    //    "18878.98",             // 3 Low
    //    "18896.13",             // 4 Close (or latest price)
    //    "492.363",              // 5 Volume
    //    1607444759999,          // 6 Close time
    //    "9302145.66080",        // 7 Quote asset volume
    //    1874,                   // 8 Number of trades
    //    "385.983",              // 9 Taker buy volume
    //    "7292402.33267",        // 10 Taker buy quote asset volume
    //    "0"                     // 11 Ignore.


    /// WEBSOCKET Response
    //{
    //"e": "kline",         // Event type
    //"E": 1672515782136,   // Event time
    //"s": "BNBBTC",        // Symbol
    //"k": {
    //    "t": 1672515780000, // Kline start time
    //    "T": 1672515839999, // Kline close time
    //    "s": "BNBBTC",      // Symbol
    //    "i": "1m",          // Interval
    //    "f": 100,           // First trade ID
    //    "L": 200,           // Last trade ID
    //    "o": "0.0010",      // Open price
    //    "c": "0.0020",      // Close price
    //    "h": "0.0025",      // High price
    //    "l": "0.0015",      // Low price
    //    "v": "1000",        // Base asset volume
    //    "n": 100,           // Number of trades
    //    "x": false,         // Is this kline closed?
    //    "q": "1.0000",      // Quote asset volume
    //    "V": "500",         // Taker buy base asset volume
    //    "Q": "0.500",       // Taker buy quote asset volume
    //    "B": "123456"       // Ignore
    //}
    //}

};

} // namespace Main

#endif // MAIN_CANDLEITEM_H
