#ifndef SERIES_SERI_H
#define SERIES_SERI_H

#include <QObject>
#include "binance/restapi/symbol.h"

namespace Series {

class Seri : public QObject
{
    Q_OBJECT
public:
    explicit Seri(const Binance::Public::RestAPI::Symbol &smybol,QObject *parent = nullptr);

signals:




};



class Seri1m : public Seri
{
public:
    Seri1m(const Binance::Public::RestAPI::Symbol &smybol):Seri(smybol){}
};

} // namespace Series

#endif // SERIES_SERI_H
