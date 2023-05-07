#ifndef MAIN_RANGEVOLUME_H
#define MAIN_RANGEVOLUME_H

#include <QGraphicsItem>
#include <QObject>
#include <QMap>

#include "tradeitem.h"



namespace Main {

class RangeItem;

class RangeVolume : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    RangeVolume();

    void setRangeValue( const double &value );

public slots:

    void addTicker( const TradeItem &item , const double &average);


private:
    QMap<double,RangeItem> mTradeList;

    double mLastAverage{1};
    qulonglong mLastKey;

    double mTotalBuy{0};
    double mTotalSell{0};


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};


class RangeItem{
public:
    RangeItem();

    RangeItem &operator+=( const TradeItem &item );

    double buy() const;

    double sell() const;

    bool lastIsBuy() const;

    double lastQty() const;

private:
    bool mLastIsBuy;
    double mBuy{0};
    double mSell{0};
    double mLastQty{0};
};

} // namespace Main

#endif // MAIN_RANGEVOLUME_H
