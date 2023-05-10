#include "exchangeinfo.h"
#include "ui_exchangeinfo.h"

#include "exchangemodel.h"








ExchangeInfo::ExchangeInfo::ExchangeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExchangeInfo)
{
    ui->setupUi(this);

    mModel = new ExchangeModel();

    ui->tableView->setModel(mModel);

    mTableViewDelegate = new TableViewDelegateWritable(ui->tableView);


    QObject::connect(ui->tableView,&QTableView::doubleClicked,[=]( const QModelIndex &index){
        emit selectedPair(index.data(Qt::DisplayRole).toString());
        mTableViewDelegate->append(index.data().toString());
//        ui->tableView->update();
    });


    for(int c = 0; c < ui->tableView->model()->columnCount(); c++)
    {
        ui->tableView->setItemDelegateForColumn(c, mTableViewDelegate);
    }

}

ExchangeInfo::ExchangeInfo::~ExchangeInfo()
{
    delete ui;
}


namespace ExchangeInfo {
ExchangeModel *ExchangeInfo::model() const
{
    return mModel;
}


}

void TableViewDelegateWritable::append(QString symbol)
{
    mSelectedList.append(symbol);
    mSelectedList.removeDuplicates();

}
