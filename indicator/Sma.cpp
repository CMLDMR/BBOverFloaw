#include "Sma.h"

namespace Indicator {

Sma::Sma()
{

}

double Sma::value(const Series::Seri &seri, const int length)
{
    if( seri.size() <= length ) {
        return 0;
    }

    const double d_length = static_cast<double>( length );
    double sum = 0;
    for( int i = ( seri.size() - length ) ; i < seri.size() ; i++ ) {
        sum += seri.at(i).closePrice();
    }

    return sum/d_length;
}

double Ema::value(const Series::Seri &seri, const int length)
{
    if( seri.size() <= length ) {
        return 0;
    }

    const int startPos = seri.size() - length;

    double lastEma = seri.at(startPos).closePrice();

    for( int i = startPos ; i < seri.size() ; i++ ) {

        const double price = seri.at(i).closePrice();
        const double k = 2.0 / ( static_cast<double>(length+1) );


        lastEma = price * k +  lastEma * ( 1 - k );
    }

    return lastEma;
}

} // namespace Indicator
