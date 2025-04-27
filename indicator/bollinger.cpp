#include "bollinger.h"
#include <iostream>


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

double getDerivation(const std::vector<std::tuple<double, double, double> > &seri, const int mLength, const double stdDev)
{
    double sum{0};
    double mean{0};

    for( int i = seri.size()-mLength ; i < seri.size(); i++ ){
        auto &[close,high,low] = seri.at(i);
        sum += (close+high+low)/3.0;
        //        sum += item.closePrice();
    }

    mean = sum / mLength;

    double standardDeviation{0};

    for( int i = seri.size()-mLength ; i < seri.size() ; i++ ){
        auto &[close,high,low] = seri.at(i);
        auto val = (close+high+low)/3.0;
        standardDeviation += std::pow(val-mean,2);
    }

    return std::sqrt(standardDeviation / static_cast<double>(mLength));
}

double getDerivation(const std::vector<double> &seri, const int mLength )
{
    double sum{0};
    double mean{0};

    int counter= 0;
    for( int i = seri.size()-mLength ; i < seri.size(); i++ ){
        sum += seri.at(i);
        counter++;
    }

    mean = sum / static_cast<double>(counter);

    double standardDeviation{0};

    for( int i = seri.size()-mLength ; i < seri.size() ; i++ ){
        auto &close = seri.at(i);
        standardDeviation += std::pow(close-mean,2);
        // std::cout << i << ". standartDeviation " << standardDeviation << " close: " << close << " mean: " << mean << "\n";
    }
    // return mean;

    return std::sqrt(standardDeviation / static_cast<double>(counter));
}



std::tuple<double, double, double> Indicator::Bollinger::bollinger(const Series::Seri &seri, const int mLength, const double stdDev)
{

    if( seri.size() < mLength ) return std::make_tuple(0,0,0);

    double sum{0};
    double movingAverage{0};

    for( int i = seri.size()-mLength ; i < seri.size() ; i++ ){
        auto item = seri.at(i);
        sum += (item.closePrice()+item.highPrice()+item.lowPrice())/3.0;
    }
    movingAverage = sum / static_cast<double>(mLength);

    auto derivation = getDerivation(seri,mLength,stdDev);

    return std::make_tuple(movingAverage+stdDev*derivation,movingAverage,movingAverage-stdDev*derivation);
}

std::tuple<double, double, double> Indicator::Bollinger::bollinger(const std::vector<std::tuple<double, double, double> > &seri, const int mLength, const double stdDev)
{
    if( seri.size() < mLength ) return std::make_tuple(0,0,0);

    double sum{0};
    double movingAverage{0};

    for( int i = seri.size()-mLength ; i < seri.size() ; i++ ){
        auto &[close,high,low] = seri.at(i);
        sum += (close+high+low)/3.0;
    }
    movingAverage = sum / static_cast<double>(mLength);

    auto derivation = getDerivation(seri,mLength,stdDev);

    return std::make_tuple(movingAverage+stdDev*derivation,movingAverage,movingAverage-stdDev*derivation);
}

std::tuple<double, double, double> Indicator::Bollinger::bollinger(const std::vector<double> &seri, const int mLength, const double stdDev)
{
    if( seri.size() < mLength ) return std::make_tuple(0,0,0);

    double sum{0};
    double movingAverage{0};
    int counter = 0;
    for( size_t i = seri.capacity() - mLength ; i < seri.size() ; i++ ){
        sum += seri.at(i);
        counter++;
    }

    movingAverage = sum / static_cast<double>(mLength);

    auto derivation = getDerivation( seri , mLength );
    const auto upper = movingAverage + stdDev * derivation;
    const auto down  = movingAverage - stdDev * derivation;
    // std::cout << "Derivation " << derivation << " movingAverage: " << movingAverage << " upper: " << upper << "down: " << down << "\n";



    return std::make_tuple( upper , movingAverage ,  down );
}

std::tuple<double, double> Indicator::Bollinger::bollingerPercent(const Series::Seri &seri, const int mLength, const double stdDev)
{
    auto [upper,middle,down] = Bollinger::bollinger(seri,mLength,stdDev);

    // fiyat upper üstündeyse pozitif upperPercent
    auto upperPercent = ( seri.close() - upper )/ upper * 100;

    // fiyat down altındaysa pozitif downPercent
    auto downPercent = ( down - seri.close() )/ down * 100;

    if( upper == 0 ) upperPercent = 0;

    return std::make_tuple(upperPercent,downPercent);
}
