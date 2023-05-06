#ifndef BOLLINGER_NEARMODEL_H
#define BOLLINGER_NEARMODEL_H

#include <QAbstractTableModel>

namespace Bollinger {

class NearModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit NearModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

} // namespace Bollinger

#endif // BOLLINGER_NEARMODEL_H
