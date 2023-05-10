#ifndef EXCHANGEINFO_EXCHANGEMODEL_H
#define EXCHANGEINFO_EXCHANGEMODEL_H

#include <QAbstractTableModel>

#include <QVector>
#include <QJsonObject>
#include <QSortFilterProxyModel>


class QNetworkAccessManager;

namespace ExchangeInfo {


class Symbol : public QJsonObject
{
public:
    Symbol(){}

    Symbol( const QJsonObject &other ){
        for( const auto &key : other.keys() ){
            this->insert(key,other[key]);
        }
    }

    QString getPair() const;
    QString getMarginAsset() const;


};



class ExchangeModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ExchangeModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


private:


    QNetworkAccessManager* mManager;

    QVector<Symbol> mList;

    QSortFilterProxyModel* mModel;



    // QAbstractItemModel interface
public:
    virtual void sort(int column, Qt::SortOrder order) override;
    QSortFilterProxyModel *model() const;
};

} // namespace ExchangeInfo

#endif // EXCHANGEINFO_EXCHANGEMODEL_H
