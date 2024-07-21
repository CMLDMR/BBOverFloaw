#ifndef SMA_H
#define SMA_H
#include "series/seri.h"


namespace Indicator {

class Sma
{
public:
    Sma();

    double static value( const Series::Seri &seri , const int length = 200 );
};


class Ema
{
public:
    Ema(){}

    static double value( const Series::Seri &seri , const int length = 200 );
};

} // namespace Indicator

#endif // SMA_H
