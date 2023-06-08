#include "pairitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QAction>
#include <QApplication>

#include "indicator/bollinger.h"
#include "global/utility.h"


namespace Graphic {

QString PairItem::pair() const
{
    return mPair;
}

Series::Series *PairItem::series() const
{
    return mSeries;
}



PairItem::PairItem(const QString &_pair, QObject *parent)
    : QObject{parent},mPair(_pair)
{
    mSeries = new Series::Series(_pair);


    QObject::connect(mSeries,&Series::Series::dataUpdated,[=](const bool &newCandle){
        this->update(boundingRect());
    });

    this->setAcceptHoverEvents(true);
}

} // namespace Graphic


QRectF Graphic::PairItem::boundingRect() const
{
    return QRectF(0,0,mWidth,mHeight);
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
        painter->drawText(70, rect.height() ,QString::number(mSeries->close()));
        painter->drawText(70, rect.height()+15 ,"BBU%");
        painter->drawText(70, rect.height()+30 ,"BBD%");
        painter->drawText(70, rect.height()+45 ,"Vol%");

    }



    {// intervals
        int xPos = 130;
        for( const auto &seri : mSeries->seriList() ){
            auto rect = fontMetric.boundingRect(QString::number(seri->close()));
            painter->drawText(xPos, rect.height() ,seri->interval());


            {// Bollinger Percent

                auto [upper,down] = Indicator::Bollinger::bollingerPercent(*seri);

                if( upper > 0 ){
                    painter->fillRect(QRectF(xPos+1,rect.height()+2,33,rect.height()),Qt::green);
                }
                if( down > 0 ){
                    painter->fillRect(QRectF(xPos+1,rect.height()+17,33,rect.height()),Qt::green);
                }
                painter->drawText(xPos, rect.height()+15 ,Global::getFixedPrecision(upper));
                painter->drawText(xPos, rect.height()+30 ,Global::getFixedPrecision(down));
            }



            painter->drawText(xPos, rect.height()+45 ,QString::number(seri->kLineContainer().size()));

            auto pen = painter->pen();
            painter->setPen(QPen(Qt::gray,1,Qt::DotLine));
            painter->drawLine(xPos-2,1,xPos-2,boundingRect().height()-2);

            painter->setPen(pen);
            xPos += 35;
        }
    }

}


void Graphic::PairItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if( event->button() == Qt::RightButton ){
        QMenu menu;


        if( mSelected ){
            menu.addAction("UnSelect",[=](){
                mSelected = false;
            });
        }else{
            menu.addAction("Select",[=](){
                mSelected = true;
            });
        }
        menu.addAction("Open Custom Url",[=](){
            emit openUrlCliked();
        });

        menu.addAction("Open in TradingView",[=](){
            emit openInTradingView();
        });

        menu.addSeparator();
        menu.addAction("Open Candle Stick",[=](){
            emit openCandles(event->screenPos());
        });

        menu.exec(event->screenPos());
    }
}


void Graphic::PairItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    QGraphicsItem::hoverEnterEvent(event);

}

void Graphic::PairItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QApplication::restoreOverrideCursor();
    QGraphicsItem::hoverLeaveEvent(event);
}
