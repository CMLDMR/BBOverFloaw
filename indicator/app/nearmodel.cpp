#include "nearmodel.h"

namespace Bollinger {

NearModel::NearModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant NearModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant{};
}

int NearModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;


    return 1;
}

int NearModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 1;
}

QVariant NearModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    return QVariant();
}

} // namespace Bollinger
