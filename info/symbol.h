#ifndef EXCHANGEINFO_SYMBOL_H
#define EXCHANGEINFO_SYMBOL_H

#include <QJsonObject>

namespace ExchangeInfo {

class Symbol : public QJsonObject
{
public:
    Symbol();

    Symbol( const QJsonObject &other );

    QString getPair() const;
    QString getMarginAsset() const;
    QString getStatus() const;
    QString getQuotaAsset() const;
};

} // namespace ExchangeInfo

#endif // EXCHANGEINFO_SYMBOL_H
