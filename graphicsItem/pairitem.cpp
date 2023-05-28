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
    return QRectF(0,0,500,1000);
}

void Graphic::PairItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(boundingRect(),Qt::green);

    if( mSeries->seriList().size() ){

        int i = 0;
        for( const auto &seri : mSeries->seriList() ){
            painter->drawText(0, i*20+20 ,seri->interval() + " : " + seri->kLineContainer().last().closePrice());
            i++;
        }
    }



}
