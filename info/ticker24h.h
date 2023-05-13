#ifndef EXCHANGEINFO_TICKER24H_H
#define EXCHANGEINFO_TICKER24H_H

#include <QJsonObject>

namespace ExchangeInfo {

class Ticker24H : public QJsonObject
{
public:
    Ticker24H();
    Ticker24H( const QJsonObject &other );

    QString symbol() const;
    double priceChange() const;
    double priceChangePercent() const;
    double weightedAvgPrice() const;
    double lastPrice() const;
    double lastQty() const;
    double openPrice() const;
    double highPrice() const;
    double lowPrice() const;
    double volume() const;
    double quoteVolume() const;

    qulonglong openTime() const;
    qulonglong closeTime() const;
    qulonglong firstId() const;
    qulonglong lastId() const;
    qulonglong count() const;

};

} // namespace ExchangeInfo

#endif // EXCHANGEINFO_TICKER24H_H
