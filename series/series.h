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

    double getM4HinunteUpperPercent() const;

    double getM1DinunteUpperPercent() const;

    double getM5MDownPercent() const;

    void setM15MinunteUpperPercent(double newM15MinunteUpperPercent);

    double getM15MDownPercent() const;
    double getM1HDownPercent() const;
    double getM4HDownPercent() const;
    double getM1DDownPercent() const;
    double allDownPercent() const;

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
    double m4HinunteUpperPercent{0};
    double m1DinunteUpperPercent{0};
    double mAllUpperPercent{0};


    double m5MDownPercent{0};
    double m15MDownPercent{0};
    double m1HDownPercent{0};
    double m4HDownPercent{0};
    double m1DDownPercent{0};
    double mAllDownPercent{0};
};

} // namespace Series

#endif // SERIES_SERIES_H
