#include "bollinger.h"




















namespace Indicator_legacy {

Bollinger::Bollinger(Main::Series_Legacy *series, QObject *parent)
    : QObject{parent},mSeries(series)
{

}

double Bollinger::getDerivation(const int &index)
{
    if( index >= mSeries->getSeries().size() ) return 0;
    if( index < mLength ) return 0;
    double sum{0};
    double mean{0};

    for( int i = index-mLength ; i < index ; i++ ){
        auto item = mSeries->getSeries()[i];
//        sum += (item.close()+item.high()+item.low())/3.;
        sum += item.close();
    }

    mean = sum / mLength;

    double standardDeviation{0};

    for( int i = index-mLength ; i < index ; i++ ){
        auto item = mSeries->getSeries()[i];
        auto val = (item.close()+item.high()+item.low())/3.;
        standardDeviation += std::pow(val-mean,2);
    }

    return std::sqrt(standardDeviation / static_cast<double>(mLength));
}

std::tuple<double, double, double> Bollinger::getBollinger(const int &index)
{
    if( index >= mSeries->getSeries().size() ) return std::make_tuple(0,0,0);
    if( index < mLength ) return std::make_tuple(0,0,0);

    double sum{0};
    double movingAverage{0};

    for( int i = index-mLength ; i < index ; i++ ){
        auto item = mSeries->getSeries()[i];
        sum += (item.close()+item.high()+item.low())/3.;
    }
    movingAverage = sum / static_cast<double>(mLength);

    auto derivation = getDerivation(index);

    return std::make_tuple(movingAverage+2*derivation,movingAverage,movingAverage-2*derivation);
}

std::tuple<double, double, double> Bollinger::getLast()
{
    return getBollinger(mSeries->getSeries().size()-1);
}

void Bollinger::setSeries(Main::Series_Legacy *newSeries)
{
    mSeries = newSeries;
}

} // namespace Indicator_legacy



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


}

std::tuple<double, double> Indicator::Bollinger::bollingerPercent(const Series::Seri &seri, const int mLength, const double stdDev)
{
    auto [upper,middle,down] = Bollinger::bollinger(seri,mLength,stdDev);

    auto upperPercent = (seri.close() - upper)/seri.close()*100;
    auto downPercent = (down - seri.close())/seri.close()*100;

    return std::make_tuple(upperPercent,downPercent);

}
