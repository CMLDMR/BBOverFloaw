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
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

namespace Main {

PairTableItem::PairTableItem(const QString &pair)
    :mPair(pair)
{

    //    mBollingerIntervalList.append("1m");
    //    mBollingerIntervalList.append("3m");
    mBollingerIntervalList.append("5m");
    mBollingerIntervalList.append("15m");   // 1x
    //    mBollingerIntervalList.append("30m");   // 2x
    mBollingerIntervalList.append("1h");    // 4x
    //    mBollingerIntervalList.append("2h");    // 8x
    mBollingerIntervalList.append("4h");    // 16x
    //    mBollingerIntervalList.append("6h");    // 24x
    //    mBollingerIntervalList.append("8h");    // 32x
    //    mBollingerIntervalList.append("12h");   // 48x
    mBollingerIntervalList.append("1d");    // 96x
    //    mBollingerIntervalList.append("3d");    // 288x
    mBollingerIntervalList.append("1w");    // 672x

    for( const auto &item : mBollingerIntervalList ){
        mValueList[item] = std::make_tuple(0,0,0);
    }


    mCurrentInterval = Interval::_5m;


    mBollinger5m = new Indicator::Bollinger(mSeries5m);



    mCurrentInterval = Interval::_5m;

    mSeries5m = new Series(mPair,"5m");
    mLastSeries = mSeries5m;

    mSeriesList.push_back(mSeries5m);

//    mSeries15m = new Series(mPair,"15m");
    mSeriesList.push_back(new Series(mPair,"15m"));
    mSeriesList.push_back(new Series(mPair,"1h"));
    mSeriesList.push_back(new Series(mPair,"4h"));
    mSeriesList.push_back(new Series(mPair,"12h"));
    mSeriesList.push_back(new Series(mPair,"1d"));
    mSeriesList.push_back(new Series(mPair,"1w"));


    canRequst = false;

    this->startTimer(250);



}




QRectF PairTableItem::boundingRect() const
{
    return QRectF(-1,-1,mWidth,mHeight);
}

void PairTableItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(boundingRect());

    qDebug() << mWidth << mHeight;

    if( mLastSeries == nullptr ) return;

    painter->setPen(QPen(Qt::black));


    auto fontMetric = painter->fontMetrics();
    QRectF symbolRect(0,0,fontMetric.boundingRect(mPair).width(),fontMetric.boundingRect(mPair).height());
    painter->fillRect(symbolRect,QColor(190,190,190));
    painter->drawText(symbolRect,mPair);

    if( mLastSeries->getSeries().size() ){
        auto pen = painter->font();
        painter->setFont(QFont("Tahoma",12));
        //        QRectF bolligerDown(0,0,50,15);
        //        painter->fillRect(bolligerDown,QColor(190,190,190));
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
                QRectF bolligerUpper(i*(width+2)+offset,20,width,15);
                painter->fillRect(bolligerUpper,_upper> 0 ? QColor(150,255,150) : QColor(255,150,150));
                painter->drawText(bolligerUpper,getFixedPrecision(_upper));

                auto _down = (down - close)/down*100;
                QRectF bolligerDown(i*(width+2)+offset,40,width,15);
                painter->fillRect(bolligerDown,_down > 0 ? QColor(150,255,150) : QColor(255,150,150));
                painter->drawText(bolligerDown,getFixedPrecision(_down));


                auto lastCandle = series->getSeries().last();
                auto percent = (lastCandle.close() - lastCandle.open())/lastCandle.open()*100;
                QRectF bolligerUpperPrice(i*(width+2)+offset,60,width,15);
                painter->fillRect(bolligerUpperPrice,lastCandle.close() > lastCandle.open() ? QColor(150,255,150) : QColor(255,150,150));
                painter->drawText(bolligerUpperPrice,"%"+getFixedPrecision(percent,2));

                if( interval == "15m" ){
                    upperPercent += _upper;
                    downPercent += _down;
                }else if( interval == "30m" ){
                    upperPercent += _upper*2;
                    downPercent += _down*2;
                }else if( interval == "1h" ){
                    upperPercent += _upper*4;
                    downPercent += _down*4;
                }else if( interval == "2h" ){
                    upperPercent += _upper*8;
                    downPercent += _down*8;
                }else if( interval == "4h" ){
                    upperPercent += _upper*16;
                    downPercent += _down*16;
                }else if( interval == "6h" ){
                    upperPercent += _upper*24;
                    downPercent += _down*24;
                }else if( interval == "8h" ){
                    upperPercent += _upper*32;
                    downPercent += _down*32;
                }else if( interval == "12h" ){
                    upperPercent += _upper*48;
                    downPercent += _down*48;
                }else if( interval == "1d" ){
                    upperPercent += _upper*96;
                    downPercent += _down*96;
                }else if( interval == "3d" ){
                    upperPercent += _upper*288;
                    downPercent += _down*288;
                }else if( interval == "1w" ){
                    upperPercent += _upper*672;
                    downPercent += _down*672;
                }
            }

            i++;
        }
    }


    QRectF bolligerUpper(i*(width+2)+offset,20,width,15);
    painter->fillRect(bolligerUpper,upperPercent > 0 ? QColor(150,255,150) : QColor(255,150,150));
    painter->drawText(bolligerUpper,getFixedPrecision(upperPercent/20,0));

    QRectF bolligerDown(i*(width+2)+offset,40,width,15);
    painter->fillRect(bolligerDown,downPercent > 0 ? QColor(150,255,150) : QColor(255,150,150));
    painter->drawText(bolligerDown,getFixedPrecision(downPercent/20,0));

    mWidth = mWidth < i*(width+2)+offset+width +5 ? i*(width+2)+offset+width +5 : mWidth;
    mHeight = 60+15+5;
    i++;
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


} // namespace Main




void Main::PairTableItem::timerEvent(QTimerEvent *event)
{
    switch (mCurrentInterval) {
    case Interval::_5m:
        mCurrentInterval = Interval::_15m;
        break;
    case Interval::_15m:
        mCurrentInterval = Interval::_1h;
        break;
    case Interval::_1h:
        mCurrentInterval = Interval::_4h;
        break;
    case Interval::_4h:
        mCurrentInterval = Interval::_1d;
        break;
    case Interval::_1d:
        mCurrentInterval = Interval::_1w;
        break;
    case Interval::_1w:
        mCurrentInterval = Interval::_5m;
        break;
    default:
        break;
    }

    this->update();
}


void Main::PairTableItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QMenu menu;
    menu.addAction("Open Candle Stick");
    menu.addAction("Delete Pair");
    menu.exec(event->screenPos());
    QGraphicsItem::mouseDoubleClickEvent(event);
}
