#include "candlestick.h"

#include <QPainter>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QMenu>
#include <QDesktopServices>

#include "indicator/bollinger.h"


namespace Screen {

CandleStickItem::CandleStickItem(QObject *parent)
    : QObject{parent}
{

    setAcceptedMouseButtons(Qt::AllButtons);

    this->setAcceptHoverEvents(true);

    this->startTimer(1000);
}


QRectF CandleStickItem::boundingRect() const
{
    return QRectF(0.,0.,900.,250.);
}

void CandleStickItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(boundingRect());

    if( mTrackMousePos ){
        auto pen = painter->pen();
        QPen tempPen;
        tempPen.setColor(Qt::gray);
        tempPen.setStyle(Qt::DotLine);
        painter->setPen(tempPen);

        painter->drawLine(mMousePoistion.x(),0,mMousePoistion.x(),boundingRect().height());
        painter->drawLine(0,mMousePoistion.y(),boundingRect().width(),mMousePoistion.y());

        tempPen.setColor(Qt::black);
        painter->setPen(tempPen);

        double mPrice =(mHighesPrice - mLowestPrice)*(boundingRect().height()-mMousePoistion.y() ) / boundingRect().height() + mLowestPrice;

        auto fontMetric = painter->fontMetrics();

        painter->drawText(boundingRect().width()-fontMetric.boundingRect(QString("%1$").arg(mPrice)).width()-2,mMousePoistion.y()-2,QString("%1$").arg(mPrice));


        painter->setPen(pen);
    }



}

} // namespace Screen


void Screen::CandleStickItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    mTrackMousePos = true;
    QApplication::setOverrideCursor(QCursor(Qt::CursorShape::CrossCursor));
    QGraphicsItem::hoverEnterEvent(event);
}

void Screen::CandleStickItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mTrackMousePos = false;
    QApplication::restoreOverrideCursor();

    QGraphicsItem::hoverLeaveEvent(event);
}


void Screen::CandleStickItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if( event->delta() > 0 ){

    }else{

    }
    QGraphicsItem::wheelEvent(event);
}


void Screen::CandleStickItem::timerEvent(QTimerEvent *event)
{
    this->update();
}


void Screen::CandleStickItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    mMousePoistion = event->pos();
    update();
    QGraphicsItem::hoverMoveEvent(event);
}



void Screen::CandleStickItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if( event->button() == Qt::RightButton ){






    }

}
