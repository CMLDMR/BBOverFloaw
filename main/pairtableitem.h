#ifndef MAIN_PAIRTABLEITEM_H
#define MAIN_PAIRTABLEITEM_H

#include <QGraphicsItem>
#include <QObject>

#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include <unordered_map>
#include <QHash>
#include <QSet>

#include <cmath>
#include <tuple>
#include <iomanip>

#include "series.h"
#include "indicator/bollinger.h"
#include "abtractitem.h"


namespace Main {

class CandleItem;

class PairTableItem : public AbtractItem
{
public:
    PairTableItem(const QString &pair);
    virtual ~PairTableItem(){
        qDebug() << "Delete PairTableItem";
        for( auto &item : mSeriesList ){
            delete item;
        }
        mSeriesList.clear();
    }

    enum class Interval{
        _5m = 0,
        _15m,
        _1h,
        _4h,
        _1d,
        _1w
    };

    Interval mCurrentInterval;

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


    Series* mLastSeries{nullptr};
    Series* mSeries5m;
    Series* mSeries15m;
    Indicator::Bollinger* mBollinger5m;

    QString pair() const;

    QVector<Series *> *seriesList();

private:


    QVector<Series*> mSeriesList;
    QVector<QString> mBollingerIntervalList;
//    std::unordered_map<QString,std::tuple<double,double,double>> mValueList;


    bool canRequst{true};
    int requestIntervalIndex{0};
    QString mLastInterval;

    QString mPair;

    QString getFixedPrecision(const double &value , const int &precision = 2);

    qreal mWidth = 431, mHeight = 54;


    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;

};

} // namespace Main

#endif // MAIN_PAIRTABLEITEM_H
