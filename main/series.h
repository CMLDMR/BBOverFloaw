#ifndef MAIN_SERIES_H
#define MAIN_SERIES_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVector>
#include <QWebSocket>
#include <QThread>

#include <unordered_map>


#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>


#include "candleitem.h"


namespace Indicator_legacy{
class Bollinger;
}

namespace Main {

class Series_Legacy : public QObject
{
    Q_OBJECT
public:
    Series_Legacy(const QString pair, const QString &interval);
    virtual ~Series_Legacy();



    const QVector<CandleItem> &getSeries() const;

    QString timeInterval() const;

    const CandleItem &lastCandle() const;

    void update( const QString &pair , const QString &interval );

    Indicator_legacy::Bollinger *bollinger() const;

    std::unordered_map<QString, std::tuple<double, double, double> > valueList() const;

    qulonglong lastCloseTimeEpoch() const;

    QString pair() const;

signals:
    void ready();

private:
    QNetworkAccessManager* mAccessManager;
    QString mTimeInterval;
    QString mPair;

    QVector<CandleItem> mSeries;

    QWebSocket* mSocket;
    Indicator_legacy::Bollinger* mBollinger;

    std::unordered_map<QString,std::tuple<double,double,double>> mValueList;

    qulonglong mLastCloseTimeEpoch;

    QThread* mThread;


private slots:

    void replaceLastCandle( const QString &msg );

    void startSocket();



};

} // namespace Main

#endif // MAIN_SERIES_H
