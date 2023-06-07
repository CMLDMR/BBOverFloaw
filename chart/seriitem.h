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


private:
    Series::Seri* mSeri;

    qreal mWidth{40};
    const qreal mHeight{200};
    qreal mInfoHeight{16};
    const qreal mVolumeHeight{75};
    const qreal mQuotaVolumeHeight{75};

    const qreal tickerAreaWidth{7};


    std::tuple<QRectF,QLineF,Qt::GlobalColor> candle(const int &index) const;
    std::tuple<QRectF, QRectF, QRectF, Qt::GlobalColor> volume(const int &index) const;
    QPointF volumeDif( const int &index );

    QString Readable(const double sayi);


    void drawGrid(QPainter* painter);


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

} // namespace Chart

#endif // CHART_SERIITEM_H
