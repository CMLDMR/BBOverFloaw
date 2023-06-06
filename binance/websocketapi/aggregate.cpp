#include "aggregate.h"

namespace Binance {
namespace Public {
namespace WebSocketAPI {

Aggregate::Aggregate()
{

}

Aggregate::Aggregate(const QJsonObject &other)
    :QJsonObject(other)
{

}

qint64 Aggregate::eventTime() const
{
    return value("E").toVariant().toLongLong();
}

double Aggregate::price() const
{
    return value("p").toVariant().toDouble();
}

double Aggregate::quantity() const
{
    return value("q").toVariant().toDouble();
}

qint64 Aggregate::tradeTime() const
{
    return value("T").toVariant().toLongLong();
}

bool Aggregate::isMaker() const
{
    return value("m").toBool();
}

} // namespace WebSocketAPI
} // namespace Public
} // namespace Binance
