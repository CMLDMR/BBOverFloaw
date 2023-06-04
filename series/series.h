#ifndef SERIES_SERIES_H
#define SERIES_SERIES_H

#include <QObject>
#include "seri.h"
#include "binance/websocketapi/websocketapi.h"

#include <optional>


namespace Series {

class Series : public QObject
{
    Q_OBJECT
public:
    explicit Series(const QString &_mPair, QObject *parent = nullptr);

    QVector<Seri *> seriList() const;

    const double &close() const;

    QString timeStr() const;

    QString pair() const;

    std::optional<Seri*> getSeri( const QString &interval );

signals:
    void dataUpdated(const bool&);


private:
    QString mPair;
    QVector<Seri*> mSeriList;
    Binance::Public::WebSocketAPI::WebSocketAPI* mSocket;

    QThread* mThread;
    void SocketWorker();

    double mClose;
    QString mTimeStr;

};

} // namespace Series

#endif // SERIES_SERIES_H
