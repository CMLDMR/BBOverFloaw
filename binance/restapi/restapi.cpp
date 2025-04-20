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


#define SPOTEXCHANGE "https://api.binance.com/api/v3/exchangeInfo"
#define FUTUREEXCHANGE "https://fapi.binance.com/fapi/v1/exchangeInfo"


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


const QVector<Binance::Public::KLine> RestAPI::getCandles(const QString &pair, const QString &interval, const int &size)
{
    auto manager = new QNetworkAccessManager();

    const QString urlString = "https://fapi.binance.com/fapi/v1/continuousKlines?pair="+pair+"&contractType=PERPETUAL&interval="+interval+"&limit="+QString::number(size);

    // qDebug() << __LINE__ << __FILE__ << urlString;
    auto reply = manager->get(QNetworkRequest(QUrl( urlString )));

    QEventLoop loop;
    QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    const auto replyAr = reply->readAll();
    auto ar = QJsonDocument::fromJson(replyAr).array();

    // qDebug() << __LINE__ << __FILE__ << ar << replyAr;

    reply->deleteLater();
    manager->deleteLater();
    QVector<Binance::Public::KLine> kList{};

    for( const auto &item : ar ){
        auto _ar = item.toArray();
        Binance::Public::KLine kLine(_ar);

        const auto buyDollarVolume = kLine.takerBuyQuoteAssetVolume();
        const auto sellDollarVolume = kLine.quoteAssetVolume() - kLine.takerBuyQuoteAssetVolume();
        if( kList.size() ) {

            kLine.setQuotaAssetVolumeOpen( kList.last().quotaClose() );
            kLine.setQuotaAssetVolumeClose( kList.last().quotaClose() + buyDollarVolume - sellDollarVolume );

            kLine.setQuotaAssetVolumeHigh( kLine.quotaClose() );
            kLine.setQuotaAssetVolumeLow( kLine.quotaOpen() );

        }
        else{
            kLine.setQuotaAssetVolume( buyDollarVolume > sellDollarVolume , buyDollarVolume - sellDollarVolume , true );

        }

        kList.append(kLine);
    }



    return kList;
}

} // namespace RestAPI
} // namespace Public
} // namespace Binance
