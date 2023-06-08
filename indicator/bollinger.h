#ifndef INDICATOR_BOLLINGER_H
#define INDICATOR_BOLLINGER_H

#include <QObject>
#include "main/series.h"

#include "series/seri.h"



namespace Indicator {

class Bollinger{

public:

    static std::tuple<double, double, double> bollinger( const Series::Seri &seri, const int mLength = 21 , const double stdDev = 2.1 );

    static std::tuple<double, double> bollingerPercent( const Series::Seri &seri, const int mLength = 21 , const double stdDev = 2.1 );

};

}










namespace Indicator_legacy {

class Bollinger : public QObject
{
    Q_OBJECT
public:
    explicit Bollinger(Main::Series_Legacy *series , QObject *parent = nullptr);



    std::tuple<double,double,double> getBollinger(const int &index);

    std::tuple<double,double,double> getLast();


    void setSeries(Main::Series_Legacy *newSeries);

signals:


private:
    Main::Series_Legacy *mSeries;

    double getDerivation(const int &index);

    const int mLength{21};

};

} // namespace Indicator_legacy

#endif // INDICATOR_BOLLINGER_H
