#ifndef BINANCE_PUBLIC_RESTAPI_SYMBOL_H
#define BINANCE_PUBLIC_RESTAPI_SYMBOL_H

#include <QJsonObject>

namespace Binance {
namespace Public {
namespace RestAPI {

class Symbol : public QJsonObject
{
public:
    Symbol();
    Symbol(const QJsonObject &other);

    QString baseAsset() const;
    int baseAssetPrecision() const;
    QString contractType() const;
    qulonglong deliveryDate() const;

    //filter

    QString pair() const;
    int pricePrecision() const;
    int quantityPrecision() const;
    QString quoteAsset() const;
    int quotePrecision() const;

    QString status() const;
    QString symbol() const;

};

} // namespace RestAPI
} // namespace Public
} // namespace Binance

#endif // BINANCE_PUBLIC_RESTAPI_SYMBOL_H
