#ifndef INDICATOR_BOLLINGER_H
#define INDICATOR_BOLLINGER_H

#include <QObject>

#include "series/seri.h"



namespace Indicator {

class Bollinger{

public:

    static std::tuple<double, double, double> bollinger( const Series::Seri &seri, const int mLength = 21 , const double stdDev = 2.1 );

    static std::tuple<double, double> bollingerPercent( const Series::Seri &seri, const int mLength = 21 , const double stdDev = 2.1 );

};

}

 // namespace Indicator_legacy

#endif // INDICATOR_BOLLINGER_H
