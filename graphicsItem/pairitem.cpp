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

    // QObject::connect(mSeries,&Series::Series::alarmed,[=](const QString &alarmMsg){
    //     QTimer::singleShot(0,[=](){
    //         Global::Alarm::AlarmWidget::instance()->popUpMessage(alarmMsg);
    //         // Global::Alarm::AlarmWidget::instance().
    //     });
    //     // Global::Alarm::AlarmWidget::instance()->popUpMessage(alarmMsg);
    // });

    this->setAcceptHoverEvents(true);


    auto mTimer = new QTimer(this);
    QObject::connect(mTimer,&QTimer::timeout,[=, this](){

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
        // Global::Alarm::AlarmWidget::instance()->popUpMessage("Added");

        mTimer->start(100);
    });

}

} // namespace Graphic


QRectF Graphic::PairItem::boundingRect() const
{
    return QRectF(0,0,mSeries->image()->width(),mSeries->image()->height() );
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

        menu.setWindowTitle("Menu");

        // menu.addAction("UnSelect",this,[=, this](){
        //     mSelected = false;
        // });


        if( mSelected ){
            menu.addAction("UnSelect",this,[=, this](){
                mSelected = false;
            });
        }else{
            menu.addAction("Select",[=, this](){
                mSelected = true;
            });
        }
        menu.addAction("Open Custom Url",[=, this](){
            emit openUrlCliked();
        });

        menu.addAction("Open in TradingView",[=, this](){
            emit openInTradingView();
        });

        menu.addAction("Open Candle Stick",[=, this](){
            emit openCandles(event->screenPos());
        });

        menu.addAction("Open Volume Graph",[=, this](){
            emit openVolumeGraph();
        });

        menu.addAction("Open Volume Percent Graph",[=, this](){
            emit openVolumePercent();
        });

        menu.addAction("Open OrderBook",[=, this](){
            emit openOrderTimeLineBook();
        });

        menu.addSeparator();

        auto ViewMenu = menu.addMenu("View Options");
        ViewMenu->addAction("View Only Positive",[=, this](){
            emit viewOnlyPositive(true);
        });

        ViewMenu->addAction("View Full Values",[=, this](){
            emit viewOnlyPositive(false);
        });





        menu.addSeparator();

        auto sortMenuBar = menu.addMenu("Sort By Bars");

        sortMenuBar->addAction("Full Green",[=, this](){
            emit sort("fullgreen");
        });

        sortMenuBar->addAction("Full Red",[=, this](){
            emit sort("fullred");
        });

        sortMenuBar->addAction("Full Bar Percent Ascending",[=, this](){
            emit sort("fullbarpercentA");
        });
        sortMenuBar->addAction("Full Bar Percent Descending",[=, this](){
            emit sort("fullbarpercentD");
        });


        auto sortMenuUpper = menu.addMenu("Sort Upper");

        auto autoSortMenuUpper = sortMenuUpper->addMenu("Auto ");

        createAction( autoSortMenuUpper , "Sort 1M","1mu");
        createAction( autoSortMenuUpper , "Sort 5M","5mu");


        sortMenuUpper->addAction("Sort by Abs Sum",[=, this](){
            emit sort("U");
        });

        sortMenuUpper->addAction("Sort by Total Sum",[=, this](){
            emit sort("TSU");
        });

        sortMenuUpper->addAction("Sort Green Count",[=, this](){
            emit sort("GUC");
        });

        sortMenuUpper->addAction("Sort 1M",[=, this](){
            emit autoSort( false , "1mu" );
        });

        sortMenuUpper->addAction("Sort 5M",[=, this](){
            emit autoSort( false , "5mu" );
        });

        sortMenuUpper->addAction("Sort 15M",[=, this](){
            emit sort("15mu");
        });

        sortMenuUpper->addAction("Sort 1H",[=, this](){
            emit sort("1hu");
        });

        sortMenuUpper->addAction("Sort 4H",[=, this](){
            emit sort("4hu");
        });

        sortMenuUpper->addAction("Sort 12H",[=, this](){
            emit sort("12hu");
        });

        sortMenuUpper->addAction("Sort 1D",[=, this](){
            emit sort("1du");
        });




        auto sortMenuDown = menu.addMenu("Sort Down");


        // Enable Disable Alarm Menu
        auto alarmMenuDown = menu.addMenu("BB Alarm");

        for( int i = 0 ; i < this->series()->seriList().size() ; i++ ) {
            auto seriItem = this->series()->seriList()[i];


            if( seriItem->interval() == "1m" ) {
                alarmMenuDown->addAction( QString("%1 %2 Alarm").arg( seriItem->interval() ).arg( this->series()->enableBBD1minuteAlarm() ? "Disable" : "Enable"),[=, this](){
                    this->series()->setEnableBBD1minuteAlarm( ! this->series()->enableBBD1minuteAlarm() );
                });
            }

            if( seriItem->interval() == "5m" ) {
                alarmMenuDown->addAction( QString("%1 %2 Alarm").arg( seriItem->interval() ).arg( this->series()->enableBBD5minuteAlarm() ? "Disable" : "Enable"),[=, this](){
                    this->series()->setEnableBBD5minuteAlarm( ! this->series()->enableBBD5minuteAlarm() );
                });
            }

            if( seriItem->interval() == "15m" ) {
                alarmMenuDown->addAction( QString("%1 %2 Alarm").arg( seriItem->interval() ).arg( this->series()->enableBBD15minuteAlarm() ? "Disable" : "Enable"),[=, this](){
                    this->series()->setEnableBBD15minuteAlarm( ! this->series()->enableBBD15minuteAlarm() );
                });
            }

            if( seriItem->interval() == "1h" ) {
                alarmMenuDown->addAction( QString("%1 %2 Alarm").arg( seriItem->interval() ).arg( this->series()->enableBBD1hourAlarm() ? "Disable" : "Enable"),[=, this](){
                    this->series()->setEnableBBD1hourAlarm( ! this->series()->enableBBD1hourAlarm() );
                });
            }

            if( seriItem->interval() == "4h" ) {
                alarmMenuDown->addAction( QString("%1 %2 Alarm").arg( seriItem->interval() ).arg( this->series()->enableBBD4hourAlarm() ? "Disable" : "Enable"),[=, this](){
                    this->series()->setEnableBBD4hourAlarm( ! this->series()->enableBBD4hourAlarm() );
                });
            }

            if( seriItem->interval() == "1d" ) {
                alarmMenuDown->addAction( QString("%1 %2 Alarm").arg( seriItem->interval() ).arg( this->series()->enableBBD1dayAlarm() ? "Disable" : "Enable"),[=, this](){
                    this->series()->setEnableBBD1dayAlarm( ! this->series()->enableBBD1dayAlarm() );
                });
            }
        }



        sortMenuDown->addAction("Sort by Abs Sum",[=, this](){
            emit sort("D");
        });

        sortMenuDown->addAction("Sort by Total Sum",[=, this](){
            emit sort("TSD");
        });

        sortMenuDown->addAction("Sort Green Count",[=, this](){
            emit sort("GDC");
        });
        sortMenuDown->addAction("Sort 5M",[=, this](){
            emit sort("5md");
        });

        sortMenuDown->addAction("Sort 15M",[=, this](){
            emit sort("15md");
        });

        sortMenuDown->addAction("Sort 1H",[=, this](){
            emit sort("1hd");
        });

        sortMenuDown->addAction("Sort 4H",[=, this](){
            emit sort("4hd");
        });

        sortMenuDown->addAction("Sort 12H",[=, this](){
            emit sort("12hd");
        });

        sortMenuDown->addAction("Sort 1D",[=, this](){
            emit sort("1dd");
        });


        auto sortMenuPercentAscending = menu.addMenu("Sort Percent Ascending");

        sortMenuPercentAscending->addAction("5M %",[=, this](){
            emit sort("5mu%");
        });

        sortMenuPercentAscending->addAction("15M %",[=, this](){
            emit sort("15mu%");
        });

        sortMenuPercentAscending->addAction("1H %",[=, this](){
            emit sort("1hu%");
        });

        sortMenuPercentAscending->addAction("4H %",[=, this](){
            emit sort("4hu%");
        });

        sortMenuPercentAscending->addAction("12H %",[=, this](){
            emit sort("12hu%");
        });

        sortMenuPercentAscending->addAction("1D %",[=, this](){
            emit sort("1du%");
        });

        auto sortMenuPercentDescending = menu.addMenu("Sort Percent Descending");

        sortMenuPercentDescending->addAction("5M %",[=, this](){
            emit sort("5md%");
        });

        sortMenuPercentDescending->addAction("15M %",[=, this](){
            emit sort("15md%");
        });

        sortMenuPercentDescending->addAction("1H %",[=, this](){
            emit sort("1hd%");
        });

        sortMenuPercentDescending->addAction("4H %",[=, this](){
            emit sort("4hd%");
        });

        sortMenuPercentDescending->addAction("12H %",[=, this](){
            emit sort("12hd%");
        });

        sortMenuPercentDescending->addAction("1D %",[=, this](){
            emit sort("1dd%");
        });


        auto sortMenuSMADascending = menu.addMenu("Sort SMA Percent Ascending");

        // sortMenuSMADascending->addAction("1M %",[=, this](){
        //     emit sort("1smaa%");
        // });

        sortMenuSMADascending->addAction("5M %",[=, this](){
            emit sort("5smaa%");
        });

        sortMenuSMADascending->addAction("15M %",[=, this](){
            emit sort("15smaa%");
        });

        sortMenuSMADascending->addAction("1H %",[=, this](){
            emit sort("1hsmaa%");
        });

        sortMenuSMADascending->addAction("4H %",[=, this](){
            emit sort("4hsmaa%");
        });

        sortMenuSMADascending->addAction("12H %",[=, this](){
            emit sort("12hsmaa%");
        });

        sortMenuSMADascending->addAction("1D %",[=, this](){
            emit sort("1dsmaa%");
        });



        auto sortMenuSMADescending = menu.addMenu("Sort SMA Percent Descending");

        // sortMenuSMADescending->addAction("1M %",[=, this](){
        //     emit sort("1sma%");
        // });

        sortMenuSMADescending->addAction("5M %",[=, this](){
            emit sort("5sma%");
        });

        sortMenuSMADescending->addAction("15M %",[=, this](){
            emit sort("15sma%");
        });

        sortMenuSMADescending->addAction("1H %",[=, this](){
            emit sort("1hsma%");
        });

        sortMenuSMADescending->addAction("4H %",[=, this](){
            emit sort("4hsma%");
        });

        sortMenuSMADescending->addAction("12H %",[=, this](){
            emit sort("12hsma%");
        });

        sortMenuSMADescending->addAction("1D %",[=, this](){
            emit sort("1dsma%");
        });

        auto sortMenuEMA20Descending = menu.addMenu("Sort EMA 20 Percent Descending");

        // sortMenuSMADescending->addAction("1M %",[=, this](){
        //     emit sort("1sma%");
        // });

        sortMenuEMA20Descending->addAction("1M %",[=, this](){
            emit sort("1ema20%");
        });

        sortMenuEMA20Descending->addAction("5M %",[=, this](){
            emit sort("5ema20%");
        });

        sortMenuEMA20Descending->addAction("15M %",[=, this](){
            emit sort("15ema20%");
        });

        sortMenuEMA20Descending->addAction("1H %",[=, this](){
            emit sort("1hema20%");
        });

        sortMenuEMA20Descending->addAction("4H %",[=, this](){
            emit sort("4hema20%");
        });

        sortMenuEMA20Descending->addAction("12H %",[=, this](){
            emit sort("12hema20%");
        });

        sortMenuEMA20Descending->addAction("1D %",[=, this](){
            emit sort("1dema20%");
        });


        auto sortMenuEMA20Ascending = menu.addMenu("Sort EMA 20 Percent Ascending");

        // sortMenuSMADescending->addAction("1M %",[=, this](){
        //     emit sort("1sma%");
        // });

        auto autoSortMenuEMA20Ascending = sortMenuEMA20Ascending->addMenu("Auto");

        m_ema20AutoSort1m = createAction( autoSortMenuEMA20Ascending , "Auto 1M %" , "1ema20A%" );
        m_ema20AutoSort5m = createAction( autoSortMenuEMA20Ascending , "Auto 5M %" , "5ema20A%" );
        m_ema20AutoSort15m = createAction( autoSortMenuEMA20Ascending , "Auto 15M %" , "15ema20A%" );
        m_ema20AutoSort15m = createAction( autoSortMenuEMA20Ascending , "Auto 15M %" , "15ema20A%" );

        m_ema20AutoSort1h = createAction( autoSortMenuEMA20Ascending , "Auto 1H %"  ,"1hema20A%");
        m_ema20AutoSort4h = createAction( autoSortMenuEMA20Ascending , "Auto 4H %"  ,"4hema20A%");
        m_ema20AutoSort1d = createAction( autoSortMenuEMA20Ascending , "Auto 1D %"  ,"1dema20A%");
        m_ema20AutoSort1w = createAction( autoSortMenuEMA20Ascending , "Auto 1W %"  ,"1wema20A%");




        sortMenuEMA20Ascending->addAction("1M %",[=, this](){
            emit autoSort( false , "1ema20A%");
        });

        sortMenuEMA20Ascending->addAction("5M %",[=, this](){
            emit sort("5ema20A%");
        });

        sortMenuEMA20Ascending->addAction("15M %",[=, this](){
            emit sort("15ema20A%");
        });

        sortMenuEMA20Ascending->addAction("1H %",[=, this](){
            emit sort("1hema20A%");
        });

        sortMenuEMA20Ascending->addAction("4H %",[=, this](){
            emit sort("4hema20A%");
        });

        sortMenuEMA20Ascending->addAction("12H %",[=, this](){
            emit sort("12hema20A%");
        });

        sortMenuEMA20Ascending->addAction("1D %",[=, this](){
            emit sort("1dema20A%");
        });


        auto SortMenuRSI = menu.addMenu("RSI");

        auto autoSortMenuRSIAscending = SortMenuRSI->addMenu("RSI +");
        autoSortMenuRSIAscending->addAction("Total %",[=, this](){ emit sort("rsitotalA%"); });
        autoSortMenuRSIAscending->addAction("1M %",[=, this](){ emit sort("1rsi20A%"); });
        autoSortMenuRSIAscending->addAction("5M %",[=, this](){ emit sort("5rsi20A%"); });
        autoSortMenuRSIAscending->addAction("15M %",[=, this](){ emit sort("15rsi20A%"); });
        autoSortMenuRSIAscending->addAction("1H %",[=, this](){ emit sort("1hrsi20A%"); });
        autoSortMenuRSIAscending->addAction("4H %",[=, this](){ emit sort("4hrsi20A%"); });
        autoSortMenuRSIAscending->addAction("12H %",[=, this](){ emit sort("12hrsi20A%"); });
        autoSortMenuRSIAscending->addAction("1D %",[=, this](){ emit sort("1drsi20A%"); });
        autoSortMenuRSIAscending->addAction("1W %",[=, this](){ emit sort("1wrsi20A%"); });

        auto autoSortMenuRSIDescending = SortMenuRSI->addMenu("RSI -");
        autoSortMenuRSIDescending->addAction("Total %",[=, this](){ emit sort("rsitotalD%"); });

        autoSortMenuRSIDescending->addAction("1M %",[=, this](){ emit sort("1rsi20D%"); });
        autoSortMenuRSIDescending->addAction("5M %",[=, this](){ emit sort("5rsi20D%"); });
        autoSortMenuRSIDescending->addAction("15M %",[=, this](){ emit sort("15rsi20D%"); });
        autoSortMenuRSIDescending->addAction("1H %",[=, this](){ emit sort("1hrsi20D%"); });
        autoSortMenuRSIDescending->addAction("4H %",[=, this](){ emit sort("4hrsi20D%"); });
        autoSortMenuRSIDescending->addAction("12H %",[=, this](){ emit sort("12hrsi20D%"); });
        autoSortMenuRSIDescending->addAction("1D %",[=, this](){ emit sort("1drsi20D%"); });
        autoSortMenuRSIDescending->addAction("1W %",[=, this](){ emit sort("1wrsi20D%"); });


        menu.exec( event->screenPos() );
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

QAction *Graphic::PairItem::createAction(QMenu *menu, const QString &title, const QString &interval)
{
    auto action = menu->addAction( title );
    action->setCheckable( true );
    connect( action , &QAction::toggled , [=,this]( const bool toggled ){
        emit autoSort( true , interval );
    });
    return action;
}
