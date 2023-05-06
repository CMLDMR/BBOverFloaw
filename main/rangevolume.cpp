#include "rangevolume.h"

#include <QPainter>

namespace Main {

RangeVolume::RangeVolume()
{

}

void RangeVolume::addTicker(const TradeItem &item)
{

}

} // namespace Main


QRectF Main::RangeVolume::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void Main::RangeVolume::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(boundingRect());
}
