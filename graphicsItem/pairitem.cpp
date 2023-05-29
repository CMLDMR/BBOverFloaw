#include "pairitem.h"

#include <QPainter>

namespace Graphic {

PairItem::PairItem(QObject *parent)
    : QObject{parent}
{
    mSeries = new Series::Series("LINAUSDT");


    QObject::connect(mSeries,&Series::Series::dataUpdated,[=](){
        this->update();
    });




}

} // namespace Graphic


QRectF Graphic::PairItem::boundingRect() const
{
    return QRectF(0,0,1000,60);
}

void Graphic::PairItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->fillRect(boundingRect(),Qt::gray);
    painter->drawRect(boundingRect());
    auto fontMetric = painter->fontMetrics();

    {// Pair name
        auto rect = fontMetric.boundingRect(mSeries->pair());
        painter->drawText(0,rect.height() ,mSeries->pair());
    }

    {// Last Price
        auto rect = fontMetric.boundingRect(QString::number(mSeries->close()));
        painter->drawText(60, rect.height() ,QString::number(mSeries->close()));
    }

    {// intervals
        int xPos = 150;
        for( const auto &seri : mSeries->seriList() ){
            auto rect = fontMetric.boundingRect(seri->kLineContainer().constLast().closePrice());
            painter->drawText(xPos, rect.height() ,seri->interval());
            painter->drawText(xPos, rect.height()+15 ,seri->kLineContainer().last().openPrice());
            painter->drawText(xPos, rect.height()+30 ,seri->kLineContainer().last().closePrice());

            xPos += rect.width()+10;
        }
    }

}
