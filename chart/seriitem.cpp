#include "seriitem.h"

#include "series/seri.h"


#include <QPainter>


namespace Chart {

SeriItem::SeriItem(Series::Seri *_seri, QObject *parent)
    : QObject{parent},
    mSeri(_seri)
{

    QObject::connect(mSeri,&Series::Seri::updated,[=](){
        this->update();
    });


}

std::tuple<QRectF, QLineF, Qt::GlobalColor> SeriItem::candle(const int &index) const
{
    auto min = mSeri->minPrice();
    auto max = mSeri->maxPrice();

    auto close = mSeri->close(index);
    auto open = mSeri->open(index);
    auto high = mSeri->high(index);
    auto low = mSeri->low(index);

    if( close > open ){

        qreal xPos = index * tickerAreaWidth+2;
        qreal yPos = mHeight - (open - min)/(max-min)*mHeight;
        qreal width = tickerAreaWidth-2;
        qreal height = (open -close)/(max-min)*mHeight;

        qreal _high = (high  - min)/(max-min)*mHeight;
        qreal _low = (low  - min)/(max-min)*mHeight;

        return std::make_tuple(QRectF(xPos,yPos,width,height),QLineF(xPos+tickerAreaWidth/2-1,mHeight-_high,xPos+tickerAreaWidth/2-1,mHeight-_low),Qt::green);
    }else{
        qreal xPos = index * tickerAreaWidth+2;
        qreal yPos = mHeight - (close - min)/(max-min)*mHeight;
        qreal width = tickerAreaWidth-2;
        qreal height = (close - open)/(max-min)*mHeight;

        qreal _high = (high  - min)/(max-min)*mHeight;
        qreal _low = (low  - min)/(max-min)*mHeight;

        return std::make_tuple(QRectF(xPos,yPos,width,height),QLineF(xPos+tickerAreaWidth/2-1,mHeight-_high,xPos+tickerAreaWidth/2-1,mHeight-_low),Qt::red);
    }




}

} // namespace Chart


QRectF Chart::SeriItem::boundingRect() const
{
    return QRectF(0,0,mWidth,mHeight);
}

void Chart::SeriItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawRect(boundingRect());

    mWidth = mSeri->size() * tickerAreaWidth +20;
    for( int i = 0 ; i < mSeri->size() ; i++ ){
        auto [rect,line,color] = candle(i);
        painter->fillRect(rect,color);
        painter->drawText(rect,QString::number(i));
        auto pen = painter->pen();
        painter->setPen(QPen(color));
        painter->drawLine(line);
        painter->setPen(pen);
    }


    painter->setPen(QPen(Qt::green));
    painter->drawLine(0,mSeri->maxPrice(),mWidth,mSeri->maxPrice());

    painter->setPen(QPen(Qt::red));
    painter->drawLine(0,mSeri->minPrice(),mWidth,mSeri->minPrice());
}
