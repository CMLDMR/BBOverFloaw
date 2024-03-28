#include "seriitem.h"

#include "series/seri.h"

#include <iomanip>
#include <iostream>
#include<fstream>





#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>

namespace Chart {

SeriItem::SeriItem(Series::Seri *_seri, QObject *parent)
    : QObject{parent},
    mSeri(_seri)
{
    mWidth = mSeri->size() * tickerAreaWidth +100;
    QObject::connect(mSeri,&Series::Seri::updated,[=](){
        this->update();
//        this->scene()->update(this->scene()->itemsBoundingRect());
    });


    auto mTimer = new QTimer();
    QObject::connect(mTimer,&QTimer::timeout,[=](){

//        if( mAlarmActivated ){
//            colorGradient += 10;
//            if( colorGradient >= 255 ){
//                colorGradient = 0;
//                mAlarmActivated = false;
//            }

//        }

        this->update();
    });

    mTimer->start(100);

}

std::tuple<QRectF, QLineF, Qt::GlobalColor> SeriItem::candle(const int &index) const
{
    auto min = mSeri->minPrice();
    auto max = mSeri->maxPrice();

    auto close = mSeri->close(index);
    auto open = mSeri->open(index);
    auto high = mSeri->high(index);
    auto low = mSeri->low(index);

    if( close >= open ){

        qreal xPos = index * tickerAreaWidth+2;
        qreal yPos = mInfoHeight+mHeight - (open - min)/(max-min)*mHeight;
        qreal width = tickerAreaWidth-2;
        qreal height = (open -close)/(max-min)*mHeight;

        qreal _high = mInfoHeight+mHeight-(high  - min)/(max-min)*mHeight;
        qreal _low = mInfoHeight+mHeight-(low  - min)/(max-min)*mHeight;

        return std::make_tuple(QRectF(xPos,yPos,width,height),QLineF(xPos+tickerAreaWidth/2-1,_high,xPos+tickerAreaWidth/2-1,_low),Qt::green);
    }else{
        qreal xPos = index * tickerAreaWidth+2;
        qreal yPos = mInfoHeight+mHeight - (close - min)/(max-min)*mHeight;
        qreal width = tickerAreaWidth-2;
        qreal height = (close - open)/(max-min)*mHeight;

        qreal _high = mInfoHeight+mHeight-(high  - min)/(max-min)*mHeight;
        qreal _low = mInfoHeight+mHeight-(low  - min)/(max-min)*mHeight;

        return std::make_tuple(QRectF(xPos,yPos,width,height),QLineF(xPos+tickerAreaWidth/2-1,_high,xPos+tickerAreaWidth/2-1,_low),Qt::red);
    }




}

std::tuple<QRectF,QRectF,QRectF, Qt::GlobalColor> SeriItem::volume(const int &index) const
{

    qreal max = mSeri->at(0).volume();
    for( int i = 0 ; i < mSeri->size() ; i++ ){
        auto item = mSeri->at(i);
        if( item.volume() > max ) max = item.volume();
    }

    auto close = mSeri->close(index);
    auto open = mSeri->open(index);


    auto _volumeYAx = mInfoHeight+mHeight+mVolumeHeight;

    qreal xPos = index * tickerAreaWidth+1;
    qreal yPos = _volumeYAx - (mSeri->volume(index))/max*mVolumeHeight;
    qreal width = tickerAreaWidth-1;
    qreal height = mSeri->volume(index)/max*mVolumeHeight;

    Qt::GlobalColor color = close >= open ? Qt::darkGreen : Qt::darkRed;

    qreal bYpos = _volumeYAx - mSeri->takerVolume(index)/max*mVolumeHeight;
    qreal bheight = mSeri->takerVolume(index)/max*mVolumeHeight;

    qreal sYpos = _volumeYAx - (mSeri->volume(index)-mSeri->takerVolume(index))/max*mVolumeHeight;
    qreal sheight = height-bheight;

    return std::make_tuple(QRectF(xPos,yPos,width,height),
                           QRectF(xPos,bYpos,width/2,bheight),
                           QRectF(xPos+width/2,sYpos,width/2,sheight)
                           ,color);


}

QPointF SeriItem::volumeDif(const int &index)
{
    QVector<double> volDif;
    qreal maxVol = 0;
    qreal minVol = 0;

    qreal currentmakerVol = 0;

    for( int i = 0 ; i < mSeri->size() ; i++ ){



        if( i == 0 ){
            auto makerVol = mSeri->volume(i) - mSeri->takerVolume(i)-mSeri->takerVolume(i);
            volDif.append(makerVol);
            maxVol = makerVol;
            minVol = makerVol;
        }else{
            auto makerVol =volDif.last()+ mSeri->volume(i) - mSeri->takerVolume(i)-mSeri->takerVolume(i);
            volDif.append(makerVol);
            maxVol = maxVol < makerVol ? makerVol : maxVol;
            minVol = minVol > makerVol ? makerVol : minVol;;
        }

        if( i < index ){
            currentmakerVol = volDif.last();
        }
    }

    qreal xPos = index * tickerAreaWidth+2;
    qreal yPos = mInfoHeight+mHeight+mVolumeHeight+/*mQuotaVolumeHeight-*/(currentmakerVol  - minVol)/(maxVol-minVol)*mQuotaVolumeHeight;

    return QPointF(xPos+tickerAreaWidth/2-1,yPos);
}

QString SeriItem::Readable(const double sayi)
{

    std::stringstream out;

    if( sayi > 1000000000 ){

        auto newSayi = sayi /1000000000;
        out << std::fixed << std::setprecision(3) << newSayi;
        return QString::fromStdString(out.str())+"G";
    }else if( sayi > 1000000 ){
        auto newSayi = sayi /1000000;
        out << std::fixed << std::setprecision(3) << newSayi;
        return QString::fromStdString(out.str())+"M";
    }else if( sayi > 1000 ){
        auto newSayi = sayi/1000;
        out << std::fixed << std::setprecision(3) << newSayi;
        return QString::fromStdString(out.str())+"K";
    }else{
        auto newSayi = sayi;
        out << std::fixed << std::setprecision(0) << newSayi;
        return QString::fromStdString(out.str());
    }
}

QString SeriItem::countDown()
{
    //TODO: Kalan Süre Gün:Saat:Dakika:Saniye Olarak Hesaplanacak
    int gun, saat, dakika, saniye;
    int kalanSure;
    int toplamSure = (mSeri->closeTime()-mSeri->last().eventTime())/1000;

    gun = toplamSure / (24 * 60 * 60); // Toplam saniyeyi güne çevirme
    kalanSure = toplamSure % (24 * 60 * 60); // Günlere çevrilmemiş kalan saniye

    saat = kalanSure / (60 * 60); // Kalan saniyeyi saate çevirme
    kalanSure = kalanSure % (60 * 60); // Saatlere çevrilmemiş kalan saniye

    dakika = kalanSure / 60; // Kalan saniyeyi dakikaya çevirme
    saniye = kalanSure % 60; // Dakikalara çevrilmemiş kalan saniye

    auto gunStr = gun == 0 ? "" : ( gun < 10 ? QString("0%1:").arg(gun) : QString("%1:").arg(gun));
    auto saatStr = saat == 0 ? "" : ( saat < 10 ? QString("0%1:").arg(saat) : QString("%1:").arg(saat));
    auto dakikaStr = dakika == 0 ? "00:" : ( dakika < 10 ? QString("0%1:").arg(dakika) : QString("%1:").arg(dakika));
    auto saniyeStr = saniye == 0 ? "00" : ( saniye < 10 ? QString("0%1").arg(saniye) : QString("%1").arg(saniye));


    return gunStr+saatStr+dakikaStr+saniyeStr;
//    return QString("%1:%2:%3:%4").arg(gun).arg(saat).arg(dakika).arg(saniye);
}

void SeriItem::drawGrid(QPainter *painter)
{

    auto min = mSeri->minPrice();
    auto max = mSeri->maxPrice();

    auto dif = max - min;
    auto step = dif/5.;
    auto pen = painter->pen();
    painter->setPen(QPen(QColor(200,200,200),1,Qt::DotLine));
    for( int i = 1 ; i <= 5 ; i++ ){
        auto yPos = mInfoHeight+(dif-i*step)/dif*mHeight;
        painter->drawLine(0,yPos,mWidth,yPos);
        painter->drawText(mWidth-50,yPos+14,QString("%1").arg(i*step+min));
    }

    for( int i = 0 ; i <= mSeri->size() ; i +=10 ){
        painter->drawLine(i*tickerAreaWidth,mInfoHeight,i*tickerAreaWidth,mHeight+mInfoHeight);
    }

    painter->setPen(pen);

}

void SeriItem::drawNumberOfTrade(QPainter *painter)
{

    {
        auto maxTrade = static_cast<double>(mSeri->at(0).numberOfTrades());
        auto minTrade = static_cast<double>(mSeri->at(0).numberOfTrades());
        for( int i = 0 ; i < mSeri->size() ; i++ ){
            auto item = mSeri->at(i);
            maxTrade = maxTrade < item.numberOfTrades() ? item.numberOfTrades() : maxTrade;
            minTrade = minTrade > item.numberOfTrades() ? item.numberOfTrades() : minTrade;
        }


        auto _volumeYAx = mInfoHeight+mHeight+mVolumeHeight+2*mNumberTradeHeight;

        for( int i = 0 ; i < mSeri->size() ; i++ ){

            auto numTrade = static_cast<double>(mSeri->numberOfTrade(i));
            qreal xPos = i * tickerAreaWidth+1;
            qreal yPos = _volumeYAx - (numTrade)/(maxTrade-minTrade)*mNumberTradeHeight;
            qreal width = tickerAreaWidth-1;
            qreal height = numTrade/(maxTrade-minTrade)*mNumberTradeHeight;
            painter->fillRect(QRectF(xPos,yPos,width,height),Qt::green);
        }
    }

    { //TODO: Bu Kısım Scale Düngün Değil. Alanın Dışında Çizimler Yapıyor
        auto maxTrade = mSeri->at(0).volume()/static_cast<double>(mSeri->at(0).numberOfTrades());
        auto minTrade = mSeri->at(0).volume()/static_cast<double>(mSeri->at(0).numberOfTrades());
        for( int i = 0 ; i < mSeri->size() ; i++ ){
            auto item = mSeri->at(i);
            auto rate = item.volume()/static_cast<double>(item.numberOfTrades());
            maxTrade = maxTrade < rate ? rate : maxTrade;
            minTrade = minTrade > rate ? rate : minTrade;
        }

        auto _volumeYAx = mInfoHeight+mHeight+mVolumeHeight+2*mNumberTradeHeight;

        for( int i = 0 ; i < mSeri->size()-1 ; i++ ){
            auto item = mSeri->at(i);
            auto rate = item.volume()/static_cast<double>(item.numberOfTrades());
            qreal xPos = i * tickerAreaWidth+1;
            qreal yPos = _volumeYAx - (rate-minTrade)/(maxTrade-minTrade)*mNumberTradeHeight;
            qreal width = tickerAreaWidth/2-1;
            qreal height = (rate-minTrade)/(maxTrade-minTrade)*mNumberTradeHeight;
            painter->fillRect(QRectF(xPos,yPos,width,height),Qt::red);
        }
    }

}



} // namespace Chart


QRectF Chart::SeriItem::boundingRect() const
{
    return QRectF( 0 , 0 , mWidth , mHeight+mInfoHeight+mVolumeHeight+mQuotaVolumeHeight );
}

void Chart::SeriItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->fillRect(QRectF(0,0,mWidth,mInfoHeight),QColor(25,25,25));
    auto pen = painter->pen();
    painter->setPen(QPen(Qt::white));
    auto font = painter->font();
    painter->setFont(QFont("Tahoma",11,1));
    painter->drawText(3,13,mSeri->pair() + " " + mSeri->interval() + " O:"+QString("%1 H:%2 L:%3 C:%4").arg(mSeri->open()).arg(mSeri->high()).arg(mSeri->low()).arg(mSeri->close()));
    painter->setFont(font);
    painter->setPen(pen);




    drawGrid(painter);


    for( int i = 0 ; i < mSeri->size() ; i++ ){
        auto [rect,line,color] = candle(i);
        painter->fillRect(rect,color);
        painter->drawText(rect,QString::number(i));
        auto pen = painter->pen();
        painter->setPen(QPen(color));
        painter->drawLine(line);
        painter->setPen(pen);
    }



    {
        painter->fillRect(QRectF(0,mInfoHeight+mHeight,mWidth,mVolumeHeight),QColor(220,220,220));
        painter->drawText(0,mInfoHeight+mHeight+14,"Volume Base: " + Readable(mSeri->volume()) + " S:"+Readable(mSeri->volume()-mSeri->takerVolume()));

        for( int i = 0 ; i < mSeri->size() ; i++ ){
            auto [rect,rectbuy,rectsell,color] = this->volume(i);
            painter->fillRect(rect,color);
            painter->fillRect(rectbuy,Qt::green);
            painter->fillRect(rectsell,Qt::red);
        }
    }

    {
        painter->fillRect(QRectF(0,mInfoHeight+mHeight+mVolumeHeight,mWidth,mVolumeHeight),Qt::GlobalColor::lightGray);
        painter->drawText(0,mInfoHeight+mHeight+mVolumeHeight+14,"Volume Dif :" + Readable(mSeri->takerVolume() - (mSeri->volume() - mSeri->takerVolume())));

        for( int i = 1 ; i < mSeri->size() ; i++ ){
            painter->drawLine(QLineF(this->volumeDif(i-1),this->volumeDif(i)));
        }
    }


    {
        auto min = mSeri->minPrice();
        auto max = mSeri->maxPrice();
        auto close = mSeri->close();
        auto yPos = mInfoHeight+mHeight - (close - min)/(max-min)*mHeight;
        yPos = yPos < 28 ? 28 : yPos;
        painter->drawText(mSeri->size() * tickerAreaWidth+10,yPos,QString::number(mSeri->close()));
        painter->drawText(mSeri->size() * tickerAreaWidth+10,yPos+14,countDown());//QString::number(mSeri->duration()/1000-(mSeri->last().eventTime()%60000)/1000));
    }


    // drawNumberOfTrade(painter);


    painter->drawRect(boundingRect());

}
