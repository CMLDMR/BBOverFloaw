#ifndef CHART_SERIITEM_H
#define CHART_SERIITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <tuple>

namespace Series{
class Seri;
};

namespace Chart {

class SeriItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit SeriItem(Series::Seri* _seri , QObject *parent = nullptr);

signals:

    void updated();


private:
    Series::Seri* mSeri;

    qreal mWidth{50};
    const qreal mHeight{200};
    qreal mInfoHeight{16};
    const qreal mVolumeHeight{75};
    const qreal mQuotaVolumeHeight{75};
    const qreal mNumberTradeHeight{75};
    const qreal mVolumeCandleStickHeight{mHeight};

    bool enableVolume     { true };
    bool enableQuotaVolume{ true };
    bool enableNumberTrade{ false };
    bool enableVolumeCandle { true };


    const qreal tickerAreaWidth{7};


    std::tuple<QRectF,QLineF,Qt::GlobalColor> candle(const int &index) const;
    std::tuple<QRectF,QLineF,Qt::GlobalColor> volumeCandle(const int &index) const;

    std::tuple<QRectF, QRectF, QRectF, Qt::GlobalColor> volume(const int &index) const;
    QPointF volumeDif( const int &index );

    QString Readable(const double sayi);
    QString countDown();


    void drawGrid(QPainter* painter);
    void drawNumberOfTrade(  QPainter* painter );


    double m_lastDollarOpen = 0;
    double m_lastBuyDollarHigh = 0;
    double m_lastDollarClose = 0;
    double m_lastDollarLow = 0;

    void drawVolumeCandle (  QPainter* painter );



    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

} // namespace Chart

#endif // CHART_SERIITEM_H
