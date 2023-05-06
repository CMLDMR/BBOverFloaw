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
    QString qtyStr() const;
    bool isSell() const;
    QString volDollarStr() const;
    double volDollar() const;
    QString timeStr() const;

};

} // namespace Main

#endif // MAIN_TRADEITEM_H
