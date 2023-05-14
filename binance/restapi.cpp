#include "restapi.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>

#include <mutex>

namespace Binance {
namespace Public {


std::once_flag mRestAPICallOnceFlag;
RestAPI* RestAPI::mRestAPI{nullptr};

RestAPI *RestAPI::instance()
{
    std::call_once(mRestAPICallOnceFlag,[=](){
        mRestAPI = new RestAPI();
    });
    return mRestAPI;
}

void RestAPI::exchangeInfo()
{
    mManager->get(QNetworkRequest(QUrl("https://fapi.binance.com/fapi/v1/exchangeInfo")));
}

RestAPI::RestAPI(QObject *parent)
    : QObject{parent}
{
    mManager = new QNetworkAccessManager(this);

    QObject::connect(mManager,&QNetworkAccessManager::finished,[=](QNetworkReply* reply ){

            auto obj = QJsonDocument::fromJson(reply->readAll()).object();

            auto asset = obj.value("symbols").toArray();

            int i = 0;
            for( const auto &item : asset ){
                qDebug() << item.toObject();
                if( ++i > 5 ) break;
            }
    });

}

} // namespace Public
} // namespace Binance
