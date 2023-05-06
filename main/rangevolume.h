#ifndef MAIN_RANGEVOLUME_H
#define MAIN_RANGEVOLUME_H

#include <QGraphicsItem>
#include <QObject>
#include <QVector>

#include "tradeitem.h"



namespace Main {

class RangeVolume : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    RangeVolume();

    void setRangeValue( const double &value );

public slots:

    void addTicker( const TradeItem &item );


private:
    QVector<TradeItem> mTradeList;
    double mRangeValue;


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

} // namespace Main

#endif // MAIN_RANGEVOLUME_H
