#include "ticker24h.h"

namespace ExchangeInfo {

Ticker24H::Ticker24H()
{

}

Ticker24H::Ticker24H(const QJsonObject &other)
    :QJsonObject(other)
{

}

QString Ticker24H::symbol() const
{
    return value("symbol").toString();
}

double Ticker24H::priceChange() const
{
    return value("priceChange").toString().toDouble();
}

double Ticker24H::priceChangePercent() const
{
    return value("priceChangePercent").toString().toDouble();
}

double Ticker24H::lastPrice() const
{
    return value("lastPrice").toString().toDouble();
}

} // namespace ExchangeInfo
