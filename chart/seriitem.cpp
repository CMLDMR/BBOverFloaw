#include "seriitem.h"

#include "series/seri.h"


#include <QGraphicsScene>
#include <QPainter>


namespace Chart {

SeriItem::SeriItem(Series::Seri *_seri, QObject *parent)
    : QObject{parent},
    mSeri(_seri)
{

    QObject::connect(mSeri,&Series::Seri::updated,[=](){
        this->update();
        this->scene()->update(this->scene()->itemsBoundingRect());
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

    if( close >= open ){

        qreal xPos = index * tickerAreaWidth+2;
        qreal yPos = mInfoHeight+mHeight - (open - min)/(max-min)*mHeight;
        qreal width = tickerAreaWidth-2;
        qreal height = (open -close)/(max-min)*mHeight;

        qreal _high = mInfoHeight+mHeight-(high  - min)/(max-min)*mHeight;
        qreal _low = mInfoHeight+mHeight-(low  - min)/(max-min)*mHeight;

        return std::make_tuple(QRectF(xPos,yPos,width,height),QLineF(xPos+tickerAreaWidth/2-1,_high,xPos+tickerAreaWidth/2-1,_low),Qt::green);
    }else{
        qreal xPos = index * tickerAreaWidth+2;
        qreal yPos = mInfoHeight+mHeight - (close - min)/(max-min)*mHeight;
        qreal width = tickerAreaWidth-2;
        qreal height = (close - open)/(max-min)*mHeight;

        qreal _high = mInfoHeight+mHeight-(high  - min)/(max-min)*mHeight;
        qreal _low = mInfoHeight+mHeight-(low  - min)/(max-min)*mHeight;

        return std::make_tuple(QRectF(xPos,yPos,width,height),QLineF(xPos+tickerAreaWidth/2-1,_high,xPos+tickerAreaWidth/2-1,_low),Qt::red);
    }




}

std::tuple<QRectF,QRectF,QRectF, Qt::GlobalColor> SeriItem::volume(const int &index) const
{

    qreal max = mSeri->at(0).volume();
    for( int i = 0 ; i < mSeri->size() ; i++ ){
        auto item = mSeri->at(i);
        if( item.volume() > max ) max = item.volume();
    }

    auto close = mSeri->close(index);
    auto open = mSeri->open(index);


    auto _volumeYAx = mInfoHeight+mHeight+mVolumeHeight;

    qreal xPos = index * tickerAreaWidth+1;
    qreal yPos = _volumeYAx - (mSeri->volume(index))/max*mVolumeHeight;
    qreal width = tickerAreaWidth-1;
    qreal height = mSeri->volume(index)/max*mVolumeHeight;

    Qt::GlobalColor color = close >= open ? Qt::darkGreen : Qt::darkRed;

    qreal bYpos = _volumeYAx - mSeri->takerVolume(index)/max*mVolumeHeight;
    qreal bheight = mSeri->takerVolume(index)/max*mVolumeHeight;

    qreal sYpos = _volumeYAx - (mSeri->volume(index)-mSeri->takerVolume(index))/max*mVolumeHeight;
    qreal sheight = height-bheight;

    return std::make_tuple(QRectF(xPos,yPos,width,height),
                           QRectF(xPos,bYpos,width/2,bheight),
                           QRectF(xPos+width/2,sYpos,width/2,sheight)
                           ,color);


}

QPointF SeriItem::volumeDif(const int &index)
{
    qreal max = mSeri->at(0).volume();

    return QPointF();
}



} // namespace Chart


QRectF Chart::SeriItem::boundingRect() const
{
    return QRectF(0,0,mWidth,mHeight+mInfoHeight+mVolumeHeight+mQuotaVolumeHeight);
}

void Chart::SeriItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawRect(boundingRect());
    painter->fillRect(QRectF(0,0,mWidth,mInfoHeight),Qt::gray);
    painter->drawText(0,15,mSeri->pair() + " " + mSeri->interval() + " O:"+QString("%1 H:%2 L:%3 C:%4").arg(mSeri->open()).arg(mSeri->high()).arg(mSeri->low()).arg(mSeri->close()));

    mWidth = mSeri->size() * tickerAreaWidth +100;
    for( int i = 0 ; i < mSeri->size() ; i++ ){
        auto [rect,line,color] = candle(i);
        painter->fillRect(rect,color);
        painter->drawText(rect,QString::number(i));
        auto pen = painter->pen();
        painter->setPen(QPen(color));
        painter->drawLine(line);
        painter->setPen(pen);
    }

    {
        auto min = mSeri->minPrice();
        auto max = mSeri->maxPrice();
        auto close = mSeri->close();
        painter->drawText(mSeri->size() * tickerAreaWidth+20,mInfoHeight+mHeight - (close - min)/(max-min)*mHeight,QString::number(mSeri->close()));
        painter->drawText(mSeri->size() * tickerAreaWidth+20,mInfoHeight+mHeight - (close - min)/(max-min)*mHeight+20,QString::number(60-(mSeri->last().eventTime()%60000)/1000));
    }

    {
        painter->fillRect(QRectF(0,mInfoHeight+mHeight,mWidth,mVolumeHeight),QColor(220,220,220));
        painter->drawText(0,mInfoHeight+mHeight+14,"Volume Base: " + QString::number(mSeri->volume()));

        for( int i = 0 ; i < mSeri->size() ; i++ ){
            auto [rect,rectbuy,rectsell,color] = this->volume(i);
            painter->fillRect(rect,color);
            painter->fillRect(rectbuy,Qt::green);
            painter->fillRect(rectsell,Qt::red);
        }
    }

//    {
//        painter->fillRect(QRectF(0,mInfoHeight+mHeight,mWidth,mVolumeHeight),Qt::GlobalColor::lightGray);
//        painter->drawText(0,mInfoHeight+mHeight+20,"VOLUME");

//        for( int i = 1 ; i < mSeri->size() ; i++ ){

//        }
//    }


}
