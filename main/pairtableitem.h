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

        mWillRemove = true;

        qDebug() << "Delete PairTableItem";
        for( auto &item : mSeriesList ){
            delete item;
        }
        mSeriesList.clear();

//        killTimer(mTimerId);




    }



    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


    Series_Legacy* mLastSeries{nullptr};
    Series_Legacy* mSeries5m;
    Series_Legacy* mSeries15m;
    Indicator_legacy::Bollinger* mBollinger5m;

    QString pair() const;

    QVector<Series_Legacy *> *seriesList();

    void setWillRemove(bool newWillRemove);

private:


    QVector<Series_Legacy*> mSeriesList;
    bool m1_up{false},m3_up{false},m5_up{false},m15_up{false},m30_up{false},m1h_up{false},m4h_up{false},m1d_up{false},m1w_up{false};
    bool m1_down{false},m3_down{false},m5_down{false},m15_down{false},m30_down{false},m1h_down{false},m4h_down{false},m1d_down{false},m1w_down{false};
    double m1wUpperValue{0.0},m1wDownValue{0.0};

    bool canRequst{true};
    int requestIntervalIndex{0};
    QString mLastInterval;

    QString mPair;

    QString getFixedPrecision(const double &value , const int &precision = 2);

    qreal mWidth = 261, mHeight = 70;
    int mTimerId;
    bool mWillRemove{false};
    QTimer* mTimer;

    int colorGradient{0};
    bool mAlarmActivated{false};
};

} // namespace Main

#endif // MAIN_PAIRTABLEITEM_H
