#ifndef EXCHANGEINFO_H
#define EXCHANGEINFO_H

#include <QWidget>
#include <QStyledItemDelegate>

#include "tableviewdelegatewritable.h"



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

    void append( const QString &selectedCoin );


signals:
    void selectedPair( const QString &pairName );

private:
    Ui::ExchangeInfo *ui;
    ExchangeModel* mModel;


    TableViewDelegateWritable* mTableViewDelegate;


};

}



#endif // EXCHANGEINFO_H
