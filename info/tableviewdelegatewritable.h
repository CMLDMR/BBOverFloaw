#ifndef EXCHANGEINFO_TABLEVIEWDELEGATEWRITABLE_H
#define EXCHANGEINFO_TABLEVIEWDELEGATEWRITABLE_H

#include <QStyledItemDelegate>
#include <QPainter>

namespace ExchangeInfo {


class TableViewDelegateWritable : /*public QObject,*/ public QStyledItemDelegate
{
    //    Q_OBJECT
    //    Q_INTERFACES(QStyledItemDelegate)
public:
    explicit TableViewDelegateWritable(QObject *parent = 0);

    // background color manipulation
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;



    //    // only allow digits
    //    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const
    //    {
    //        QSpinBox *editor = new QSpinBox(parent);

    //        editor->setMinimum(-99999);
    //        editor->setMaximum(99999);

    //        return editor;
    //    }
    void append( QString symbol );

    QStringList mSelectedList;

};


} // namespace ExchangeInfo

#endif // EXCHANGEINFO_TABLEVIEWDELEGATEWRITABLE_H
