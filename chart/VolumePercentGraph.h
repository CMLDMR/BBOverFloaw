#ifndef VOLUMEPERCENTGRAPH_H
#define VOLUMEPERCENTGRAPH_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "binance/websocketapi/aggregate.h"

#include <vector>

namespace Series{
class Series;
class Seri;
};


struct Candle {
    double close = 0;
    double high = 0;
    double low = 0;
    double open = 0;
    double buyVolume = 0;
    double sellVolume = 0;

    double buyPercent() const {
        return buyVolume / ( buyVolume + sellVolume );
    }



    void nextCandle(){
        open = close;
        high = close;
        low = close;
        buyVolume = 0;
        sellVolume = 0;
    }

    bool isVolumeOver(){
        return ( (buyVolume + sellVolume) > 5000000 );
    }

    void update( const Binance::Public::WebSocketAPI::Aggregate &aggregate );
};

class VolumePercentGraph : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    VolumePercentGraph( const QString &_mPair );

    void addAggregate( const Binance::Public::WebSocketAPI::Aggregate &aggregate );

private:
    QString m_pair;

    qreal m_height{ 480 };
    qreal m_width{ 640 };

    std::vector<Candle> m_candleList;

    Candle m_candle;

    bool getNextCandle{ false };



    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};



class VolumePercentGraphWidget : public QGraphicsView
{
    Q_OBJECT
public:
    VolumePercentGraphWidget(Series::Series* _series ,  QWidget * parent = nullptr );


    QString pair() const;
    void setPair(const QString &newPair);

private:
    QString          m_pair;
    QGraphicsScene  *m_scene;

    Series::Series* m_series;

    VolumePercentGraph* m_volumePercentGraph { nullptr };
};

#endif // VOLUMEPERCENTGRAPH_H
