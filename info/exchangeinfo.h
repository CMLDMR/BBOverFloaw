#ifndef EXCHANGEINFO_H
#define EXCHANGEINFO_H

#include <QWidget>
#include <QStyledItemDelegate>
#include <QPainter>

class TableViewDelegateWritable : /*public QObject,*/ public QStyledItemDelegate
{
    //    Q_OBJECT
    //    Q_INTERFACES(QStyledItemDelegate)
public:
    explicit TableViewDelegateWritable(QObject *parent = 0)
        : QStyledItemDelegate(parent)
    {
    }

    // background color manipulation
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        if( mSelectedList.contains(index.data().toString()) ){
            QColor background = QColor(135, 206, 255); // RGB value: https://www.rapidtables.com/web/color/blue-color.html
            painter->fillRect(option.rect, background);
        }


        // Paint text
        QStyledItemDelegate::paint(painter, option, index);
    }



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




namespace Ui {
class ExchangeInfo;
}

namespace ExchangeInfo{

class ExchangeModel;

class ExchangeInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ExchangeInfo(QWidget *parent = nullptr);
    ~ExchangeInfo();

    ExchangeModel *model() const;



signals:
    void selectedPair( const QString &pairName );

private:
    Ui::ExchangeInfo *ui;
    ExchangeModel* mModel;


    TableViewDelegateWritable* mTableViewDelegate;


};

}



#endif // EXCHANGEINFO_H
