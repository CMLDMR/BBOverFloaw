#ifndef MAIN_PAIRTABLEITEM_H
#define MAIN_PAIRTABLEITEM_H

#include <QGraphicsItem>
#include <QObject>

#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <cmath>
#include <tuple>
#include <unordered_map>
#include <QHash>
#include <QSet>

#include "series.h"
#include "indicator/bollinger.h"

namespace Main {

class CandleItem;

class PairTableItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    PairTableItem(const QString &pair);

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


    Series* mSeris;
    Indicator::Bollinger* mBollinger;

private:


    QVector<QString> mBollingerIntervalList;
    std::unordered_map<QString,std::tuple<double,double,double>> mValueList;


    bool canRequst{true};
    int requestIntervalIndex{0};
    QString mLastInterval;

    QString mPair;


    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
};

} // namespace Main

#endif // MAIN_PAIRTABLEITEM_H
