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

    void append( const Binance::Public::KLine &kline );
    void removelast();
    void removeFirst();
    // void replacelast(const Binance::Public::KLine &kline);

    const QString interval() const;

    ///
    /// \brief close if index == 0, close is most recent price
    /// \param index
    /// \return
    ///
    const double close( const int &index = -1 )  const;
    const double open( const int &index = -1 ) const;
    const double high( const int &index = -1 ) const;
    const double low( const int &index = -1 ) const;
    const qint64 openTime( const int &index = -1 ) const;
    const qint64 closeTime( const int &index = -1 ) const;
    const double volume( const int &index = -1 ) const;
    const double takerVolume( const int &index = -1 ) const;
    const qint64 numberOfTrade( const int &index = - 1 ) const;
    const double percentLastBar( const int &index = -1 ) const;

    const double quotaClose( const int &index = -1 )  const;
    const double quotaOpen( const int &index = -1 ) const;
    const double quotaHigh( const int &index = -1 ) const;
    const double quotaLow( const int &index = -1 ) const;

    Binance::Public::KLine last() const;

    size_t size() const;

    const Binance::Public::KLine &at( const int &index ) const;
    const double maxPrice() const;
    const double minPrice() const;

    const double maxQuotaVolume() const;
    const double minQuotaVolume() const;

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

    qint64 duration() const;

signals:
    void updated();

private:
    QString mPair;
    QString mInterval;
    qint64 mDuration;
    QVector<Binance::Public::KLine> mKLineContainer;


};




} // namespace Series

#endif // SERIES_SERI_H
