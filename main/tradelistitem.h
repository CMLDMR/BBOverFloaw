#ifndef MAIN_TRADELISTITEM_H
#define MAIN_TRADELISTITEM_H

#include <QGraphicsItem>
#include <QObject>
#include <QWebSocket>
#include <QStack>
#include "tradeitem.h"


namespace Main {


class TradeListItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    TradeListItem(const QString &_mPair);

signals:
    void ticker( const TradeItem & , const double &);

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QWebSocket* mSocket;

    QStack<TradeItem> mItemList;

    double mMaxDollar{0};

    double mAverage1000Ticker{0};

    QString mPair;



};

} // namespace Main

#endif // MAIN_TRADELISTITEM_H
