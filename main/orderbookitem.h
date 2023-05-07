#ifndef MAIN_ORDERBOOKITEM_H
#define MAIN_ORDERBOOKITEM_H

#include <QGraphicsItem>
#include <QObject>
#include <QWebSocket>
#include <QJsonArray>
#include <tuple>

namespace Main {

class Orders;

class OrderBookItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    OrderBookItem(const QString &_mPair);

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QWebSocket* mSocket;

    Orders* mAskOrders;
    Orders* mBidOrders;

    QString mPair;


};



class Orders : public QJsonArray
{
public:
    Orders();
    Orders( const QJsonArray &other );

    double price(const int &index) const;
    QString priceStr(const int &index) const;

    double qty(const int &index) const;
    QString qtyStr(const int &index) const;
    double volDollar(const int &index) const;
//    QString vol() const;

    double maxVol() const;



};


} // namespace Main

#endif // MAIN_ORDERBOOLITEM_H
