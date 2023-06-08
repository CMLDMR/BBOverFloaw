#ifndef GLOBAL_UTILITY_H
#define GLOBAL_UTILITY_H


#include <QString>
#include <iomanip>
#include <sstream>

namespace Global {

class Utility
{
public:
    Utility();
};


static QString getFixedPrecision(const double &value, const int &precision = 2 )
{
    int pre = precision;
    if( precision == 0 || precision > 50 ){
        return QString::number(static_cast<int>(value));
    }

    if( std::abs(value) > 10 ) pre = 1;
    if( std::abs(value) > 100 ) pre = 0;


    std::ostringstream streamObj3;
    streamObj3 << std::fixed;
    streamObj3 << std::setprecision(pre);
    streamObj3 << value;
    return QString::fromStdString(streamObj3.str());
}


} // namespace Global

#endif // GLOBAL_UTILITY_H
