#include "pairitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QTimer>

#include "indicator/bollinger.h"
#include "global/utility.h"
#include "global/alarmwidget.h"

#include <chrono>



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

    mWidth = mSeries->image()->width()+1;

//    QObject::connect(mSeries,&Series::Series::dataUpdated,[=](const bool &newCandle){
//        this->update(boundingRect());
//    });

    this->setAcceptHoverEvents(true);


    auto mTimer = new QTimer();
    QObject::connect(mTimer,&QTimer::timeout,[=](){

        if( mAlarmActivated ){
            colorGradient += 10;
            if( colorGradient >= 255 ){
                colorGradient = 0;
                mAlarmActivated = false;
            }
        }
        this->update();
    });


    QTimer::singleShot(1000,[=](){
        mTimer->start(125);
    });

}

} // namespace Graphic


QRectF Graphic::PairItem::boundingRect() const
{
    return QRectF(0,0,mWidth,mHeight);
}

void Graphic::PairItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if( mSeries->image() ){
        if( mHovered ){
            painter->fillRect(-4,-4,mSeries->image()->width()+8,mSeries->image()->height()+8,Qt::darkGray);
        }
        painter->drawImage(0,0,*mSeries->image(),0,0,-1,-1);
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



        auto sortMenuUpper = menu.addMenu("Sort Upper");
        sortMenuUpper->addAction("Sort 5M",[=](){
            emit sort("5mu");
        });

        sortMenuUpper->addAction("Sort 15M",[=](){
            emit sort("15mu");
        });

        sortMenuUpper->addAction("Sort 1H",[=](){
            emit sort("1hu");
        });

        sortMenuUpper->addAction("Sort 4H",[=](){
            emit sort("4hu");
        });

        sortMenuUpper->addAction("Sort 1D",[=](){
            emit sort("1du");
        });

        sortMenuUpper->addAction("Sort by Sum",[=](){
            emit sort("U");
        });


        auto sortMenuDown = menu.addMenu("Sort Down");
        sortMenuDown->addAction("Sort 5M",[=](){
            emit sort("5md");
        });

        sortMenuDown->addAction("Sort 15M",[=](){
            emit sort("15md");
        });

        sortMenuDown->addAction("Sort 1H",[=](){
            emit sort("1hd");
        });

        sortMenuDown->addAction("Sort 4H",[=](){
            emit sort("4hd");
        });

        sortMenuDown->addAction("Sort 1D",[=](){
            emit sort("1dd");
        });

        sortMenuDown->addAction("Sort by Sum",[=](){
            emit sort("D");
        });

        menu.exec(event->screenPos());
    }else if(event->button() == Qt::LeftButton){
        QGraphicsItem::mousePressEvent(event);
    }
}


void Graphic::PairItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    mHovered = true;
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    QGraphicsItem::hoverEnterEvent(event);

}

void Graphic::PairItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mHovered = false;
    QApplication::restoreOverrideCursor();
    QGraphicsItem::hoverLeaveEvent(event);
}
