#ifndef INDICATOR_BOLLINGER_H
#define INDICATOR_BOLLINGER_H

#include <QObject>

#include "series/seri.h"

#include <cmath>


namespace Indicator {

class Bollinger{

public:

    static std::tuple<double, double, double> bollinger( const Series::Seri &seri, const int mLength = 20 , const double stdDev = 2 );
    static std::tuple<double, double, double> bollinger( const std::vector<std::tuple<double, double, double>> &seri, const int mLength = 20 , const double stdDev = 2 );
    static std::tuple<double, double, double> bollinger( const std::vector<double> &seri, const int mLength = 20 , const double stdDev = 2 );

    static std::tuple<double, double> bollingerPercent( const Series::Seri &seri, const int mLength = 20 , const double stdDev = 2 );

};


// Basit hareketli ortalama (SMA)
inline double calculateSMA(const std::vector<double>& data, int start, int period) {
    double sum = 0.0;
    for (int i = start; i < start + period; ++i) {
        sum += data[i];
    }
    return sum / period;
}

// Standart sapma
inline double calculateStdDev(const std::vector<double>& data, int start, int period, double mean) {
    double sum = 0.0;
    for (int i = start; i < start + period; ++i) {
        sum += (data[i] - mean) * (data[i] - mean);
    }
    return std::sqrt(sum / period);
}

// Bollinger Bandı hesapla
inline std::tuple<double,double,double> calculateBollingerBands(const std::vector<double>& prices, int period = 20, double k = 2.0) {
    std::vector<std::tuple<double,double,double>> bands;

    if (prices.size() < period)
        return {0,0,0}; // Yeterli veri yok

    for (size_t i = 0; i <= prices.size() - period; ++i) {
        double sma = calculateSMA(prices, i, period);
        double stddev = calculateStdDev(prices, i, period, sma);

        // BollingerBand band;
        auto middle = sma;
        auto upper = sma + (k * stddev);
        auto lower = sma - (k * stddev);

        bands.push_back({upper,middle,lower});
    }

    return bands.back();
}

}

 // namespace Indicator_legacy

#endif // INDICATOR_BOLLINGER_H
