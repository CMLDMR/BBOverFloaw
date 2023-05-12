#include "symbol.h"

namespace ExchangeInfo {

Symbol::Symbol()
{

}

Symbol::Symbol(const QJsonObject &other)
{
    for( const auto &key : other.keys() ){
        this->insert(key,other[key]);
    }
}

QString Symbol::getPair() const
{
    return value("pair").toString();
}

QString Symbol::getMarginAsset() const
{
    return value("marginAsset").toString();
}

QString Symbol::getStatus() const
{
    return value("status").toString();
}

QString Symbol::getQuotaAsset() const
{
    return value("quoteAsset").toString();
}

} // namespace ExchangeInfo
