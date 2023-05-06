#include "nearmodel.h"

namespace Bollinger {

NearModel::NearModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant NearModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    return QVariant{};
}

int NearModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;


    return 1;
    // FIXME: Implement me!
}

int NearModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 1;
    // FIXME: Implement me!
}

QVariant NearModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

} // namespace Bollinger
