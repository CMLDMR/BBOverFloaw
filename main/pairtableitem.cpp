#include "pairtableitem.h"

#include <QPainter>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

namespace Main {

PairTableItem::PairTableItem()
{

    mAccessManager = new QNetworkAccessManager();

    QObject::connect(mAccessManager,&QNetworkAccessManager::finished,[=](QNetworkReply* reply){
        auto array = QJsonDocument::fromJson(reply->readAll()).array();
        for( const auto &item : array ){
            CandleItem _item = item.toArray();
            mCandles.push_back(_item);
        }
        this->update(boundingRect());
    });
    mAccessManager->get(QNetworkRequest(QUrl("https://fapi.binance.com/fapi/v1/continuousKlines?pair=BTCUSDT&contractType=PERPETUAL&interval=15m&limit=250")));
}

CandleItem::CandleItem(const QJsonArray &other)
    :QJsonArray(other)
{

}


QRectF PairTableItem::boundingRect() const
{
    return QRectF(0,0,2000,500);
}

void PairTableItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(boundingRect());

    double max{0};
    double min{1000000000};
    for( const auto &item : mCandles ){
        max = item.high() > max ? item.high() : max;
        min = item.low() < min ? item.low() : min;
    }

    qDebug() << "Painter " << mCandles.size();
    int i = 480;
    int index = 0;
    for( const auto &item : mCandles ){

        QColor color;
        if( item.close() < item.open() ){
            color = QColor(255,25,25);
        }else{
            color = QColor(25,255,25);
        }

        auto xPos = index*8;
        auto yPos = boundingRect().height()-(item.open()-min)/(max-min)*boundingRect().height();
        auto width = 7;
        auto height = -(item.close()-item.open())/(max-min)*boundingRect().height();

        auto rect = QRectF(xPos,yPos,width,height);

        painter->fillRect(rect,color);

//        painter->setFont(QFont("Tahoma",7));
//        QPen pen;
//        if( i % 2 == 0 ){
//            painter->drawText(xPos,20,item.closeTime().toString("hh:mm"));
//        }else{
//            painter->drawText(xPos,20,item.closeTime().toString("hh:mm"));
//        }

        yPos = boundingRect().height()-(item.low()-min)/(max-min)*boundingRect().height();
        auto yPos1 = boundingRect().height()-(item.high()-min)/(max-min)*boundingRect().height();

        painter->setPen(QPen(color));
        painter->drawLine(xPos+width/2,yPos,xPos+width/2,yPos1);


        auto [upper,mid,lower] = this->getBollinger(index);

        auto midYpos = boundingRect().height()-(mid-min)/(max-min)*boundingRect().height();
        qDebug() << upper << mid << lower;
        painter->setPen(QPen(QColor(0,200,255)));
        painter->drawLine(xPos-2,midYpos,xPos+2,midYpos);

        midYpos = boundingRect().height()-(upper-min)/(max-min)*boundingRect().height();
        painter->drawLine(xPos-2,midYpos,xPos+2,midYpos);
        midYpos = boundingRect().height()-(lower-min)/(max-min)*boundingRect().height();
        painter->drawLine(xPos-2,midYpos,xPos+2,midYpos);

        i++;
        index++;
    }

}

double PairTableItem::getDerivation(const int &index)
{
    if( index >= mCandles.size() ) return 0;
    if( index < 21 ) return 0;
    double sum{0};
    double mean{0};

    for( int i = index-21 ; i < index ; i++ ){
        auto item = mCandles[i];
        sum += (item.close()+item.high()+item.low())/3;
    }

    mean = sum / 21.;

    double standardDeviation{0};

    for( int i = index-21 ; i < index ; i++ ){
        auto item = mCandles[i];
        auto val = (item.close()+item.high()+item.low())/3;
        standardDeviation += std::pow(val-mean,2);
    }

    return std::sqrt(standardDeviation / 21);
}

std::tuple<double, double, double> PairTableItem::getBollinger(const int &index)
{
    if( index >= mCandles.size() ) return std::make_tuple(0,0,0);
    if( index < 21 ) return std::make_tuple(0,0,0);

    double sum{0};
    double movingAverage{0};

    for( int i = index-21 ; i < index ; i++ ){
        auto item = mCandles[i];
        sum += (item.close()+item.high()+item.low())/3;
    }
    movingAverage = sum / 21.0;

    auto derivation = getDerivation(index);

    return std::make_tuple(movingAverage+2*derivation,movingAverage,movingAverage-2*derivation);
}






qulonglong CandleItem::openTime() const
{
    return this->at(0).toVariant().toULongLong();
}

QString CandleItem::openStr() const
{
    return this->at(1).toString();
}

double CandleItem::open() const
{
    return openStr().toDouble();
}

QString CandleItem::highStr() const
{
    return this->at(2).toString();
}

double CandleItem::high() const
{
    return this->highStr().toDouble();
}

QString CandleItem::lowStr() const
{
    return this->at(3).toString();
}

double CandleItem::low() const
{
    return this->lowStr().toDouble();
}

QString CandleItem::closeStr() const
{
    return this->at(4).toString();
}

double CandleItem::close() const
{
    return this->closeStr().toDouble();
}

QString CandleItem::volumeStr() const
{
    return this->at(5).toString();
}

QString CandleItem::assetVolume() const
{
    return this->at(7).toString();
}

qulonglong CandleItem::closeTimeLong() const
{
    return this->at(6).toVariant().toULongLong();
}

QTime CandleItem::closeTime() const
{
    return QDateTime::fromMSecsSinceEpoch(this->closeTimeLong()).time();
}

qulonglong CandleItem::numberOfTrade() const
{
    return this->at(8).toVariant().toULongLong();
}

QString CandleItem::buyVolumeStr() const
{
    return this->at(9).toString();
}

QString CandleItem::buyAssetVolumeStr() const
{
    return this->at(10).toString();
}



} // namespace Main


