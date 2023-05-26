#include "restapi.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>

#include <QFile>

#include <QDebug>

namespace Binance {
namespace Public {
namespace RestAPI {




std::once_flag mRestAPICallOnceFlag;
RestAPI* RestAPI::mRestAPI{nullptr};



RestAPI *RestAPI::instance()
{
    std::call_once(mRestAPICallOnceFlag,[=](){
        mRestAPI = new RestAPI();
    });
    return mRestAPI;
}

void RestAPI::updateInfo()
{
    mManager->get(QNetworkRequest(QUrl("https://fapi.binance.com/fapi/v1/exchangeInfo")));
}

RestAPI::RestAPI(QObject *parent)
    : QObject{parent}
{
    mManager = new QNetworkAccessManager(this);

    QObject::connect(mManager,&QNetworkAccessManager::finished,[=](QNetworkReply* reply ){

            auto obj = QJsonDocument::fromJson(reply->readAll()).object();
            mManager->clearAccessCache();
            mManager->clearConnectionCache();

            auto asset = obj.value("symbols").toArray();
            mSymbolList.clear();
            for( const auto &item : asset ){
                Symbol symbol(item.toObject());
                mSymbolList.append(symbol);
            }
            this->saveList();

    });

    if( !this->loadList() ){
        mManager->get(QNetworkRequest(QUrl("https://fapi.binance.com/fapi/v1/exchangeInfo")));
    }


}

bool RestAPI::saveList()
{
    QFile file("exchangeinfo.dat");

    if( file.exists() ){
        file.remove();
    }


    if( file.open(QIODevice::ReadWrite) ){
        QDataStream in(&file);
        in << mSymbolList.size();

        for( const auto &item : mSymbolList ){
            in << item;
        }

        file.close();
        return true;
    }
    return false;

}

bool RestAPI::loadList()
{
    QFile file("exchangeinfo.dat");

    if( file.open(QIODevice::ReadOnly ) ){
        QDataStream in(&file);
        qsizetype size;
        in >> size;

        for( int i = 0 ; i < size ; i++ ){
            Symbol symbol;
            in >> symbol;
            mSymbolList.append(symbol);
        }

        file.close();


        return true;
    }

    return false;
}

QVector<Symbol> RestAPI::symbolList() const
{
    return mSymbolList;
}


const KLineContainer RestAPI::getCandles(const QString &pair, const QString &interval, const int &size)
{
    auto manager = new QNetworkAccessManager();

    auto reply = manager->get(QNetworkRequest(QUrl("https://fapi.binance.com/fapi/v1/continuousKlines?pair="+pair+"&contractType=PERPETUAL&interval="+interval+"&limit="+QString::number(size))));

    QEventLoop loop;
    QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    auto ar = reply->readAll();

    reply->deleteLater();
    manager->deleteLater();

    KLineContainer kList(ar);

    return kList;
}

} // namespace RestAPI
} // namespace Public
} // namespace Binance
