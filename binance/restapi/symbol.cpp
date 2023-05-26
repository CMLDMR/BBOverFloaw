#include "symbol.h"

namespace Binance {
namespace Public {
namespace RestAPI {

Symbol::Symbol()
{

}

Symbol::Symbol(const QJsonObject &other)
    :QJsonObject(other)
{

}

QString Symbol::baseAsset() const
{
    return value("baseAsset").toString();
}

int Symbol::baseAssetPrecision() const
{
    return value("baseAssetPrecision").toInt();
}

QString Symbol::contractType() const
{
    return value("contractType").toString();
}

qulonglong Symbol::deliveryDate() const
{
    return value("deliveryDate").toVariant().toLongLong();
}

QString Symbol::pair() const
{
    return value("pair").toString();
}

int Symbol::pricePrecision() const
{
    return value("pricePrecision").toInt();
}

int Symbol::quantityPrecision() const
{
    return value("quantityPrecision").toInt();
}

QString Symbol::quoteAsset() const
{
    return value("quoteAsset").toString();
}

int Symbol::quotePrecision() const
{
    return value("quotePrecision").toInt();
}

QString Symbol::status() const
{
    return value("status").toString();
}

QString Symbol::symbol() const
{
    return value("symbol").toString();
}

} // namespace RestAPI
} // namespace Public
} // namespace Binance
