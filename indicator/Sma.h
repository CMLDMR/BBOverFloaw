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


class RSI
{
public:
    RSI(){}

    static double value( const Series::Seri &seri , const int length = 14 );

private:


};



class ADX
{
public:
    ADX(){}

    struct ADXResult {
        std::vector<double> plusDI;
        std::vector<double> minusDI;
        std::vector<double> adx;
    };
    struct Candle {
        double high;
        double low;
        double close;
    };


    static double value( const Series::Seri &seri , const int length = 14 );

    static double calcTrueRange(double high, double low, double prevClose);

    static double calcDMPlus(double high, double prevHigh, double low, double prevLow);

    static double calcDMMinus(double high, double prevHigh, double low, double prevLow) ;


    static double calculateTrueRange(double prevClose, double currentHigh, double currentLow) {
        double tr1 = currentHigh - currentLow;
        double tr2 = fabs(currentHigh - prevClose);
        double tr3 = fabs(currentLow - prevClose);
        return std::max(tr1, std::max(tr2, tr3));
    }

    // Function to calculate directional movement (+DM and -DM)
    static void calculateDirectionalMovement(double prevHigh, double prevLow, double currentHigh, double currentLow, double &plusDM, double &minusDM) {
        double upMove = currentHigh - prevHigh;
        double downMove = prevLow - currentLow;

        plusDM = (upMove > downMove && upMove > 0) ? upMove : 0;
        minusDM = (downMove > upMove && downMove > 0) ? downMove : 0;
    }
};




} // namespace Indicator

#endif // SMA_H
