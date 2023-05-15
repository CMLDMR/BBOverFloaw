#ifndef BINANCE_PUBLIC_RESTAPI_H
#define BINANCE_PUBLIC_RESTAPI_H

#include <QObject>

class QNetworkAccessManager;

namespace Binance {
namespace Public {

class RestAPI : public QObject
{
    Q_OBJECT
public:
    static RestAPI* instance();

    void exchangeInfo();



signals:


private:

    explicit RestAPI(QObject *parent = nullptr);

    static RestAPI* mRestAPI;

    QNetworkAccessManager* mManager;

};

} // namespace Public
} // namespace Binance

#endif // BINANCE_PUBLIC_RESTAPI_H
