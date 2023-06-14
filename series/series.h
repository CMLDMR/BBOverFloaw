#ifndef SERIES_SERIES_H
#define SERIES_SERIES_H

#include <QObject>
#include <QImage>
#include <QPainter>

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

    QImage *image() const;

    double getM5MinunteUpperPercent() const;

    double allUpperPercent() const;

    double getM15MinunteUpperPercent() const;

    double getM1HinunteUpperPercent() const;

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

    QImage* mImage{nullptr};
    QPainter* mPainter;
    void prePareImage( QPainter* painter );
    bool mAlarmActivated{false};

    double m5MinunteUpperPercent{0};
    double m15MinunteUpperPercent{0};
    double m1HinunteUpperPercent{0};

    double mAllUpperPercent{0};

};

} // namespace Series

#endif // SERIES_SERIES_H
