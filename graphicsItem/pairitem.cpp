#include "pairitem.h"

#include <QPainter>

namespace Graphic {

PairItem::PairItem(QObject *parent)
    : QObject{parent}
{
    mSeries = new Series::Series("BTCUSDT");


    QObject::connect(mSeries,&Series::Series::dataUpdated,[=](){
        this->update();
    });




}

} // namespace Graphic


QRectF Graphic::PairItem::boundingRect() const
{
    return QRectF(0,0,1000,40);
}

void Graphic::PairItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),Qt::gray);
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

    /// TODO: Price Does not Seen
    qDebug() << "Seri Size: " << mSeries->seriList().size();
    {// intervals
        int xPos = 100;
        for( const auto &seri : mSeries->seriList() ){
            qDebug() << xPos << seri->kLineContainer().last().closePrice();
            auto rect = fontMetric.boundingRect(seri->kLineContainer().constLast().closePrice());
            painter->drawText(xPos*rect.width(), rect.height() ,seri->kLineContainer().constLast().closePrice()+"00xx");
            xPos += rect.width()+10;
        }
    }

}
