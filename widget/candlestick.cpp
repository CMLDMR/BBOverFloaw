#include "candlestick.h"

#include <QPainter>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>

#include "main/series.h"
#include "indicator/bollinger.h"


namespace Screen {

CandleStickItem::CandleStickItem(QObject *parent)
    : QObject{parent}
{

    setAcceptedMouseButtons(Qt::AllButtons);

    this->setAcceptHoverEvents(true);

    this->startTimer(1000);
}

void CandleStickItem::setSeries(Main::Series *newSeries)
{
    mSeries = newSeries;
}

QRectF CandleStickItem::boundingRect() const
{
    return QRectF(0.,0.,700.,250.);
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

        painter->setPen(pen);
    }

    if( mSeries ){

        if( mSeries->getSeries().size() ){
            double mMax{0},mMin{99999999};

            int index = 0;
            for( const auto &item : mSeries->getSeries() ){
                mMax = mMax < item.high() ? item.high() : mMax;
                mMin = mMin > item.low() ? item.low() : mMin;

                const auto &[upper,mid,lower] = mSeries->bollinger()->getBollinger(index++);

                if( upper != 0 ){
                    mMax = upper > mMax ? upper : mMax;
                    mMin = lower < mMin ? lower : mMin;
                }
            }

            painter->setBrush(QBrush(Qt::green));

            auto xFactor = boundingRect().height() / ( mMax - mMin);

            // Draw Candle Stick
            for( int i = 0 ; i < mSeries->getSeries().size() ; i++ ){

                const auto &item = mSeries->getSeries()[i];

                auto open = item.open();
                auto high = item.high();
                auto low  = item.low();
                auto close = item.close();

                auto RectHeight = boundingRect().height();

                if( item.close() > item.open() ){

                    painter->setBrush(QBrush(Qt::green));

                    auto xPos = i*13.0;
                    auto yPos = (open-mMin)*xFactor;

                    auto width = 7.;
                    auto height = (close-open)*xFactor;

                    {
                        auto wickyPos = (low-mMin)*xFactor;
                        auto wickHeight = (high-low)*xFactor;

                        QLineF wick(xPos+4,RectHeight-wickyPos-wickHeight,xPos+4,RectHeight-wickyPos);
                        painter->drawLine(wick);
                    }

                    QRectF body(xPos,RectHeight-yPos-height,width,height);

                    painter->drawRect(body);

                }else{

                    painter->setBrush(QBrush(Qt::red));

                    auto xPos = i*13.0;
                    auto yPos = (open-mMin)*xFactor;

                    auto width = 7.;
                    auto height = std::abs(close-open)*xFactor;

                    {
                        auto wickyPos = (low-mMin)*xFactor;
                        auto wickHeight = (high-low)*xFactor;

                        QLineF wick(xPos+4,RectHeight-wickyPos-wickHeight,xPos+4,RectHeight-wickyPos);
                        painter->drawLine(wick);
                    }

                    QRectF body(xPos,RectHeight-yPos,width,height);

                    painter->drawRect(body);

                }
            }

            //Draw Bollinger

            double lastUpper = 0;
            double lastmid = 0;
            double lastlower = 0;

            auto RectHeight = boundingRect().height();

            for( int i = 0 ; i < mSeries->getSeries().size() ; i++ ){

                const auto &[upper,mid,lower] = mSeries->bollinger()->getBollinger(i);

                if( upper == 0 ) continue;

                if( lastUpper == 0 ) lastUpper = upper;
                if( lastmid == 0 ) lastmid = mid;
                if( lastlower == 0 ) lastlower = lower;

                auto xPos = (i-1)*13.0;

                {
                    auto wickyPos = (upper-mMin)*xFactor;
                    auto wickHeight = (lastUpper-mMin)*xFactor;

                    QLineF wick(xPos+4,RectHeight-wickHeight,xPos+4+13,RectHeight-wickyPos);
                    painter->drawLine(wick);

                    lastUpper = upper;
                }

                xPos = (i-1)*13.0;
                {
                    auto wickyPos = (mid-mMin)*xFactor;
                    auto wickHeight = (lastmid-mMin)*xFactor;

                    QLineF wick(xPos+4,RectHeight-wickHeight,xPos+4+13,RectHeight-wickyPos);
                    painter->drawLine(wick);

                    lastmid = mid;
                }

                xPos = (i-1)*13.0;
                {
                    auto wickyPos = (lower-mMin)*xFactor;
                    auto wickHeight = (lastlower-mMin)*xFactor;

                    QLineF wick(xPos+4,RectHeight-wickHeight,xPos+4+13,RectHeight-wickyPos);
                    painter->drawLine(wick);

                    lastlower = lower;
                }
            }
        }

        auto font = painter->font();
        painter->setFont(QFont("Tahoma",16));
        painter->drawText(0,20,QString("Interval %1").arg(mSeries->timeInterval()));
        painter->setFont(font);
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

