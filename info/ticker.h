#ifndef EXCHANGEINFO_TICKER_H
#define EXCHANGEINFO_TICKER_H

#include <QJsonObject>

namespace ExchangeInfo {

class Ticker : public QJsonObject
{
public:
    Ticker();
    Ticker( const QJsonObject &other );

    QString getSymbol() const;
    double getPrice() const;
};

} // namespace ExchangeInfo

#endif // EXCHANGEINFO_TICKER_H
