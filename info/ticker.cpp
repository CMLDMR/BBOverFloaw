#include "ticker.h"

namespace ExchangeInfo {

Ticker::Ticker()
{

}

Ticker::Ticker(const QJsonObject &other)
    :QJsonObject(other)
{

}

QString Ticker::getSymbol() const
{
    return value("symbol").toString();
}

double Ticker::getPrice() const
{
    return value("price").toVariant().toDouble();
}

} // namespace ExchangeInfo
