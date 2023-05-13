#ifndef EXCHANGEINFO_EXCHANGEMODEL_H
#define EXCHANGEINFO_EXCHANGEMODEL_H

#include <QAbstractTableModel>

#include <QVector>
#include <QJsonObject>
#include <QSortFilterProxyModel>
#include "symbol.h"
#include "ticker.h"
#include "ticker24h.h"


class QNetworkAccessManager;

namespace ExchangeInfo {


class ExchangeModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ExchangeModel(QObject *parent = nullptr);

    static ExchangeModel* instance() ;

    enum Role{
        displayRole = Qt::DisplayRole,
        baseAsset = Qt::UserRole+1,
        pair,
        marginAsset,
        quoteAsset,
        symbol,
        status,
        SYMBOL
    };

    enum RequestType{
        exchangeInfo,
        price,
        percent
    };

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    void updateInfo();

    void updatePricetoPercent();
private:

    static ExchangeModel* mExchangeModel;


    QNetworkAccessManager* mManager;

    QVector<Symbol> mList;
    QVector<Symbol> mFullList;
    QVector<Ticker24H> mPriceList;
    QVector<Symbol> mPercentList;

    QString mQuotaFilterKey{"ALL"};
    bool mHideNONTRADING{false};
    bool saveList();
    bool loadList();

    QSortFilterProxyModel* mModel;

    RequestType mRequestType{exchangeInfo};



    // QAbstractItemModel interface
public:
    virtual void sort(int column, Qt::SortOrder order) override;
    QSortFilterProxyModel *model() const;
    void setFilter(const QString &filter );
    void setQuotaFilterKey(const QString &newQuotaFilterKey);
    void setHideNONTRADING(bool newHideNONTRADING);
    QVector<Symbol> list() const;
};

} // namespace ExchangeInfo

#endif // EXCHANGEINFO_EXCHANGEMODEL_H
