#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <iomanip>
#include <sstream>

namespace Utility {

inline std::string humanReadable( const double value ) {
    const double units[] = { 1.0, 1000.0, 1000000.0, 1000000000.0, 1000000000000.0 }; // B, KB, MB, GB, TB
    const char* unitNames[] = { "$", "K$", "M$", "G$", "T$" };
    const int numUnits = sizeof(units) / sizeof(units[0]);

    // Negatiflik kontrolü
    bool isNegative = value < 0;
    double absValue = std::abs(value);

    // Uygun birimi bulma
    int i = 0;
    while (i < numUnits - 1 && absValue >= units[i + 1]) {
        ++i;
    }

    // String formatlama
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);  // Sabit ondalık ve iki haneli hassasiyet
    oss << (absValue / units[i]) << " " << unitNames[i];

    std::string result = oss.str();
    if (isNegative) {
        result = "-" + result;  // Negatif işareti ekleme
    }

    return result;
}

}

#endif // UTILITY_H
