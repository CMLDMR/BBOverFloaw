#ifndef BINANCE_PUBLIC_RESTAPI_H
#define BINANCE_PUBLIC_RESTAPI_H

#include <QObject>
#include "symbol.h"
#include "binance/kline.h"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent>


class QNetworkAccessManager;

namespace Binance {
namespace Public {
namespace RestAPI{

class RestAPI : public QObject
{
    Q_OBJECT
public:
    static RestAPI* instance();

    void updateInfo();

    QVector<Symbol> symbolList() const;

    const QVector<Binance::Public::KLine> getCandles(const QString &pair, const QString &interval , const int &size );

signals:


private:

    enum class Command{
        getSymbol,
        getKline
    };

    Command mCurrentCommand;

    explicit RestAPI(QObject *parent = nullptr);

    static RestAPI* mRestAPI;

    QNetworkAccessManager* mManager;

    QVector<Symbol> mSymbolList;

    bool saveList();

    bool loadList();

};
}




} // namespace Public
} // namespace Binance

#endif // BINANCE_PUBLIC_RESTAPI_H
