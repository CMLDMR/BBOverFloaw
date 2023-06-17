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

void PairItem::setFocusIndicate(bool newFocusIndicate)
{
    mFocusIndicate = newFocusIndicate;
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
            colorGradient += 1;
            if( colorGradient >= 255 ){
                colorGradient = 0;
                mAlarmActivated = false;
            }
        }

        if( mFocusIndicate ){
            colorGradient += 5;
            if( colorGradient >= 255 ){
                colorGradient = 0;
                mFocusIndicate = false;
            }
        }

        this->update();
    });


    QTimer::singleShot(1000,[=](){
        mTimer->start(100);
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

        if( mFocusIndicate ){
            painter->fillRect(-4,-4,mSeries->image()->width()+8,mSeries->image()->height()+8,QColor(255,colorGradient,colorGradient));
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

        menu.addAction("Open Candle Stick",[=](){
            emit openCandles(event->screenPos());
        });

        menu.addSeparator();

        auto ViewMenu = menu.addMenu("View Options");
        ViewMenu->addAction("View Only Positive",[=](){
            emit viewOnlyPositive(true);
        });

        ViewMenu->addAction("View Full Values",[=](){
            emit viewOnlyPositive(false);
        });





        menu.addSeparator();


        auto sortMenuUpper = menu.addMenu("Sort Upper");

        sortMenuUpper->addAction("Sort by Abs Sum",[=](){
            emit sort("U");
        });

        sortMenuUpper->addAction("Sort by Total Sum",[=](){
            emit sort("TSU");
        });

        sortMenuUpper->addAction("Sort Green Count",[=](){
            emit sort("GUC");
        });

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

        sortMenuUpper->addAction("Sort 12H",[=](){
            emit sort("12hu");
        });

        sortMenuUpper->addAction("Sort 1D",[=](){
            emit sort("1du");
        });




        auto sortMenuDown = menu.addMenu("Sort Down");

        sortMenuDown->addAction("Sort by Abs Sum",[=](){
            emit sort("D");
        });

        sortMenuDown->addAction("Sort by Total Sum",[=](){
            emit sort("TSD");
        });

        sortMenuDown->addAction("Sort Green Count",[=](){
            emit sort("GDC");
        });
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

        sortMenuDown->addAction("Sort 12H",[=](){
            emit sort("12hd");
        });

        sortMenuDown->addAction("Sort 1D",[=](){
            emit sort("1dd");
        });


        auto sortMenuPercentAscending = menu.addMenu("Sort Percent Ascending");

        sortMenuPercentAscending->addAction("5M %",[=](){
            emit sort("5mu%");
        });

        sortMenuPercentAscending->addAction("15M %",[=](){
            emit sort("15mu%");
        });

        sortMenuPercentAscending->addAction("1H %",[=](){
            emit sort("1hu%");
        });

        sortMenuPercentAscending->addAction("4H %",[=](){
            emit sort("4hu%");
        });

        sortMenuPercentAscending->addAction("12H %",[=](){
            emit sort("12hu%");
        });

        sortMenuPercentAscending->addAction("1D %",[=](){
            emit sort("1du%");
        });

        auto sortMenuPercentDescending = menu.addMenu("Sort Percent Descending");

        sortMenuPercentDescending->addAction("5M %",[=](){
            emit sort("5md%");
        });

        sortMenuPercentDescending->addAction("15M %",[=](){
            emit sort("15md%");
        });

        sortMenuPercentDescending->addAction("1H %",[=](){
            emit sort("1hd%");
        });

        sortMenuPercentDescending->addAction("4H %",[=](){
            emit sort("4hd%");
        });

        sortMenuPercentDescending->addAction("12H %",[=](){
            emit sort("12hd%");
        });

        sortMenuPercentDescending->addAction("1D %",[=](){
            emit sort("1dd%");
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
