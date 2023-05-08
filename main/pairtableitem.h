#ifndef MAIN_PAIRTABLEITEM_H
#define MAIN_PAIRTABLEITEM_H

#include <QGraphicsItem>
#include <QObject>
#include <QNetworkAccessManager>

#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <cmath>
#include <tuple>

namespace Main {

class CandleItem;

class PairTableItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    PairTableItem();

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QNetworkAccessManager* mAccessManager;

private:
    QVector<CandleItem> mCandles;

    double getDerivation(const int &index);
    std::tuple<double,double,double> getBollinger(const int &index);

};

class CandleItem : public QJsonArray
{
public:
    CandleItem(){};
    CandleItem( const QJsonArray &other );

    qulonglong openTime() const;
    QString openStr() const;
    double open() const;
    QString highStr() const;
    double high() const;
    QString lowStr() const;
    double low() const;
    QString closeStr() const;
    double close() const;
    QString volumeStr() const;
    QString assetVolume() const;

    qulonglong closeTimeLong() const;
    QTime closeTime() const;
    qulonglong numberOfTrade() const;
    QString buyVolumeStr() const;
    QString buyAssetVolumeStr() const;


//    1607444700000,          // 0 Open time
//    "18879.99",             // 1 Open
//    "18900.00",             // 2 High
//    "18878.98",             // 3 Low
//    "18896.13",             // 4 Close (or latest price)
//    "492.363",              // 5 Volume
//    1607444759999,          // 6 Close time
//    "9302145.66080",        // 7 Quote asset volume
//    1874,                   // 8 Number of trades
//    "385.983",              // 9 Taker buy volume
//    "7292402.33267",        // 10 Taker buy quote asset volume
//    "0"                     // 11 Ignore.

};

} // namespace Main

#endif // MAIN_PAIRTABLEITEM_H
