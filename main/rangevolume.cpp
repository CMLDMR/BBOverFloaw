#include "rangevolume.h"

#include <QPainter>

namespace Main {

RangeVolume::RangeVolume()
{

}

void RangeVolume::addTicker(const TradeItem &item, const double &average)
{
    //    auto key = static_cast<int>(item.price())/10*10;//BTC


    auto key = static_cast<int>(item.price()*100)/100;

    mLastAverage = mLastAverage < average ? average : mLastAverage;
    mLastKey = key;
    mTradeList[key] += item;
    this->update();
}

RangeItem::RangeItem()
{

}

RangeItem &RangeItem::operator+=(const TradeItem &item)
{

    this->mLastIsBuy = !item.isSell();
    if( item.isSell() ){
        this->mSell += item.volDollar();
    }else{
        this->mBuy += item.volDollar();
    }
    this->mLastQty = item.volDollar();
    return *this;
}

double RangeItem::buy() const
{
    return mBuy;
}

double RangeItem::sell() const
{
    return mSell;
}

bool RangeItem::lastIsBuy() const
{
    return mLastIsBuy;
}

double RangeItem::lastQty() const
{
    return mLastQty;
}

} // namespace Main


QRectF Main::RangeVolume::boundingRect() const
{
    return QRectF(0,0,500,750);
}

void Main::RangeVolume::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(boundingRect());
    auto pen = painter->pen();

    QPen gridPen;
    gridPen.setStyle(Qt::PenStyle::DotLine);
    gridPen.setColor(QColor(150,150,150));
    painter->setPen(gridPen);
    painter->drawText(0,12,"0$");

    for( double i = 1 ; i < 7 ; i++ ){
        painter->drawLine((boundingRect().width()-0)/7*i,0,(boundingRect().width()-0)/7*i,boundingRect().height());
        if( static_cast<int>(i) % 2 == 1 ){
            painter->drawText((boundingRect().width()-0)/7*i,12,QString("%1").arg(static_cast<int>(mTotalSell+mTotalBuy)/7*i/**mLastAverage*/)+"$");
        }
    }



    painter->setPen(pen);


    auto yOffset = 50.;
    auto height = 2;

    mTotalSell = 0;
    mTotalBuy = 0;

    auto keyList = mTradeList.keys();
    int i = 0;
    QMapIterator<double,RangeItem> SellIt(mTradeList);
    while (SellIt.hasNext()) {
        SellIt.next();



        if( std::abs(keyList.indexOf(mLastKey) - i) > 100 ){

        }else{

            auto row = /*std::abs*/(keyList.indexOf(mLastKey) - i)+110;


            if( SellIt.value().lastIsBuy() ){
                painter->fillRect(QRectF(0,row*height+1+yOffset,boundingRect().width(),height),QColor(235,235,235,25));


                if( SellIt.key() == mLastKey ){
                    painter->fillRect(QRectF(0,row*height+1+yOffset,boundingRect().width(),height),QColor(225,225,225,125));

                    painter->fillRect(QRectF(boundingRect().width()-SellIt.value().lastQty()/mLastAverage*10,row*height+1+yOffset,SellIt.value().lastQty()/mLastAverage*10,height),QColor(125,255,125));
                }
            }else{
                if( SellIt.key() == mLastKey ){
                    painter->fillRect(QRectF(0,row*height+1+yOffset,boundingRect().width(),height),QColor(225,225,225,125));

                    painter->fillRect(QRectF(boundingRect().width()-SellIt.value().lastQty()/mLastAverage*10,row*height+1+yOffset,SellIt.value().lastQty()/mLastAverage*10,height),QColor(255,125,125));
                }
            }

            while( SellIt.value().sell()/mLastAverage > boundingRect().width()-100 ){
                mLastAverage +=100;
            }

            while( SellIt.value().buy()/mLastAverage > boundingRect().width()-100 ){
                mLastAverage +=100;
            }

            auto width = std::abs(SellIt.value().buy()-SellIt.value().sell())/mLastAverage;

            if( SellIt.value().sell() > SellIt.value().buy() ){
                mTotalSell += width;
                painter->fillRect(QRectF(0,row*height+1+yOffset,width,height),QColor(255,50,50));
            }else{
                painter->fillRect(QRectF(0,row*height+1+yOffset,width,height),QColor(50,255,50));
                mTotalBuy += width;
            }

            if( row%15 == 0 ){
                painter->setFont(QFont("Tahoma",10));
                auto fontMetric = painter->fontMetrics();
                painter->setPen(gridPen);

                painter->drawLine(0,row*height+height-2+yOffset,500,row*height+height-2+yOffset);
                painter->setPen(pen);

                painter->drawText(boundingRect().width()-fontMetric.boundingRect(QString::number(SellIt.key())).width(),row*height+height-2+yOffset,QString::number(SellIt.key()));
            }
        }






        i++;
    }



    painter->fillRect(QRectF(0,15,mTotalBuy/(mTotalBuy+mTotalSell)*boundingRect().width(),20),QColor(125,255,125));
    painter->fillRect(QRectF(boundingRect().width()-mTotalSell/(mTotalBuy+mTotalSell)*boundingRect().width(),15,mTotalSell/(mTotalBuy+mTotalSell)*boundingRect().width(),20),QColor(255,125,125));




}
