#ifndef BINANCE_PUBLIC_WEBSOCKETAPI_WEBSOCKETAPI_H
#define BINANCE_PUBLIC_WEBSOCKETAPI_WEBSOCKETAPI_H

#include <QObject>
#include <QThread>
#include <QWebSocket>

#include "binance/kline.h"


namespace Binance {
namespace Public {
namespace WebSocketAPI {

class WebSocketAPI : public QObject
{
    Q_OBJECT
public:

    static WebSocketAPI* createSocket( const QString &pair );

    void startAggregateStream();

signals:
    void receivedKLine(const Binance::Public::KLine &);


private:

    explicit WebSocketAPI(const QString &pair,QObject *parent = nullptr);

    QString mPair;
    QThread* mThread;
    QWebSocket* mSocket;
    void startedSocket();
    Binance::Public::KLine mLastKLine;
};

} // namespace WebSocketAPI
} // namespace Public
} // namespace Binance

#endif // BINANCE_PUBLIC_WEBSOCKETAPI_WEBSOCKETAPI_H
