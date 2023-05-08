#ifndef MAIN_SERIES_H
#define MAIN_SERIES_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVector>


#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>


#include "candleitem.h"

namespace Main {

class Series : public QObject
{
    Q_OBJECT
public:
    Series(const QString pair, const QString &interval);




    const QVector<CandleItem> &getSeries() const;

    QString timeInterval() const;

    const CandleItem &lastCandle() const;

    void update( const QString &pair , const QString &interval );

signals:
    void ready();

private:
    QNetworkAccessManager* mAccessManager;
    QString mTimeInterval;
    QString mPair;

    QVector<CandleItem> mSeries;

};

} // namespace Main

#endif // MAIN_SERIES_H
