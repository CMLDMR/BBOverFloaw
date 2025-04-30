#include "series.h"

#include "binance/kline.h"
#include "indicator/bollinger.h"
#include "indicator/Sma.h"
#include "global/utility.h"
#include "global/alarmwidget.h"

#include "TelegramManager.h"

#include <QMutex>
#include <QMutexLocker>
#include <iostream>

namespace Series {

QMutex mutex;

Series::Series(const QString &_mPair, QObject *parent)
    : QObject{parent},mPair(_mPair)
{

    mImage = new QImage( 650 , 55 , QImage::Format_RGB888);
    mImage->fill(Qt::white);

    mThread = new QThread();
    this->moveToThread(mThread);
    QObject::connect(mThread,&QThread::started,this,&Series::SocketWorker);
    mThread->start(QThread::LowPriority);

    if( ! m_alarmImage.load("alarmicon.png") ){
        qDebug() << "alarm Image Not Loaded";
    }
}



QVector<Seri *> Series::seriList() const
{
    return mSeriList;
}

const double &Series::close() const
{
    return mClose;
}

QString Series::timeStr() const
{
    return mTimeStr;
}

QString Series::pair() const
{
    return mPair;
}

std::optional<Seri *> Series::getSeri(const QString &interval)
{
    Seri* seri{nullptr};
    bool exist = false;

    for( const auto &item : mSeriList ){
        if( item->interval() == interval ){
            seri = item;
            exist = true;
            break;
        }
    }

    if( exist ){
        return seri;
    }else{
        return std::nullopt;
    }
}

QImage *Series::image() const
{
    QMutexLocker locker(&mutex);  // Mutex kilitlenir
    return mImage;
}

double Series::getM5MinunteUpperPercent() const
{
    return m5MinunteUpperPercent;
}

double Series::allUpperPercent() const
{
    return mAllUpperPercent;
}

double Series::getM15MinunteUpperPercent() const
{
    return m15MinunteUpperPercent;
}

double Series::getM1HinunteUpperPercent() const
{
    return m1HinunteUpperPercent;
}

double Series::getM4HinunteUpperPercent() const
{
    return m4HinunteUpperPercent;
}

double Series::getM1DinunteUpperPercent() const
{
    return m1DinunteUpperPercent;
}

double Series::getM5MDownPercent() const
{
    return m5MDownPercent;
}

double Series::getM15MDownPercent() const
{
    return m15MDownPercent;
}

double Series::getM1HDownPercent() const
{
    return m1HDownPercent;
}

double Series::getM4HDownPercent() const
{
    return m4HDownPercent;
}

double Series::getM1DDownPercent() const
{
    return m1DDownPercent;
}

double Series::allDownPercent() const
{
    return mAllDownPercent;
}

int Series::upperGreenCount() const
{
    return mUpperGreenCount;
}

int Series::downGreenCount() const
{
    return mDownGreenCount;
}

double Series::allUpperSumPercent() const
{
    return mAllUpperSumPercent;
}

double Series::allDownSumPercent() const
{
    return mAllDownSumPercent;
}

double Series::getM5MinuntePercent() const
{
    return m5MinuntePercent;
}

double Series::getM15MinuntePercent() const
{
    return m15MinuntePercent;
}

double Series::getM1HinuntePercent() const
{
    return m1HinuntePercent;
}

double Series::getM4HinuntePercent() const
{
    return m4HinuntePercent;
}

double Series::getM1DinuntePercent() const
{
    return m1DinuntePercent;
}

double Series::getM12HinuntePercent() const
{
    return m12HinuntePercent;
}

double Series::getM12HinunteUpperPercent() const
{
    return m12HinunteUpperPercent;
}

double Series::getM12HDownPercent() const
{
    return m12HDownPercent;
}

std::tuple<double, double, double> Series::getAllBarPercentAndColorCount()
{
    return std::make_tuple(mAllBarPercentSum,static_cast<double>(mAllBarGreenCount),static_cast<double>(mAllBarRedCount));
}

double Series::open() const
{
    return mOpen;
}

double Series::getM1MinunteSMA200Percent() const
{
    return m1MinunteSMA200Percent;
}

double Series::getM5MinunteSMA200Percent() const
{
    return m5MinunteSMA200Percent;
}

double Series::getM15MinunteSMA200Percent() const
{
    return m15MinunteSMA200Percent;
}

double Series::getM1HinunteSMA200Percent() const
{
    return m1HinunteSMA200Percent;
}

double Series::getM4HinunteSMA200Percent() const
{
    return m4HinunteSMA200Percent;
}

double Series::getM12HinunteSMA200Percent() const
{
    return m12HinunteSMA200Percent;
}

double Series::getM1DinunteSMA200Percent() const
{
    return m1DinunteSMA200Percent;
}

double Series::getM1MinunteEMA200Percent() const
{
    return m1MinunteEMA200Percent;
}

double Series::getM5MinunteEMA200Percent() const
{
    return m5MinunteEMA200Percent;
}

double Series::getM15MinunteEMA200Percent() const
{
    return m15MinunteEMA200Percent;
}

double Series::getM1HinunteEMA200Percent() const
{
    return m1HinunteEMA200Percent;
}

double Series::getM4HinunteEMA200Percent() const
{
    return m4HinunteEMA200Percent;
}

double Series::getM12HinunteEMA200Percent() const
{
    return m12HinunteEMA200Percent;
}

double Series::getM1DinunteEMA200Percent() const
{
    return m1DinunteEMA200Percent;
}

double Series::getM1MinunteEMA20Percent() const
{
    return m1MinunteEMA20Percent;
}

double Series::getM5MinunteEMA20Percent() const
{
    return m5MinunteEMA20Percent;
}

double Series::getM15MinunteEMA20Percent() const
{
    return m15MinunteEMA20Percent;
}

double Series::getM1HinunteEMA20Percent() const
{
    return m1HinunteEMA20Percent;
}

double Series::getM4HinunteEMA20Percent() const
{
    return m4HinunteEMA20Percent;
}

double Series::getM12HinunteEMA20Percent() const
{
    return m12HinunteEMA20Percent;
}

double Series::getM1DinunteEMA20Percent() const
{
    return m1DinunteEMA20Percent;
}

double Series::getM1WinunteEMA20Percent() const
{
    return m1WinunteEMA20Percent;
}

double Series::getM1MinunteUpperPercent() const
{
    return m1MinunteUpperPercent;
}

double Series::getM1MinuntePercent() const
{
    return m1MinuntePercent;
}

double Series::getM1MDownPercent() const
{
    return m1MDownPercent;
}

void Series::setEnableBBD1minuteAlarm(bool newEnableBBD1minuteAlarm)
{
    m_enableBBD1minuteAlarm = newEnableBBD1minuteAlarm;
}

bool Series::enableBBD1minuteAlarm() const
{
    return m_enableBBD1minuteAlarm;
}

bool Series::enableBBD5minuteAlarm() const
{
    return m_enableBBD5minuteAlarm;
}

void Series::setEnableBBD5minuteAlarm(bool newEnableBBD5minuteAlarm)
{
    m_enableBBD5minuteAlarm = newEnableBBD5minuteAlarm;
}

bool Series::enableBBD15minuteAlarm() const
{
    return m_enableBBD15minuteAlarm;
}

void Series::setEnableBBD15minuteAlarm(bool newEnableBBD15minuteAlarm)
{
    m_enableBBD15minuteAlarm = newEnableBBD15minuteAlarm;
}

bool Series::enableBBD1hourAlarm() const
{
    return m_enableBBD1hourAlarm;
}

void Series::setEnableBBD1hourAlarm(bool newEnableBBD1hourAlarm)
{
    m_enableBBD1hourAlarm = newEnableBBD1hourAlarm;
}



bool Series::enableBBD4hourAlarm() const
{
    return m_enableBBD4hourAlarm;
}

void Series::setEnableBBD4hourAlarm(bool newEnableBBD4hourAlarm)
{
    m_enableBBD4hourAlarm = newEnableBBD4hourAlarm;
}

bool Series::enableBBD1dayAlarm() const
{
    return m_enableBBD1dayAlarm;
}

void Series::setEnableBBD1dayAlarm(bool newEnableBBD1dayAlarm)
{
    m_enableBBD1dayAlarm = newEnableBBD1dayAlarm;
}

double Series::getM15MinunteRSI() const
{
    return m15MinunteRSI;
}

double Series::getM1MinunteRSI() const
{
    return m1MinunteRSI;
}

double Series::getM5MinunteRSI() const
{
    return m5MinunteRSI;
}

double Series::getM1HourRSI() const
{
    return m1HourRSI;
}

double Series::getM4HourRSI() const
{
    return m4HourRSI;
}

double Series::getM12HourRSI() const
{
    return m12HourRSI;
}

double Series::getM1DayRSI() const
{
    return m1DayRSI;
}

double Series::getM1WeekRSI() const
{
    return m1WeekRSI;
}

void Series::SocketWorker()
{
    //    qDebug() << "Start Series";

    // if( ! mSeriList.size() ) {
    //     qDebug() << __LINE__ << __FILE__ << "mSeriList Empty";
    //     return;
    // }


    // if( ! mSeriList.last()->kLineContainer().size() ) {
    //     qDebug() << __LINE__ << __FILE__ << "KLineCOntainer Empty";
    //     return;
    // }

    const int loadingY = 0;
    const int loadingHeight = 5;


    mPainter = new QPainter();
    mPainter->begin(mImage);
    auto tempFont = mPainter->font();
    mPainter->setFont(QFont("Tahoma",16));
    mPainter->drawRect(0,0,mImage->rect().width()-1,mImage->height()-1);
    mPainter->drawText(20,30,this->pair()+" Loading...");

    // qDebug() << __LINE__<< __FILE__;
    // bu 15 saniye mumbar tamamlanmadı
    // mSeriList.append(new Seri(mPair,"15ms"));


    mSeriList.append(new Seri(mPair,"1m")); qDebug() << __LINE__<< __FILE__;
    if( ! mSeriList.last()->kLineContainer().size() ) {
        qDebug() << __LINE__ << __FILE__ << "KLineCOntainer Empty";
        return;
    }

    mClose = mSeriList.last()->kLineContainer().last().closePrice();
    // qDebug() << __LINE__ << __FILE__;
    mPainter->fillRect(0,loadingY,mImage->width()/7,loadingHeight,Qt::darkGreen);
    // qDebug() << __LINE__<< __FILE__;
    emit dataUpdated(false);
    mSeriList.append(new Seri(mPair,"3m"));
    // qDebug() << __LINE__<< __FILE__;

    mSeriList.append(new Seri(mPair,"5m"));
    mClose = mSeriList.last()->close();
    mOpen = mSeriList.last()->open();
    mPainter->fillRect(0,loadingY,2*mImage->width()/7,loadingHeight,Qt::darkGreen);
    emit dataUpdated(false);
    // qDebug() << __LINE__<< __FILE__;
    mSeriList.append(new Seri(mPair,"15m"));
    mPainter->fillRect(0,loadingY,3*mImage->width()/7,loadingHeight,Qt::darkGreen);
    emit dataUpdated(false);
    // qDebug() << __LINE__<< __FILE__;
       mSeriList.append(new Seri(mPair,"30m"));
       emit dataUpdated(false);

    mSeriList.append(new Seri(mPair,"1h"));
    emit dataUpdated(false);
    // qDebug() << __LINE__<< __FILE__;
    mPainter->fillRect(0,loadingY,4*mImage->width()/7,loadingHeight,Qt::darkGreen);
    mSeriList.append(new Seri(mPair,"2h"));
    // mSeriList.append(new Seri(mPair,"3h"));

    mSeriList.append(new Seri(mPair,"4h"));
    emit dataUpdated(false);
    // qDebug() << __LINE__<< __FILE__;
    mSeriList.append(new Seri(mPair,"6h"));
        mSeriList.append(new Seri(mPair,"8h"));
        mSeriList.append(new Seri(mPair,"12h"));
    emit dataUpdated(false);

    mPainter->fillRect(0,loadingY,5*mImage->width()/7,loadingHeight,Qt::darkGreen);
    mSeriList.append(new Seri(mPair,"1d"));
    //    emit dataUpdated(false);
    mPainter->fillRect(0,loadingY,6*mImage->width()/7,loadingHeight,Qt::darkGreen);

    mSeriList.append(new Seri(mPair,"3d"));


    mSeriList.append(new Seri(mPair,"1w"));

    mPainter->fillRect(0,loadingY,mImage->width(),loadingHeight,Qt::darkGreen);

    mPainter->setFont(tempFont);
    mPainter->end();

    mSocket = Binance::Public::WebSocketAPI::WebSocketAPI::createSocket(mPair);
    QObject::connect(mSocket,&Binance::Public::WebSocketAPI::WebSocketAPI::receivedAggregate,[=, this](const Binance::Public::WebSocketAPI::Aggregate aggregate ){

        emit aggregateSignal( aggregate );
        mClose = aggregate.price();
        mTimeStr = QDateTime::fromMSecsSinceEpoch(aggregate.eventTime()).time().toString("hh:mm:ss");

        bool Is_this_kline_closed = false;

        for( auto &item : mSeriList ){

            auto kline = item->last();
            kline.setEventTime(aggregate.eventTime());

            if( aggregate.eventTime() > kline.closeTime() ){

                kline.setOpenTime(item->openTime()+item->duration());
                kline.setCloseTime(item->closeTime()+item->duration());
                kline.setHighPrice(aggregate.price());
                kline.setLowPrice(aggregate.price());
                kline.setClosePrice(aggregate.price());
                kline.setOpenPrice(aggregate.price());
                kline.setVolume(aggregate.quantity());
                kline.setNumberOfTrade(1);
                kline.setQuotaAssetVolume( aggregate.isMaker() , aggregate.price()*aggregate.quantity() , true );

                if( !aggregate.isMaker() ){
                    kline.setTakerQuotaAseetVolume(aggregate.price()*aggregate.quantity());
                    kline.setTakerBaseAssetVolume(aggregate.quantity());
                }else{
                    kline.setTakerQuotaAseetVolume(0);
                    kline.setTakerBaseAssetVolume(0);
                }


                item->append(kline);
                item->removeFirst();

                Is_this_kline_closed = true;
            }else{


                kline.setClosePrice(aggregate.price());


                if( aggregate.price() > kline.highPrice() ){
                    kline.setHighPrice(aggregate.price());
                }

                if( aggregate.price() < kline.lowPrice() ){
                    kline.setLowPrice(aggregate.price());
                }

                kline.setVolume(kline.volume()+aggregate.quantity());
                kline.setAssetVolume(kline.quoteAssetVolume()+aggregate.quantity()*aggregate.price());

                kline.setQuotaAssetVolume( aggregate.isMaker() , aggregate.price()*aggregate.quantity() );

                if( !aggregate.isMaker() ){
                    kline.setTakerBaseAssetVolume(kline.takerBuyBaseAssetVolume()+aggregate.quantity());
                    kline.setTakerQuotaAseetVolume(kline.takerBuyQuoteAssetVolume()+aggregate.price()*aggregate.quantity());
                }
                kline.setNumberOfTrade(kline.numberOfTrades()+1);
                item->removelast();
                item->append(kline);
            }

            if( kline.eventTime() - mLastTimeForEmitSignal > 100 ){
                mLastTimeForEmitSignal = kline.eventTime();
                prePareImage(mPainter);
            }

            //            emit item->updated();

        }


        emit dataUpdated(Is_this_kline_closed);


    });

    mSocket->startAggregateStream();
}

void Series::prePareImage(QPainter *painter)
{

    mImage->fill(Qt::white);
    painter->begin(mImage);

    painter->setFont(QFont("Tahoma",10,2));


    {// Pair name
        painter->save();
        painter->setPen(QPen(Qt::white));

        auto fontMetric = painter->fontMetrics();
        auto rect = fontMetric.boundingRect(this->pair().mid(0,this->pair().size()-4));
        painter->fillRect(2,0,rect.width()+6,rect.height()+2,Qt::gray);
        painter->drawText(5,13 ,this->pair().mid(0,this->pair().size()-4));
        painter->restore();
    }

    {// Last Price
        painter->save();

        auto fontMetric = painter->fontMetrics();
        auto rect = fontMetric.boundingRect(QString::number(this->close()));
        painter->fillRect(2,17,rect.width()+6,rect.height()+2,this->close() > this->open() ? Qt::darkRed : Qt::darkGreen);
        mOpen = this->close();

        painter->setPen(QPen(Qt::white));
        painter->drawText(2, 30 ,QString::number(this->close()));

        painter->restore();


    }

    const int cellWidth{38};

    ///TODO: Önceden Hesaplanıp Sadece Positif Değer yazılacak
    //    this->calcAllBollingerValues();

    {// intervals
        int xPos = 110;
        const int indNameWidth = xPos-3;
        mUpperGreenCount = 0;
        mDownGreenCount = 0;

        mAllUpperPercent = 0;
        mAllDownPercent = 0;

        mAllDownSumPercent = 0;
        mAllUpperSumPercent = 0;

        mAllBarGreenCount = 0;
        mAllBarRedCount = 0;

        mAllBarPercentSum = 0;

        for( const auto &seri : this->seriList() ){

            if( seri->interval() != "1w" ){
                mAllBarPercentSum += seri->percentLastBar();
                if( seri->percentLastBar() > 0 ){
                    mAllBarGreenCount++;
                }else if( seri->percentLastBar() < 0 ){
                    mAllBarRedCount++;
                }
            }

            const auto smaValue = Indicator::RSI::value( *seri , 14 );
            const auto percent = smaValue ;

            QColor color;
            const auto hue = ( percent - 10 )/100*120;
            color.setHsv( hue < 0 ? 0 : ( hue > 120 ? 120 : hue ) , 255 , 255 );


            auto rect = QRectF(0,0,0,15);
            auto pen = painter->pen();
            painter->setPen(QPen(Qt::black));

            painter->fillRect(xPos-1,0,cellWidth,rect.height()*2+2 , color );

            painter->drawText(xPos, rect.height() ,seri->interval());
            painter->drawText(xPos, rect.height()+15 ,"%"+Global::getFixedPrecision(seri->percentLastBar(),1));

            painter->setPen(pen);

            int yPos = rect.height()+18;

            // { // Bollinger Percent 2.38
            //     painter->fillRect(1,yPos + 3,indNameWidth,16,QColor(235,235,235));


            //     auto [upper,down] = Indicator::Bollinger::bollingerPercent(*seri,m_length,2.0);

            //     const QString alarmHighString = QString("%1 %2 close:%3 %4").arg( seri->pair() ).arg(seri->interval() ).arg( seri->close() ).arg("Higher");
            //     const QString alarmLowString = QString("%1 %2 close:%3 %4").arg( seri->pair() ).arg(seri->interval() ).arg( seri->close() ).arg("Lower");

            //     if( seri->interval() == "1m" ){
            //         m1MinuntePercent = seri->percentLastBar();
            //         m1MinunteUpperPercent = upper;
            //         m1MDownPercent = down;
            //         if( upper > 0 && m_enableBBD1minuteAlarm ) {
            //             emit alarmed( alarmHighString );
            //         }
            //         if( down > 0 && m_enableBBD1minuteAlarm ) {
            //             emit alarmed( alarmLowString );
            //         }
            //     }

            //     if( seri->interval() == "5m" ){
            //         m5MinuntePercent = seri->percentLastBar();
            //         m5MinunteUpperPercent = upper;
            //         m5MDownPercent = down;
            //         if( upper > 0 && m_enableBBD5minuteAlarm ) {
            //             emit alarmed( alarmHighString );
            //         }
            //         if( down > 0 && m_enableBBD5minuteAlarm ) {
            //             emit alarmed( alarmLowString );
            //         }
            //     }

            //     if( seri->interval() == "15m" ){
            //         m15MinuntePercent = seri->percentLastBar();
            //         m15MinunteUpperPercent = upper;
            //         m15MDownPercent = down;
            //         if( upper > 0 && m_enableBBD15minuteAlarm ) {
            //             emit alarmed( alarmHighString );
            //         }
            //         if( down > 0 && m_enableBBD15minuteAlarm ) {
            //             emit alarmed( alarmLowString );
            //         }

            //         // bool  { true };

            //     }

            //     if( seri->interval() == "1h" ){
            //         m1HinuntePercent = seri->percentLastBar();
            //         m1HinunteUpperPercent = upper;
            //         m1HDownPercent = down;
            //         if( upper > 0 && m_enableBBD1hourAlarm ) {
            //             emit alarmed( alarmHighString );
            //         }
            //         if( down > 0 && m_enableBBD1hourAlarm ) {
            //             emit alarmed( alarmLowString );
            //         }
            //     }

            //     if( seri->interval() == "4h" ){
            //         m4HinuntePercent = seri->percentLastBar();
            //         m4HinunteUpperPercent = upper;
            //         m4HDownPercent = down;

            //         if( m_enableBBD4hourAlarm ) {
            //             painter->drawImage( QRectF(xPos-1+33,yPos+4+2,cellWidth-35,rect.height()-5) , m_alarmImage );
            //             painter->drawImage( QRectF(xPos-1+33,yPos+4+2+15,cellWidth-35,rect.height()-5) , m_alarmImage );
            //         }

            //         if( upper > 0 && m_enableBBD4hourAlarm ) {
            //             emit alarmed( alarmHighString );
            //         }
            //         if( down > 0 && m_enableBBD4hourAlarm ) {
            //             emit alarmed( alarmLowString );
            //         }
            //     }

            //     if( seri->interval() == "12h" ){
            //         m12HinuntePercent = seri->percentLastBar();
            //         m12HinunteUpperPercent = upper;
            //         m12HDownPercent = down;
            //     }


            //     if( seri->interval() == "1d" ){
            //         m1DinuntePercent = seri->percentLastBar();
            //         m1DinunteUpperPercent = upper;
            //         m1DDownPercent = down;

            //         if( upper > 0 && m_enableBBD1dayAlarm ) {
            //             emit alarmed( alarmHighString );
            //         }
            //         if( down > 0 && m_enableBBD1dayAlarm ) {
            //             emit alarmed( alarmLowString );
            //         }
            //     }

            //     mAllDownSumPercent += down;
            //     mAllUpperSumPercent += upper;



            //     if( upper > 0 ){
            //         if( upper < 1 ) {
            //             painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),QColor( 150 , 255 ,150 ));

            //         }else{
            //             painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),QColor( 0 , 255 , 0 ));
            //         }
            //         // painter->fillRect(QRectF(xPos+1,yPos+2,cellWidth,rect.height()),Qt::green);

            //         mAlarmActivated = true;
            //         mUpperGreenCount++;
            //         mAllUpperPercent += upper;

            //     }
            //     if( down > 0 ){

            //         // painter->fillRect(QRectF(xPos+1,yPos+2,cellWidth,rect.height()),Qt::green);

            //         if( down < 1 ) {
            //             painter->fillRect(QRectF(xPos-1,yPos+4+15,cellWidth,rect.height()),QColor( 150 , 255 , 150 ));

            //         }else{
            //             painter->fillRect(QRectF(xPos-1,yPos+4+15,cellWidth,rect.height()),QColor( 0 , 255 , 0 ));
            //         }
            //         mAlarmActivated = true;
            //         mDownGreenCount++;
            //         mAllDownPercent += down;

            //     }

            //     if( seri->interval() == "1m" && m_enableBBD1minuteAlarm ) {
            //         painter->drawImage( QRectF(xPos-1+33,yPos+4+2,cellWidth-35,rect.height()-5) , m_alarmImage );
            //         painter->drawImage( QRectF(xPos-1+33,yPos+4+2+15,cellWidth-35,rect.height()-5) , m_alarmImage );
            //     }

            //     if( seri->interval() == "5m" && m_enableBBD5minuteAlarm ) {
            //         painter->drawImage( QRectF(xPos-1+33,yPos+4+2,cellWidth-35,rect.height()-5) , m_alarmImage );
            //         painter->drawImage( QRectF(xPos-1+33,yPos+4+2+15,cellWidth-35,rect.height()-5) , m_alarmImage );
            //     }

            //     if( seri->interval() == "15m" && m_enableBBD15minuteAlarm ) {
            //         painter->drawImage( QRectF(xPos-1+33,yPos+4+2,cellWidth-35,rect.height()-5) , m_alarmImage );
            //         painter->drawImage( QRectF(xPos-1+33,yPos+4+2+15,cellWidth-35,rect.height()-5) , m_alarmImage );
            //     }

            //     if( seri->interval() == "1h" && m_enableBBD1hourAlarm ) {
            //         painter->drawImage( QRectF(xPos-1+33,yPos+4+2,cellWidth-35,rect.height()-5) , m_alarmImage );
            //         painter->drawImage( QRectF(xPos-1+33,yPos+4+2+15,cellWidth-35,rect.height()-5) , m_alarmImage );
            //     }

            //     if( seri->interval() == "4h" && m_enableBBD4hourAlarm ) {
            //         painter->drawImage( QRectF(xPos-1+33,yPos+4+2,cellWidth-35,rect.height()-5) , m_alarmImage );
            //         painter->drawImage( QRectF(xPos-1+33,yPos+4+2+15,cellWidth-35,rect.height()-5) , m_alarmImage );
            //     }

            //     if( seri->interval() == "1d" && m_enableBBD1dayAlarm ) {
            //         painter->drawImage( QRectF(xPos-1+33,yPos+4+2,cellWidth-35,rect.height()-5) , m_alarmImage );
            //         painter->drawImage( QRectF(xPos-1+33,yPos+4+2+15,cellWidth-35,rect.height()-5) , m_alarmImage );
            //     }


            //     yPos += 15;
            //     painter->drawText(xPos, yPos ,Global::getFixedPrecision(upper));
            //     painter->drawText(5, yPos ,QString("BBU %1/2.0  %").arg(m_length));

            //     yPos += 15;
            //     painter->drawText(5, yPos ,QString("BBD %1/2.0 %").arg(m_length));
            //     painter->drawText(xPos, yPos ,Global::getFixedPrecision(down));

            // }

            // {// SMA 200

            //     painter->fillRect(1,yPos + 3,indNameWidth,16,QColor(235,235,235));

            //     painter->drawText(5, yPos+15 ,"SMA 200 %");
            //     // calculate RSI
            //     const auto smaValue = Indicator::Sma::value( *seri , 200 );
            //     const auto percent =( seri->close() - smaValue )/smaValue*100 ;

            //     if ( percent > 70 ) {
            //         painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),QColor( 0 , 255 ,0 ));
            //     }
            //     else if( percent < 30 ) {
            //         painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),QColor( 255 , 0 ,0 ));
            //     }

            //     if( seri->interval() == "1m" ){
            //         m1MinunteSMA200Percent = percent;
            //     }

            //     if( seri->interval() == "5m" ){
            //         m5MinunteSMA200Percent = percent;
            //     }

            //     if( seri->interval() == "15m" ){
            //         m15MinunteSMA200Percent = percent;
            //     }

            //     if( seri->interval() == "1h" ){
            //         m1HinunteSMA200Percent = percent;
            //     }

            //     if( seri->interval() == "4h" ){
            //         m4HinunteSMA200Percent = percent;
            //     }

            //     if( seri->interval() == "12h" ){
            //         m12HinunteSMA200Percent = percent;
            //     }


            //     if( seri->interval() == "1d" ){
            //         m1DinunteSMA200Percent = percent;
            //     }


            //     painter->drawText(xPos, yPos+15 ,Global::getFixedPrecision( percent ) );
            //     yPos += 15;
            // }

            // {// EMA 200

            //     painter->drawText(5, yPos+15 ,"EMA 200 %");

            //     // calculate SMA
            //     const auto smaValue = Indicator::Ema::value( *seri , 200 );
            //     const auto percent =( seri->close() - smaValue )/smaValue*100 ;
            //     if ( percent > 0 ) {
            //         if( percent > 1 ) {
            //             painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),QColor( 0 , 255 ,0 ));

            //         }else{
            //             painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),QColor( 200 , 255 ,200 ));
            //         }                }
            //     else if( percent < 0 ) {
            //         if( percent < -1 ) {
            //             painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),QColor( 255 , 0 ,0 ));

            //         }else{
            //             painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),QColor( 255 , 200 ,200 ));
            //         }
            //     }
            //     if( seri->interval() == "1m" ){
            //         m1MinunteEMA200Percent = percent;
            //     }

            //     if( seri->interval() == "5m" ){
            //         m5MinunteEMA200Percent = percent;
            //     }

            //     if( seri->interval() == "15m" ){
            //         m15MinunteEMA200Percent = percent;
            //     }

            //     if( seri->interval() == "1h" ){
            //         m1HinunteEMA200Percent = percent;
            //     }

            //     if( seri->interval() == "4h" ){
            //         m4HinunteEMA200Percent = percent;
            //     }

            //     if( seri->interval() == "12h" ){
            //         m12HinunteEMA200Percent = percent;
            //     }

            //     if( seri->interval() == "1d" ){
            //         m1DinunteEMA200Percent = percent;
            //     }

            //     painter->drawText(xPos, yPos+15 ,Global::getFixedPrecision( percent ) );
            //     yPos += 15;
            // }


            // {// EMA 20

            //     painter->fillRect(1,yPos + 3,indNameWidth,16,QColor(235,235,235));

            //     painter->drawText(5, yPos+15 ,"EMA 20 %");

            //     // calculate SMA
            //     const auto smaValue = Indicator::Ema::value( *seri , 20 );
            //     const auto percent =( seri->close() - smaValue )/smaValue*100 ;
            //     if ( percent > 0 ) {
            //         if( percent > 1 ) {
            //             painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),QColor( 0 , 255 ,0 ));

            //         }else{
            //             painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),QColor( 200 , 255 ,200 ));
            //         }
            //     }
            //     else if( percent < 0 ) {
            //         if( percent < -1 ) {
            //             painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),QColor( 255 , 0 ,0 ));

            //         }else{
            //             painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),QColor( 255 , 200 ,200 ));
            //         }
            //     }

            //     if( seri->interval() == "1m" ){
            //         m1MinunteEMA20Percent = percent;
            //     }

            //     if( seri->interval() == "5m" ){
            //         m5MinunteEMA20Percent = percent;
            //     }

            //     if( seri->interval() == "15m" ){
            //         m15MinunteEMA20Percent = percent;
            //     }

            //     if( seri->interval() == "1h" ){
            //         m1HinunteEMA20Percent = percent;
            //     }

            //     if( seri->interval() == "4h" ){
            //         m4HinunteEMA20Percent = percent;
            //     }

            //     if( seri->interval() == "12h" ){
            //         m12HinunteEMA20Percent = percent;
            //     }


            //     if( seri->interval() == "1d" ){
            //         m1DinunteEMA20Percent = percent;
            //     }

            //     if( seri->interval() == "1w" ){
            //         m1WinunteEMA20Percent = percent;
            //     }


            //     painter->drawText(xPos, yPos+15 ,Global::getFixedPrecision( percent ) );
            //     yPos += 15;
            // }


            {// RSI 14

                // painter->fillRect(1,yPos + 3,indNameWidth,16,QColor(235,235,235));


                // calculate SMA
                const auto smaValue = Indicator::RSI::value( *seri , 14 );
                const auto percent = smaValue ;

                QColor color;
                const auto hue = ( percent - 10 )/100*120;
                color.setHsv( hue < 0 ? 0 : ( hue > 120 ? 120 : hue ) , 255 , 255 );
                painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()) , color );

                if( seri->interval() == "1m" ){
                    m1MinunteRSI = percent;
                }

                if( seri->interval() == "3m" ){
                    m3MinunteRSI = percent;
                }

                if( seri->interval() == "5m" ){
                    m5MinunteRSI = percent;
                }


                if( seri->interval() == "15m" ){
                    m15MinunteRSI = percent;
                }

                if( seri->interval() == "30m" ){
                    m30MinunteRSI = percent;
                }

                if( seri->interval() == "1h" ){
                    m1HourRSI = percent;
                }

                if( seri->interval() == "4h" ){
                    m4HourRSI = percent;
                }

                if( seri->interval() == "12h" ){
                    m12HourRSI = percent;
                }


                if( seri->interval() == "1d" ){
                    m1DayRSI = percent;
                }

                if( seri->interval() == "1w" ){
                    m1WeekRSI = percent;
                }

                const auto totalRSI = m1MinunteRSI + m3MinunteRSI*3 + m5MinunteRSI*5 + m15MinunteRSI*15 + m30MinunteRSI*30 + m1HourRSI * 60;
                if( totalRSI != maboveTotalHourRSI ) {
                    maboveTotalHourRSI = totalRSI;
                }


                if( seri->interval() == "1m" ){
                    const auto hue = ( maboveTotalHourRSI/114 - 10 )/100*120;
                    color.setHsv( hue < 0 ? 0 : ( hue > 120 ? 120 : hue ) , 255 , 255 );
                    painter->fillRect(QRectF(0,yPos+4, maboveTotalHourRSI/114 ,rect.height()) , color );

                    painter->drawText(5, yPos+15 ,QString("RSI 14 %1").arg(Global::getFixedPrecision( maboveTotalHourRSI/114 )));

                }

                painter->drawText(xPos, yPos+15 ,Global::getFixedPrecision( percent ) );
                yPos += 15;
            }


            if(0){ // RSI Bollinger Band 2.38
                painter->fillRect(1,yPos + 3,indNameWidth,16,QColor(235,235,235));

                std::vector<double> openList;
                std::vector<double> closeList;
                std::vector<double> highList;
                std::vector<double> lowList;

                for( int i = 0 ; i < seri->size() ; i++ ) {
                    openList.push_back( seri->open( i ) );
                    closeList.push_back( seri->close( i ) );
                    highList.push_back( seri->high( i ) );
                    lowList.push_back( seri->low( i ) );
                }
                std::vector<double> rsiOpenList;
                std::vector<double> rsiCloseList;
                std::vector<double> rsiHighList;
                std::vector<double> rsiLowList;


                auto tempOpenList = openList;
                auto tempCloseList = closeList;
                auto tempHighList = highList;
                auto tempLowList = lowList;

                for( int i = 0 ; i < 125 ; i++ ) {
                    rsiCloseList.insert( rsiCloseList.begin() , Indicator::RSI::value( tempCloseList ) );
                    tempCloseList.pop_back();// tempCloseList.begin() );
                }




                auto [upper,middle,down] = Indicator::calculateBollingerBands( rsiCloseList , 60 );

                const QString alarmHighString = QString("%1 %2 close:%3 %4").arg( seri->pair() ).arg(seri->interval() ).arg( seri->close() ).arg("Higher");
                const QString alarmLowString  = QString("%1 %2 close:%3 %4").arg( seri->pair() ).arg(seri->interval() ).arg( seri->close() ).arg("Lower");

                if( seri->interval() == "1m" ){
                    m1MinuntePercent = seri->percentLastBar();
                    m1MinunteUpperPercent = upper;
                    m1MDownPercent = down;
                    if( upper > 0 && m_enableBBD1minuteAlarm ) {
                        emit alarmed( alarmHighString );
                    }
                    if( down > 0 && m_enableBBD1minuteAlarm ) {
                        emit alarmed( alarmLowString );
                    }


                    // TelegramManager::instance()->sendMessage("Bot", std::format("1 min {} {} {}",upper ,rsiCloseList.back() , down ).data() );

                }

                if( seri->interval() == "5m" ){
                    m5MinuntePercent = seri->percentLastBar();
                    m5MinunteUpperPercent = upper;
                    m5MDownPercent = down;
                    if( upper > 0 && m_enableBBD5minuteAlarm ) {
                        emit alarmed( alarmHighString );
                    }
                    if( down > 0 && m_enableBBD5minuteAlarm ) {
                        emit alarmed( alarmLowString );
                    }
                }

                if( seri->interval() == "15m" ){
                    m15MinuntePercent = seri->percentLastBar();
                    m15MinunteUpperPercent = upper;
                    m15MDownPercent = down;
                    if( upper > 0 && m_enableBBD15minuteAlarm ) {
                        emit alarmed( alarmHighString );
                    }
                    if( down > 0 && m_enableBBD15minuteAlarm ) {
                        emit alarmed( alarmLowString );
                    }
                }

                if( seri->interval() == "1h" ){
                    m1HinuntePercent = seri->percentLastBar();
                    m1HinunteUpperPercent = upper;
                    m1HDownPercent = down;
                    if( upper > 0 && m_enableBBD1hourAlarm ) {
                        emit alarmed( alarmHighString );
                    }
                    if( down > 0 && m_enableBBD1hourAlarm ) {
                        emit alarmed( alarmLowString );
                    }
                }

                if( seri->interval() == "4h" ){
                    m4HinuntePercent = seri->percentLastBar();
                    m4HinunteUpperPercent = upper;
                    m4HDownPercent = down;

                    if( m_enableBBD4hourAlarm ) {
                        painter->drawImage( QRectF(xPos-1+33,yPos+4+2,cellWidth-35,rect.height()-5) , m_alarmImage );
                        painter->drawImage( QRectF(xPos-1+33,yPos+4+2+15,cellWidth-35,rect.height()-5) , m_alarmImage );
                    }

                    if( upper > 0 && m_enableBBD4hourAlarm ) {
                        emit alarmed( alarmHighString );
                    }
                    if( down > 0 && m_enableBBD4hourAlarm ) {
                        emit alarmed( alarmLowString );
                    }
                }

                if( seri->interval() == "12h" ){
                    m12HinuntePercent = seri->percentLastBar();
                    m12HinunteUpperPercent = upper;
                    m12HDownPercent = down;
                }


                if( seri->interval() == "1d" ){
                    m1DinuntePercent = seri->percentLastBar();
                    m1DinunteUpperPercent = upper;
                    m1DDownPercent = down;

                    if( upper > 0 && m_enableBBD1dayAlarm ) {
                        emit alarmed( alarmHighString );
                    }
                    if( down > 0 && m_enableBBD1dayAlarm ) {
                        emit alarmed( alarmLowString );
                    }
                }

                mAllDownSumPercent += down;
                mAllUpperSumPercent += upper;

                QColor color;

                // color.setHsv( percent/100*120 , 255 , 255 );


                color.setHsv( (rsiCloseList.back() - down) / ( upper - down ) * 120 , 255 , 255 );
                painter->fillRect(QRectF(xPos+1,yPos+2,cellWidth,rect.height()),color);

                color.setHsv( 120 - down/100*120 , 255 , 255 );

                painter->fillRect(QRectF(xPos-1,yPos+4+15,cellWidth,rect.height()),color);


                if( seri->interval() == "1m" && m_enableBBD1minuteAlarm ) {
                    painter->drawImage( QRectF(xPos-1+33,yPos+4+2,cellWidth-35,rect.height()-5) , m_alarmImage );
                    painter->drawImage( QRectF(xPos-1+33,yPos+4+2+15,cellWidth-35,rect.height()-5) , m_alarmImage );
                }

                if( seri->interval() == "5m" && m_enableBBD5minuteAlarm ) {
                    painter->drawImage( QRectF(xPos-1+33,yPos+4+2,cellWidth-35,rect.height()-5) , m_alarmImage );
                    painter->drawImage( QRectF(xPos-1+33,yPos+4+2+15,cellWidth-35,rect.height()-5) , m_alarmImage );
                }

                if( seri->interval() == "15m" && m_enableBBD15minuteAlarm ) {
                    painter->drawImage( QRectF(xPos-1+33,yPos+4+2,cellWidth-35,rect.height()-5) , m_alarmImage );
                    painter->drawImage( QRectF(xPos-1+33,yPos+4+2+15,cellWidth-35,rect.height()-5) , m_alarmImage );
                }

                if( seri->interval() == "1h" && m_enableBBD1hourAlarm ) {
                    painter->drawImage( QRectF(xPos-1+33,yPos+4+2,cellWidth-35,rect.height()-5) , m_alarmImage );
                    painter->drawImage( QRectF(xPos-1+33,yPos+4+2+15,cellWidth-35,rect.height()-5) , m_alarmImage );
                }

                if( seri->interval() == "4h" && m_enableBBD4hourAlarm ) {
                    painter->drawImage( QRectF(xPos-1+33,yPos+4+2,cellWidth-35,rect.height()-5) , m_alarmImage );
                    painter->drawImage( QRectF(xPos-1+33,yPos+4+2+15,cellWidth-35,rect.height()-5) , m_alarmImage );
                }

                if( seri->interval() == "1d" && m_enableBBD1dayAlarm ) {
                    painter->drawImage( QRectF(xPos-1+33,yPos+4+2,cellWidth-35,rect.height()-5) , m_alarmImage );
                    painter->drawImage( QRectF(xPos-1+33,yPos+4+2+15,cellWidth-35,rect.height()-5) , m_alarmImage );
                }


                yPos += 15;
                painter->drawText(xPos, yPos ,Global::getFixedPrecision( upper ));
                painter->drawText(5, yPos ,QString("RSI UB 60/2.0"));

                yPos += 15;
                painter->drawText(5, yPos ,QString("RSI DB 60/2.0 "));
                painter->drawText(xPos, yPos ,Global::getFixedPrecision( down ));

            }



            if(0){// ADX 14

                // painter->fillRect(1,yPos + 3,indNameWidth,16,QColor(235,235,235));

                painter->drawText(5, yPos+15 ,"ADX 14 %");

                // calculate SMA
                const auto adxValue = Indicator::ADX::value( *seri , 14 );


                QColor color;
                color.setHsv( adxValue / 100 * 120 , 255 , 255 );
                painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),color);


                // if ( adxValue > 50 ) {
                //     painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),color);
                // }
                // else if( adxValue < 10 ) {
                //     painter->fillRect(QRectF(xPos-1,yPos+4,cellWidth,rect.height()),color);
                // }

                // if( seri->interval() == "1m" ){
                //     m1MinunteRSI = adxValue;
                // }

                // if( seri->interval() == "5m" ){
                //     m5MinunteRSI = adxValue;
                // }

                // if( seri->interval() == "15m" ){
                //     m15MinunteRSI = adxValue;
                // }

                // if( seri->interval() == "1h" ){
                //     m1HourRSI = adxValue;
                // }

                // if( seri->interval() == "4h" ){
                //     m4HourRSI = adxValue;
                // }

                // if( seri->interval() == "12h" ){
                //     m12HourRSI = adxValue;
                // }

                // if( seri->interval() == "1d" ){
                //     m1DayRSI = adxValue;
                // }

                // if( seri->interval() == "1w" ){
                //     m1WeekRSI = adxValue;
                // }

                painter->drawText(xPos, yPos+15 ,Global::getFixedPrecision( adxValue ) );
                yPos += 15;

            }



            pen = painter->pen();
            painter->setPen(QPen(Qt::gray,1,Qt::DotLine));
            painter->drawLine(xPos-2,1,xPos-2,mImage->height()-2);

            painter->setPen(pen);
            xPos += cellWidth;
        }

        // painter->drawText(65, 30+75 ,"S:"+Global::getFixedPrecision(mAllDownPercent) + " A:"+Global::getFixedPrecision(mAllDownSumPercent));
        // painter->drawText(65, 30+15 ,"S:"+Global::getFixedPrecision(mAllUpperPercent) + " A:"+Global::getFixedPrecision(mAllUpperSumPercent));

        // painter->drawText(2, 15+15 ,Global::getFixedPrecision(mAllBarPercentSum) + "% " + QString("%1/%2").arg(mAllBarGreenCount).arg(mAllBarRedCount));

    }

    painter->drawRect(0,0,mImage->rect().width()-1,mImage->height()-1);

    painter->end();

}

double Series::getMaboveTotalHourRSI() const
{
    return maboveTotalHourRSI;
}


} // namespace Series
