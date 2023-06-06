#ifndef BINANCE_PUBLIC_WEBSOCKETAPI_AGGREGATE_H
#define BINANCE_PUBLIC_WEBSOCKETAPI_AGGREGATE_H

#include <QJsonObject>

namespace Binance {
namespace Public {
namespace WebSocketAPI {

class Aggregate : public QJsonObject
{
public:
    Aggregate();
    Aggregate( const QJsonObject &other );

    qint64 eventTime() const;
    double price() const;
    double quantity() const;
    qint64 tradeTime() const;
    bool isMaker() const;
};

} // namespace WebSocketAPI
} // namespace Public
} // namespace Binance

#endif // BINANCE_PUBLIC_WEBSOCKETAPI_AGGREGATE_H
