#include "tradeitem.h"
#include <QDateTime>
#include <QVariant>
#include <QJsonArray>
#include <QJsonValue>

namespace Main {

TradeItem::TradeItem()
{

}


TradeItem::TradeItem(const QJsonObject &other)
    :QJsonObject(other)
{
    //    *this = other;
}

QString TradeItem::priceStr() const
{
    return value("p").toString();
}

double TradeItem::price() const
{
    return value("p").toVariant().toDouble();
}

QString TradeItem::qtyStr() const
{
    return value("q").toString();
}

double TradeItem::qty() const
{
    return value("q").toVariant().toDouble();
}

bool TradeItem::isSell() const
{
    return value("m").toBool();
}


QString TradeItem::volDollarStr() const
{
    return QString("%1").arg(volDollar(),0,'f',0);
}

double TradeItem::volDollar() const
{
    return value("q").toVariant().toDouble()*value("p").toVariant().toDouble();

}

QString TradeItem::timeStr() const
{
    return QDateTime::fromMSecsSinceEpoch(value("T").toVariant().toLongLong()).toString("hh:mm:ss");

}

} // namespace Main
