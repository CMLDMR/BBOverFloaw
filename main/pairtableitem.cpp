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


namespace Main {

PairTableItem::PairTableItem(const QString &pair)
    :mPair(pair)
{

    mBollinger5m = new Indicator::Bollinger(mSeries5m);

    mSeries5m = new Series(mPair,"5m");
    mLastSeries = mSeries5m;

    mSeriesList.push_back(new Series(mPair,"1m"));

    mSeriesList.push_back(mSeries5m);

//    mSeries15m = new Series(mPair,"15m");
    mSeriesList.push_back(new Series(mPair,"15m"));
    mSeriesList.push_back(new Series(mPair,"1h"));
    mSeriesList.push_back(new Series(mPair,"4h"));
    mSeriesList.push_back(new Series(mPair,"12h"));
    mSeriesList.push_back(new Series(mPair,"1d"));
    mSeriesList.push_back(new Series(mPair,"1w"));

    canRequst = false;

    mTimerId = this->startTimer(1000);

}




QRectF PairTableItem::boundingRect() const
{
    return QRectF(-1,-1,mWidth,mHeight);
}

void PairTableItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if( mWillRemove ) return;
    if( selectedItem() ){
        painter->fillRect(boundingRect(),QColor(225,225,225));
    }else{
        painter->fillRect(boundingRect(),Qt::white);
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
                painter->fillRect(bolligerUpper,_upper> 0 ? QColor(150,255,150) : QColor(255,150,150));
                painter->drawText(bolligerUpper,getFixedPrecision(_upper));



                auto _down = (down - close)/down*100;
                QRectF bolligerDown(i*(width+2)+offset,34,width,15);
                painter->fillRect(bolligerDown,_down > 0 ? QColor(150,255,150) : QColor(255,150,150));
                painter->drawText(bolligerDown,getFixedPrecision(_down));


                if( interval == "5m" ){
                    upperPercent += _upper;
                    downPercent += _down;
                }else if( interval == "15m" ){
                    upperPercent += _upper*2;
                    downPercent += _down*2;
                }else if( interval == "30m" ){
//                    upperPercent += _upper*2;
//                    downPercent += _down*2;
                }else if( interval == "1h" ){
                    upperPercent += _upper*4;
                    downPercent += _down*4;
                }else if( interval == "2h" ){
//                    upperPercent += _upper*8;
//                    downPercent += _down*8;
                }else if( interval == "4h" ){
                    upperPercent += _upper*8;
                    downPercent += _down*8;
                }else if( interval == "6h" ){
//                    upperPercent += _upper*24;
//                    downPercent += _down*24;
                }else if( interval == "8h" ){
//                    upperPercent += _upper*32;
//                    downPercent += _down*32;
                }else if( interval == "12h" ){
                    upperPercent += _upper*16;
                    downPercent += _down*16;
                }else if( interval == "1d" ){
                    upperPercent += _upper*32;
                    downPercent += _down*32;
                }else if( interval == "3d" ){
//                    upperPercent += _upper*288;
//                    downPercent += _down*288;
                }else if( interval == "1w" ){
                    upperPercent += _upper*64;
                    downPercent += _down*64;
                }
            }

            i++;
        }
    }


    QRectF bolligerUpper(i*(width+2)+offset,17,width,15);
    painter->fillRect(bolligerUpper,upperPercent > 0 ? QColor(150,255,150) : QColor(255,150,150));
    painter->drawText(bolligerUpper,getFixedPrecision(upperPercent/20,0));

    QRectF bolligerDown(i*(width+2)+offset,34,width,15);
    painter->fillRect(bolligerDown,downPercent > 0 ? QColor(150,255,150) : QColor(255,150,150));
    painter->drawText(bolligerDown,getFixedPrecision(downPercent/20,0));

    mWidth = mWidth < i*(width+2)+offset+width +5 ? i*(width+2)+offset+width +5 : mWidth;
    mHeight = 34+15+5;

    AbtractItem::paint(painter,option,widget);
}

QString PairTableItem::pair() const
{
    return mPair;
}

QVector<Series *> *PairTableItem::seriesList()
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




void Main::PairTableItem::timerEvent(QTimerEvent *event)
{
    this->update();
}



