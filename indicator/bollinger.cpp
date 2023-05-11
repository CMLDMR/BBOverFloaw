#include "bollinger.h"

namespace Indicator {

Bollinger::Bollinger(Main::Series *series, QObject *parent)
    : QObject{parent},mSeries(series)
{

}

double Bollinger::getDerivation(const int &index)
{
    if( index >= mSeries->getSeries().size() ) return 0;
    if( index < 21 ) return 0;
    double sum{0};
    double mean{0};

    for( int i = index-21 ; i < index ; i++ ){
        auto item = mSeries->getSeries()[i];
        sum += (item.close()+item.high()+item.low())/3.;
    }

    mean = sum / 21.;

    double standardDeviation{0};

    int counter = 0;
    for( int i = index-21 ; i < index ; i++ ){
        counter++;
        auto item = mSeries->getSeries()[i];
        auto val = (item.close()+item.high()+item.low())/3.;
        standardDeviation += std::pow(val-mean,2);
        qDebug() << "Standart Deviation: " << counter;
    }

    return std::sqrt(standardDeviation / 21);
}

std::tuple<double, double, double> Bollinger::getBollinger(const int &index)
{
    if( index >= mSeries->getSeries().size() ) return std::make_tuple(0,0,0);
    if( index < 21 ) return std::make_tuple(0,0,0);

    double sum{0};
    double movingAverage{0};

    for( int i = index-21 ; i < index ; i++ ){
        auto item = mSeries->getSeries()[i];
        sum += (item.close()+item.high()+item.low())/3.;
    }
    movingAverage = sum / 21.0;

    auto derivation = getDerivation(index);

    return std::make_tuple(movingAverage+2*derivation,movingAverage,movingAverage-2*derivation);
}

std::tuple<double, double, double> Bollinger::getLast()
{
    return getBollinger(mSeries->getSeries().size()-1);
}

void Bollinger::setSeries(Main::Series *newSeries)
{
    mSeries = newSeries;
}

} // namespace Indicator
