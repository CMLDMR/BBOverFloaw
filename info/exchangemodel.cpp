#include "exchangemodel.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>

#include <QFile>
#include <QDataStream>

#include <mutex>

#include "binance/restapi/restapi.h"


namespace ExchangeInfo {

ExchangeModel::ExchangeModel(QObject *parent)
    : QAbstractTableModel(parent)
{

    mModel = new QSortFilterProxyModel();
    mModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mModel->setSourceModel(this);


    mManager = new QNetworkAccessManager(parent);

    QObject::connect(mManager,&QNetworkAccessManager::finished,[=](QNetworkReply* reply ){

        if( mRequestType == exchangeInfo ){

        }else if( mRequestType == price ){
            auto array = QJsonDocument::fromJson(reply->readAll()).array();

            beginResetModel();
            mPriceList.clear();
            for( const auto &item : array ){
                Ticker obj = item.toObject();
                mPriceList.append(obj);
            }
            endResetModel();
        }

        setQuotaFilterKey("USDT");
    });



    for( const auto &item : Binance::Public::RestAPI::RestAPI::instance()->symbolList() ){
        if( !mFullList.contains(item) ){
            mFullList.append(item);
        }
    }


    setQuotaFilterKey("USDT");
    updatePricetoPercent();
}

std::once_flag mExchangeModelFlags;
ExchangeModel* ExchangeModel::mExchangeModel{nullptr};
ExchangeModel *ExchangeModel::instance()
{
    std::call_once(mExchangeModelFlags,[=](){
        mExchangeModel = new ExchangeModel();
    });
    return mExchangeModel;
}

QVariant ExchangeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return ("Pair");
            case 1:
                return ("Price");
            case 2:
                return ("24H");
            default:
                break;
            }
        }

        if (orientation == Qt::Vertical) {
            return QString::number(section+1);
        }
    }

    return QVariant{};
}

int ExchangeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return mList.size();

}

int ExchangeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant ExchangeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        if( index.column() == 0 ){
            return mList[index.row()].pair();
        }
        if( index.column() == 1 ){
            double price = 0;
            for( const auto &item : mPriceList ){
                if( item.symbol() == mList[index.row()].pair() ){
                    price = item.lastPrice();
                    break;
                }
            }
            return price;
        }
        if( index.column() == 2 ){
            double priceChangePercent = 0;
            for( const auto &item : mPriceList ){
                if( item.symbol() == mList[index.row()].pair() ){
                    priceChangePercent = item.priceChangePercent();
                    break;
                }
            }
            return priceChangePercent;
        }
        break;
    case Role::quoteAsset:
        return mList[index.row()].quoteAsset();
        break;
    case Role::status:
        return mList[index.row()].status();
        break;
    case Role::SYMBOL:
        return mList[index.row()];
    case Role::pair:
        return mList[index.row()].pair();
        break;
    default:
        break;
    }





    return QVariant();
}

void ExchangeModel::updateInfo()
{
    mRequestType = exchangeInfo;
    mManager->get(QNetworkRequest(QUrl("https://fapi.binance.com/fapi/v1/exchangeInfo")));
}

void ExchangeModel::updatePricetoPercent()
{
    mRequestType = price;
    /// ALL most recent Price
    //mManager->get(QNetworkRequest(QUrl("https://fapi.binance.com/fapi/v1/ticker/price")));

    /// 24H Most Recent Price
    mManager->get(QNetworkRequest(QUrl("https://fapi.binance.com/fapi/v1/ticker/24hr")));
}

QVector<Binance::Public::RestAPI::Symbol> ExchangeModel::list() const
{
    return mList;
}

void ExchangeModel::setHideNONTRADING(bool newHideNONTRADING)
{
    mHideNONTRADING = newHideNONTRADING;
    setQuotaFilterKey(mQuotaFilterKey);
}

void ExchangeModel::setQuotaFilterKey(const QString &newQuotaFilterKey)
{
    mQuotaFilterKey = newQuotaFilterKey;

    beginResetModel();
    mList.clear();
    for( const auto &item : mFullList ){
        if( mHideNONTRADING ){
            if( item.status() == "TRADING" ){
                if( mQuotaFilterKey == "ALL" ){
                    mList.append(item);
                }else if( mQuotaFilterKey == item.quoteAsset() ){
                    mList.append(item);
                }
            }
        }else{
            if( mQuotaFilterKey == "ALL" ){
                mList.append(item);
            }else if( mQuotaFilterKey == item.quoteAsset() ){
                mList.append(item);
            }
        }

    }
    endResetModel();
}

bool ExchangeModel::saveList()
{
    QFile file("exchangeinfo.dat");

    if( file.exists() ){
        file.remove();
    }


    if( file.open(QIODevice::ReadWrite) ){
        QDataStream in(&file);
        in << mFullList.size();

        for( const auto &item : mFullList ){
            in << item;
        }

        file.close();
        return true;
    }
    return false;

}

bool ExchangeModel::loadList()
{
    QFile file("exchangeinfo.dat");

    if( file.open(QIODevice::ReadOnly ) ){
        QDataStream in(&file);
        qsizetype size;
        in >> size;

        qDebug() << "Size" <<size;

        for( int i = 0 ; i < size ; i++ ){
            Binance::Public::RestAPI::Symbol symbol;
            in >> symbol;
            mFullList.append(symbol);
        }

        file.close();


        return true;
    }

    return false;
}

QSortFilterProxyModel *ExchangeModel::model() const
{
    return mModel;
}

void ExchangeModel::setFilter(const QString &filter)
{
    mModel->setFilterFixedString(filter);
}

void ExchangeModel::sort(int column, Qt::SortOrder order)
{
    qDebug() << "Sorting" << column << order;
}

} // namespace ExchangeInfo
