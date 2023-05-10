#include "exchangemodel.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>


namespace ExchangeInfo {

ExchangeModel::ExchangeModel(QObject *parent)
    : QAbstractTableModel(parent)
{

    mModel = new QSortFilterProxyModel();
    mModel->setSourceModel(this);


    mManager = new QNetworkAccessManager(parent);

    QObject::connect(mManager,&QNetworkAccessManager::finished,[=](QNetworkReply* reply ){

        auto obj = QJsonDocument::fromJson(reply->readAll()).object();

        auto asset = obj.value("symbols").toArray();

        beginResetModel();
        for( const auto &item : asset ){
            if( item.toObject().value("marginAsset").toString() == "USDT" ){
                mList.append(item.toObject());
            }
        }
        endResetModel();
    });
    mManager->get(QNetworkRequest(QUrl("https://fapi.binance.com/fapi/v1/exchangeInfo")));
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
            default:
                break;
            }
        }
    }

    return QVariant{};
}

int ExchangeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return mList.size();

    // FIXME: Implement me!
}

int ExchangeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 1;
    // FIXME: Implement me!
}

QVariant ExchangeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!

    switch (role) {
    case Qt::DisplayRole:
        return mList[index.row()].getPair();
        break;
    default:
        break;
    }





    return QVariant();
}

QSortFilterProxyModel *ExchangeModel::model() const
{
    return mModel;
}

void ExchangeModel::sort(int column, Qt::SortOrder order)
{
    qDebug() << "Sorting" << column << order;
}


QString Symbol::getPair() const
{
    return value("pair").toString();
}

QString Symbol::getMarginAsset() const
{
    return value("marginAsset").toString();
}

} // namespace ExchangeInfo
