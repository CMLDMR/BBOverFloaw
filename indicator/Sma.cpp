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

double RSI::value(const Series::Seri &seri, const int length)
{
    double gain = 0.0, loss = 0.0;
    const double period = static_cast<double>(length);

    const int startPos = seri.size() - length;

    // İlk dönem için kazanç ve kayıpları hesaplayın
    for (int i = startPos; i < seri.size(); ++i) {
        double change = seri.at(i).closePrice() - seri.at(i-1).closePrice();
        if (change > 0) {
            gain += change;
        } else {
            loss -= change;
        }
    }

    // Ortalama kazanç ve kayıp
    gain /= period;
    loss /= period;

    // // RMA'yı periyottan sonra hesapla
    // for (int i = period; i < data.size(); i++) {
    //     rma[i] = (rma[i - 1] * (period - 1) + data[i]) / period;
    // }

    // RS ve RSI hesaplama
    double RS = gain / loss;
    double RSI = 100 - (100 / (1 + RS));

    return RSI;
}

double ADX::value(const Series::Seri &seri, const int period)
{
    if( seri.size() <= period )
        return 0;

    std::vector<double> tr(period), plusDM(period), minusDM(period);
    std::vector<double> smoothedTR, smoothedPlusDM, smoothedMinusDM, plusDI, minusDI, dx, adx;

    for (int i = 1; i < period; i++) {
        tr[i] = calculateTrueRange(seri.close(i - 1), seri.high(i), seri.low(i) );
        calculateDirectionalMovement(seri.high(i-1), seri.low(i-1), seri.high(i), seri.low(i), plusDM[i], minusDM[i]);
    }

    double trSum = 0, plusDMSum = 0, minusDMSum = 0;
    for (int i = 1; i < period; i++) {
        trSum += tr[i];
        plusDMSum += plusDM[i];
        minusDMSum += minusDM[i];
    }

    smoothedTR.push_back(trSum);
    smoothedPlusDM.push_back(plusDMSum);
    smoothedMinusDM.push_back(minusDMSum);

    for (int i = period; i < seri.size(); i++) {
        tr[i % period] = calculateTrueRange(seri.close(i - 1), seri.high(i), seri.low(i));
        calculateDirectionalMovement(seri.high(i - 1), seri.low(i - 1), seri.high(i), seri.low(i), plusDM[i % period], minusDM[i % period]);

        double smoothTR = smoothedTR.back() - (smoothedTR.back() / period) + tr[i % period];
        double smoothPlusDM = smoothedPlusDM.back() - (smoothedPlusDM.back() / period) + plusDM[i % period];
        double smoothMinusDM = smoothedMinusDM.back() - (smoothedMinusDM.back() / period) + minusDM[i % period];

        smoothedTR.push_back(smoothTR);
        smoothedPlusDM.push_back(smoothPlusDM);
        smoothedMinusDM.push_back(smoothMinusDM);

        plusDI.push_back(100 * (smoothPlusDM / smoothTR));
        minusDI.push_back(100 * (smoothMinusDM / smoothTR));

        double diDiff = fabs(plusDI.back() - minusDI.back());
        double diSum = plusDI.back() + minusDI.back();
        dx.push_back(100 * (diDiff / diSum));

        if (i >= 2 * period - 1) {
            double adxValue = (adx.empty()) ? dx.back() : ((adx.back() * (period - 1)) + dx.back()) / period;
            adx.push_back(adxValue);
        }
    }


    return adx.back();
}

double ADX::calcTrueRange(double high, double low, double prevClose)
{
    return std::max({high - low, std::abs(high - prevClose), std::abs(low - prevClose)});
}

double ADX::calcDMPlus(double high, double prevHigh, double low, double prevLow)
{
    double moveUp = high - prevHigh;
    double moveDown = prevLow - low;

    if (moveUp > moveDown && moveUp > 0)
        return moveUp;
    return 0;
}

double ADX::calcDMMinus(double high, double prevHigh, double low, double prevLow)
{
    double moveUp = high - prevHigh;
    double moveDown = prevLow - low;

    if (moveDown > moveUp && moveDown > 0)
        return moveDown;
    return 0;
}

} // namespace Indicator
