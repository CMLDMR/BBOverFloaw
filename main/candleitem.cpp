#include "candleitem.h"

namespace Main {

CandleItem::CandleItem(const QJsonArray &other)
    :QJsonArray(other)
{

}

qulonglong CandleItem::openTime() const
{
    return this->at(0).toVariant().toULongLong();
}

QString CandleItem::openStr() const
{
    return this->at(1).toString();
}

double CandleItem::open() const
{
    return openStr().toDouble();
}

QString CandleItem::highStr() const
{
    return this->at(2).toString();
}

double CandleItem::high() const
{
    return this->highStr().toDouble();
}

QString CandleItem::lowStr() const
{
    return this->at(3).toString();
}

double CandleItem::low() const
{
    return this->lowStr().toDouble();
}

QString CandleItem::closeStr() const
{
    return this->at(4).toString();
}

double CandleItem::close() const
{
    return this->closeStr().toDouble();
}

QString CandleItem::volumeStr() const
{
    return this->at(5).toString();
}

QString CandleItem::assetVolume() const
{
    return this->at(7).toString();
}

qulonglong CandleItem::closeTimeLong() const
{
    return this->at(6).toVariant().toULongLong();
}

QTime CandleItem::closeTime() const
{
    return QDateTime::fromMSecsSinceEpoch(this->closeTimeLong()).time();
}

qulonglong CandleItem::numberOfTrade() const
{
    return this->at(8).toVariant().toULongLong();
}

QString CandleItem::buyVolumeStr() const
{
    return this->at(9).toString();
}

QString CandleItem::buyAssetVolumeStr() const
{
    return this->at(10).toString();
}


} // namespace Main
