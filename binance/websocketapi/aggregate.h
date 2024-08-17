#ifndef BINANCE_PUBLIC_WEBSOCKETAPI_AGGREGATE_H
#define BINANCE_PUBLIC_WEBSOCKETAPI_AGGREGATE_H

#include <QJsonObject>

#include <string>

inline std::string formatLargeNumber(double num) {
    const char* suffixes[] = {"", "K", "M", "G", "T", "P", "E"};
    int suffixIndex = 0;

    // Sayı 1000'den büyükse uygun kısaltmayı bulmak için döngü
    while (num >= 1000 && suffixIndex < 6) {
        num /= 1000;
        ++suffixIndex;
    }

    // Sonucu string'e çevir ve kısaltmayı ekle
    char formattedNumber[20];
    snprintf(formattedNumber, sizeof(formattedNumber), "%.2f%s", num, suffixes[suffixIndex]);
    return std::string(formattedNumber);
}

namespace Binance {
namespace Public {
namespace WebSocketAPI {

class Aggregate : public QJsonObject
{
public:
    Aggregate();
    Aggregate( const QJsonObject &other );

    qint64 eventTime() const;
    double price() const;
    double quantity() const;
    qint64 tradeTime() const;
    bool isMaker() const;
};

} // namespace WebSocketAPI
} // namespace Public
} // namespace Binance

#endif // BINANCE_PUBLIC_WEBSOCKETAPI_AGGREGATE_H
