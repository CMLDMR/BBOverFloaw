#ifndef MAIN_TRADEITEM_H
#define MAIN_TRADEITEM_H

#include <QJsonObject>

namespace Main {

class TradeItem : public QJsonObject
{
public:
    TradeItem();
    TradeItem( const QJsonObject &other );

    QString priceStr() const;
    double price() const;
    QString qtyStr() const;
    double qty() const;

    bool isSell() const;
    QString volDollarStr() const;
    double volDollar() const;
    QString timeStr() const;

};

} // namespace Main

#endif // MAIN_TRADEITEM_H
