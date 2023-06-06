#include "pairitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QAction>
#include <QApplication>


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
        this->update();
    });

    this->setAcceptHoverEvents(true);



}

} // namespace Graphic


QRectF Graphic::PairItem::boundingRect() const
{
    return QRectF(0,0,1000,100);
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
            auto rect = fontMetric.boundingRect(QString::number(seri->close()));
            painter->drawText(xPos, rect.height() ,seri->interval());
            painter->drawText(xPos, rect.height()+15 ,QString::number(seri->open()));
            painter->drawText(xPos, rect.height()+30 ,QString::number(seri->high()));
            painter->drawText(xPos, rect.height()+45 ,QString::number(seri->low()));
            painter->drawText(xPos, rect.height()+60 ,QString::number(seri->close()));
            painter->drawText(xPos, rect.height()+75 ,QString::number(seri->kLineContainer().size()));

            xPos += 50;
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
