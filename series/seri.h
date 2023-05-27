#ifndef SERIES_SERI_H
#define SERIES_SERI_H

#include <QObject>
#include "binance/kline.h"
#include <QThread>

namespace Series {

class Seri : public QObject
{
    Q_OBJECT
public:
    explicit Seri(const QString &pair,const QString &interval,QObject *parent = nullptr);


    QString pair() const;

    QVector<Binance::Public::KLine> &kLineContainer();

    QString interval() const;

signals:
    void updated();

private:
    QString mPair;
    QString mInterval;
    QVector<Binance::Public::KLine> mKLineContainer;


};




} // namespace Series

#endif // SERIES_SERI_H
