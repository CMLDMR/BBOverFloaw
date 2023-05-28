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

    const QString interval() const;


    class iterator{
    public:
        iterator(QVector<Binance::Public::KLine>::iterator iter):current(iter){}
        Binance::Public::KLine &operator*() const;
        iterator &operator++();
        bool operator!=(const iterator &other );
    private:
        QVector<Binance::Public::KLine>::iterator current;
    };

    iterator begin();
    iterator end();

signals:
    void updated();

private:
    QString mPair;
    QString mInterval;
    QVector<Binance::Public::KLine> mKLineContainer;


};




} // namespace Series

#endif // SERIES_SERI_H
