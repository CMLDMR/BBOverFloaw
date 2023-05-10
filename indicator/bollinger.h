#ifndef INDICATOR_BOLLINGER_H
#define INDICATOR_BOLLINGER_H

#include <QObject>
#include "main/series.h"

namespace Indicator {

class Bollinger : public QObject
{
    Q_OBJECT
public:
    explicit Bollinger(Main::Series *series , QObject *parent = nullptr);



    std::tuple<double,double,double> getBollinger(const int &index);

    std::tuple<double,double,double> getLast();


    void setSeries(Main::Series *newSeries);

signals:


private:
    Main::Series *mSeries;

    double getDerivation(const int &index);

};

} // namespace Indicator

#endif // INDICATOR_BOLLINGER_H
