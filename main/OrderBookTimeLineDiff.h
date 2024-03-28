#ifndef ORDERBOOKTIMELINEDIFF_H
#define ORDERBOOKTIMELINEDIFF_H

#include <QObject>
#include <QGraphicsItem>
#include <QList>
#include <tuple>

class OrderBookTimeLineDiff : public QObject, public QGraphicsItem
{
public:
    OrderBookTimeLineDiff();


public slots:
    void updateOrderBookVol( const qreal buySide , const qreal sellSide );


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int m_updateRate        { 0 };
    double m_buySide        { 0 };
    double m_sellSide       { 0 };
    quint64 m_updateTime    { 0 };
    int m_lastUpdateTime    { 0 };

    double m_lastBuySide        { 0 };
    double m_lastSellSide       { 0 };

    QList<std::tuple<double,double,int>> m_list;

    int m_width { 0 };
    int m_height{ 0 };
    bool firstAppen { true };

};


static QString doubleToHumanReadable(double number );

#endif // ORDERBOOKTIMELINEDIFF_H
