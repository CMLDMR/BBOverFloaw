#ifndef INDICATOR_BOLLINGER_H
#define INDICATOR_BOLLINGER_H

#include <QObject>

#include "series/seri.h"



namespace Indicator {

class Bollinger{

public:

    static std::tuple<double, double, double> bollinger( const Series::Seri &seri, const int mLength = 20 , const double stdDev = 2 );

    static std::tuple<double, double> bollingerPercent( const Series::Seri &seri, const int mLength = 20 , const double stdDev = 2 );

};

}

 // namespace Indicator_legacy

#endif // INDICATOR_BOLLINGER_H
