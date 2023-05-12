#include "tableviewdelegatewritable.h"
#include "exchangemodel.h"

namespace ExchangeInfo {

TableViewDelegateWritable::TableViewDelegateWritable(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

void TableViewDelegateWritable::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if( index.data(ExchangeModel::status).toString() != "TRADING" ){
        QColor background = QColor(255, 50, 50); // RGB value: https://www.rapidtables.com/web/color/blue-color.html
        painter->fillRect(option.rect, background);
    }else{
        if( mSelectedList.contains(index.data().toString()) ){
            QColor background = QColor(135, 206, 255); // RGB value: https://www.rapidtables.com/web/color/blue-color.html
            painter->fillRect(option.rect, background);
        }else{
            if( index.data(ExchangeModel::quoteAsset).toString() == "BUSD" ){
                QColor background = QColor(255, 206, 150); // RGB value: https://www.rapidtables.com/web/color/blue-color.html
                painter->fillRect(option.rect, background);
            }else if (index.data(ExchangeModel::quoteAsset).toString() == "BTC") {
                QColor background = QColor(135, 255, 200); // RGB value: https://www.rapidtables.com/web/color/blue-color.html
                painter->fillRect(option.rect, background);
            }
        }
    }

    // Paint text
    QStyledItemDelegate::paint(painter, option, index);
}

void TableViewDelegateWritable::append(QString symbol)
{
    mSelectedList.append(symbol);
    mSelectedList.removeDuplicates();
}

} // namespace ExchangeInfo
