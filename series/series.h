#ifndef SERIES_SERIES_H
#define SERIES_SERIES_H

#include <QObject>
#include "seri.h"
#include "binance/websocketapi/websocketapi.h"


namespace Series {

class Series : public QObject
{
    Q_OBJECT
public:
    explicit Series(const QString &_mPair, QObject *parent = nullptr);

    QVector<Seri *> seriList() const;

signals:
    void dataUpdated();


private:
    QString mPair;
    QVector<Seri*> mSeriList;
    Binance::Public::WebSocketAPI::WebSocketAPI* mSocket;

    QThread* mThread;
    void SocketWorker();
};

} // namespace Series

#endif // SERIES_SERIES_H
