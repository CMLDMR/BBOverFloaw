#ifndef MAIN_SERIES_H
#define MAIN_SERIES_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVector>
#include <QWebSocket>

#include <unordered_map>


#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>


#include "candleitem.h"


namespace Indicator{
class Bollinger;
}

namespace Main {

class Series : public QObject
{
    Q_OBJECT
public:
    Series(const QString pair, const QString &interval);
    virtual ~Series(){
        qDebug() << "Delete Series";
        mSocket->close();
        delete mSocket;
        mSocket = nullptr;
    }



    const QVector<CandleItem> &getSeries() const;

    QString timeInterval() const;

    const CandleItem &lastCandle() const;

    void update( const QString &pair , const QString &interval );

    Indicator::Bollinger *bollinger() const;

    std::unordered_map<QString, std::tuple<double, double, double> > valueList() const;

    qulonglong lastCloseTimeEpoch() const;

signals:
    void ready();

private:
    QNetworkAccessManager* mAccessManager;
    QString mTimeInterval;
    QString mPair;

    QVector<CandleItem> mSeries;

    QWebSocket* mSocket;
    Indicator::Bollinger* mBollinger;

    std::unordered_map<QString,std::tuple<double,double,double>> mValueList;

    qulonglong mLastCloseTimeEpoch;


private slots:

    void replaceLastCandle( const QString &msg );



};

} // namespace Main

#endif // MAIN_SERIES_H
