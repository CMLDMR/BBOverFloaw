#include "pairtableitem.h"

#include <QPainter>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QTimer>
#include <QRandomGenerator>
#include "global/alarmwidget.h"


namespace Main {

PairTableItem::PairTableItem(const QString &pair)
    :mPair(pair)
{

    mBollinger5m = new Indicator_legacy::Bollinger(mSeries5m);

    mSeries5m = new Series_Legacy(mPair,"5m");
    mLastSeries = mSeries5m;

    mSeriesList.push_back(new Series_Legacy(mPair,"1m"));
//    mSeriesList.push_back(new Series_Legacy(mPair,"3m"));

    mSeriesList.push_back(mSeries5m);

//    mSeries15m = new Series(mPair,"15m");
    mSeriesList.push_back(new Series_Legacy(mPair,"15m"));
//    mSeriesList.push_back(new Series_Legacy(mPair,"30m"));
    mSeriesList.push_back(new Series_Legacy(mPair,"1h"));
    mSeriesList.push_back(new Series_Legacy(mPair,"4h"));
//    mSeriesList.push_back(new Series(mPair,"12h"));
    mSeriesList.push_back(new Series_Legacy(mPair,"1d"));
//    mSeriesList.push_back(new Series_Legacy(mPair,"1w"));

    canRequst = false;

//    mTimerId = this->startTimer(1000);

    mTimer = new QTimer();
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

    mTimer->start(100);

}




QRectF PairTableItem::boundingRect() const
{
    return QRectF(-1,-1,mWidth,mHeight);
}

void PairTableItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{



    if( mWillRemove ) return;
    if( selectedItem() ){
        painter->fillRect(boundingRect(),QColor(175,175,175));
    }else{
        painter->fillRect(boundingRect(),Qt::white);
    }

    if( mAlarmActivated ){
        painter->fillRect(boundingRect(),QColor(255,colorGradient,colorGradient));
    }

    painter->setPen(QPen(Qt::gray));

    painter->drawRect(boundingRect());

    if( mLastSeries == nullptr ) return;

    painter->setPen(QPen(Qt::black));

    auto fontMetric = painter->fontMetrics();
    QRectF symbolRect(0,0,fontMetric.boundingRect(mPair).width(),fontMetric.boundingRect(mPair).height());
    painter->fillRect(symbolRect,QColor(190,190,190));
    painter->drawText(symbolRect,mPair);

    if( mLastSeries->getSeries().size() ){
        auto pen = painter->font();
        painter->setFont(QFont("Tahoma",12));
        painter->drawText(0,50,mLastSeries->lastCandle().closeStr());
        painter->setFont(pen);
    }

    int i = 1;
    double upperPercent = 0;
    double downPercent = 0;

    int width = 40;
    int offset = 50;

    for( const auto &series : mSeriesList ){

        auto StaticInterval = series->timeInterval();

        for( const auto &[interval,tup] : series->valueList() ){

            if( interval == StaticInterval ){
                auto timeStr = QDateTime::fromMSecsSinceEpoch(series->lastCloseTimeEpoch()).time().toString("hh:mm:ss");
                QRectF timeRect(2,symbolRect.height()+3,fontMetric.boundingRect(timeStr).width()+3,fontMetric.boundingRect(timeStr).height()+3);
                painter->fillRect(timeRect,QColor(225,225,225));
                painter->drawText(timeRect,timeStr);

                auto &[upper,down,close] = tup;

                if( down == 0 || upper == 0 ) return;

                QRectF bolliger1m(i*(width+2)+offset,0,width,15);
                if( interval == mLastInterval ){
                    painter->fillRect(bolliger1m,QColor(25,25,25));
                }else{
                    painter->fillRect(bolliger1m,QColor(190,190,190));
                }

                auto pen = painter->pen();

                painter->setPen(QPen(Qt::white));
                painter->drawText(bolliger1m,interval);
                painter->setPen(pen);

                auto _upper = (close - upper)/upper*100;
                QRectF bolligerUpper(i*(width+2)+offset,17,width,15);
                painter->fillRect(bolligerUpper,_upper> 0 ? QColor(150,255,150) : QColor(255,255,255));
                painter->drawText(bolligerUpper,getFixedPrecision(_upper));



                auto _down = (down - close)/down*100;
                QRectF bolligerDown(i*(width+2)+offset,34,width,15);
                painter->fillRect(bolligerDown,_down > 0 ? QColor(150,255,150) : QColor(255,255,255));
                painter->drawText(bolligerDown,getFixedPrecision(_down));

                auto bollingerPercent = (upper - down)/down*100;
                QRectF bollingerPercentRect(i*(width+2)+offset,51,width,15);
                painter->drawText(bollingerPercentRect,getFixedPrecision(bollingerPercent));


                if( interval == "1m" ){
                    upperPercent += _upper;
                    downPercent += _down;
                    m1_down = _down > 0 ? true : false;
                    m1_up = _upper > 0 ? true : false;
                }if( interval == "3m" ){
                    upperPercent += _upper;
                    downPercent += _down;
                    m3_down = _down > 0 ? true : false;
                    m3_up = _upper > 0 ? true : false;
                }if( interval == "5m" ){
                    upperPercent += _upper;
                    downPercent += _down;
                    m5_down = _down > 0 ? true : false;
                    m5_up = _upper > 0 ? true : false;
                }else if( interval == "15m" ){
                    upperPercent += _upper;
                    downPercent += _down;
                    m15_down = _down > 0 ? true : false;
                    m15_up = _upper > 0 ? true : false;
                }else if( interval == "30m" ){
                    upperPercent += _upper;
                    downPercent += _down;
                    m30_down = _down > 0 ? true : false;
                    m30_up = _upper > 0 ? true : false;
                }else if( interval == "1h" ){
                    upperPercent += _upper;
                    downPercent += _down;
                    m1h_down = _down > 0 ? true : false;
                    m1h_up = _upper > 0 ? true : false;
                }else if( interval == "2h" ){
//                    upperPercent += _upper*8;
//                    downPercent += _down*8;
                }else if( interval == "4h" ){
                    upperPercent += _upper;
                    downPercent += _down;
                    m4h_down = _down > 0 ? true : false;
                    m4h_up = _upper > 0 ? true : false;
                }else if( interval == "6h" ){
//                    upperPercent += _upper*24;
//                    downPercent += _down*24;
                }else if( interval == "8h" ){
//                    upperPercent += _upper*32;
//                    downPercent += _down*32;
                }else if( interval == "12h" ){
//                    upperPercent += _upper;
//                    downPercent += _down;
                }else if( interval == "1d" ){
                    upperPercent += _upper;
                    downPercent += _down;
                    m1d_down = _down > 0 ? true : false;
                    m1d_up = _upper > 0 ? true : false;
                }else if( interval == "3d" ){
//                    upperPercent += _upper*288;
//                    downPercent += _down*288;
                }else if( interval == "1w" ){
                    upperPercent += _upper;
                    downPercent += _down;
                    m1wUpperValue = _upper;
                    m1wDownValue = _down;

                    m1w_down = _down > 0 ? true : false;
                    m1w_up = _upper > 0 ? true : false;
                }

                if( m1_up && m5_up && m15_up && m1h_up && m4h_up && m1d_up ){

                    if( interval == "1m" ){
                        if( _upper > 0.25 && bollingerPercent > 1.5 ){
                            Global::Alarm::AlarmWidget::instance()->popUpMessage(mPair + " SHORT POS " + QString("%1 $").arg(_upper));
                            mAlarmActivated = true;
                        }
                        if( _down > 0.25 && bollingerPercent > 1.5 ){
                            Global::Alarm::AlarmWidget::instance()->popUpMessage(mPair + " LONG POS " + QString("%1 $").arg(_down));
                            mAlarmActivated = true;
                        }
                    }

//                    if( m1wUpperValue != 0.0 ){
//                        Global::Alarm::AlarmWidget::instance()->popUpMessage(mPair + " SHORT " + QString("%1X").arg(static_cast<int>(100/std::abs(m1wUpperValue))));
//                    }

                }
                if( m1_down && m5_down && m15_down && m1h_down && m4h_up && m1d_up ){

                    if( interval == "1m" ){
                        if( _upper > 0.25 && bollingerPercent > 1.5 ){
                            Global::Alarm::AlarmWidget::instance()->popUpMessage(mPair + " SHORT POS " + QString("%1 $").arg(_upper));
                            mAlarmActivated = true;
                        }
                        if( _down > 0.25 && bollingerPercent > 1.5 ){
                            Global::Alarm::AlarmWidget::instance()->popUpMessage(mPair + " LONG POS " + QString("%1 $").arg(_down));
                            mAlarmActivated = true;
                        }
                    }

//                    if( m1wDownValue != 0.0 ){
//                        Global::Alarm::AlarmWidget::instance()->popUpMessage(mPair + " LONG " + QString("%1X").arg(static_cast<int>(100/std::abs(m1wDownValue))));
//                    }

                }
            }

            i++;
        }
    }


//    QRectF bolligerUpper(i*(width+2)+offset,17,width,15);
//    painter->fillRect(bolligerUpper,upperPercent > 0 ? QColor(150,255,150) : QColor(255,150,150));
//    painter->drawText(bolligerUpper,getFixedPrecision(upperPercent,0));

//    QRectF bolligerDown(i*(width+2)+offset,34,width,15);
//    painter->fillRect(bolligerDown,downPercent > 0 ? QColor(150,255,150) : QColor(255,150,150));
//    painter->drawText(bolligerDown,getFixedPrecision(downPercent,0));

//    mWidth = mWidth < i*(width+2)+offset+width +5 ? i*(width+2)+offset+width +5 : mWidth;
//    mHeight = 34+15+5;

    AbtractItem::paint(painter,option,widget);
}

QString PairTableItem::pair() const
{
    return mPair;
}

QVector<Series_Legacy *> *PairTableItem::seriesList()
{
    return &mSeriesList;
}

QString PairTableItem::getFixedPrecision(const double &value, const int &precision )
{
    int pre = precision;
    if( precision == 0 || precision > 50 ){
        return QString::number(static_cast<int>(value));
    }

    if( precision > 10 ){
        pre = 1;
    }

    std::ostringstream streamObj3;
    streamObj3 << std::fixed;
    streamObj3 << std::setprecision(pre);
    streamObj3 << value;
    return QString::fromStdString(streamObj3.str());
}

void PairTableItem::setWillRemove(bool newWillRemove)
{
    mWillRemove = newWillRemove;
}


} // namespace Main








