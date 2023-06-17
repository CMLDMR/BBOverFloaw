#include "bollinger.h"




















double getDerivation(const Series::Seri &seri, const int mLength, const double stdDev)
{
    double sum{0};
    double mean{0};

    for( int i = seri.size()-mLength ; i < seri.size(); i++ ){
        auto item = seri.at(i);;
                sum += (item.closePrice()+item.highPrice()+item.lowPrice())/3.;
//        sum += item.closePrice();
    }

    mean = sum / mLength;

    double standardDeviation{0};

    for( int i = seri.size()-mLength ; i < seri.size() ; i++ ){
        auto item = seri.at(i);
        auto val = (item.closePrice()+item.highPrice()+item.lowPrice())/3.;
        standardDeviation += std::pow(val-mean,2);
    }

    return std::sqrt(standardDeviation / static_cast<double>(mLength));
}



std::tuple<double, double, double> Indicator::Bollinger::bollinger(const Series::Seri &seri, const int mLength, const double stdDev)
{

    if( seri.size() < seri.size() ) return std::make_tuple(0,0,0);

    double sum{0};
    double movingAverage{0};

    for( int i = seri.size()-mLength ; i < seri.size() ; i++ ){
        auto item = seri.at(i);
        sum += (item.closePrice()+item.highPrice()+item.lowPrice())/3.0;
    }
    movingAverage = sum / static_cast<double>(mLength);

    auto derivation = getDerivation(seri,mLength,stdDev);

    return std::make_tuple(movingAverage+stdDev*derivation,movingAverage,movingAverage-stdDev*derivation);
//    return std::make_tuple(movingAverage+stdDev*derivation,0,0);


}

std::tuple<double, double> Indicator::Bollinger::bollingerPercent(const Series::Seri &seri, const int mLength, const double stdDev)
{
    auto [upper,middle,down] = Bollinger::bollinger(seri,mLength,stdDev);

    auto upperPercent = (seri.close() - upper)/seri.close()*100;
    auto downPercent = (down - seri.close())/seri.close()*100;

    if( upper == 0 ) upperPercent = 0;

    return std::make_tuple(upperPercent,downPercent);

}
