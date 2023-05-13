#include "candlestick.h"

#include <QPainter>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>

#include "main/series.h"
#include "indicator/bollinger.h"


namespace Screen {

CandleStickItem::CandleStickItem(QObject *parent)
    : QObject{parent}
{



    this->startTimer(250);
}

void CandleStickItem::setSeries(Main::Series *newSeries)
{
    mSeries = newSeries;
}

QRectF CandleStickItem::boundingRect() const
{
    return QRectF(0.,0.,1500.,250.);
}

void CandleStickItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(boundingRect());


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

            painter->drawText(700,20,QString("xFactor %1  %2-%3=%4").arg(xFactor).arg(mMax).arg(mMin));
            painter->drawText(700,40,QString("Interval %1").arg(mSeries->timeInterval()));


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





    }


}

} // namespace Screen


void Screen::CandleStickItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{

    QGraphicsItem::hoverEnterEvent(event);
}

void Screen::CandleStickItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event);
}

void Screen::CandleStickItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
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
