#include "exchangeinfo.h"
#include "ui_exchangeinfo.h"

#include "exchangemodel.h"

#include <QThread>
#include <QTest>






ExchangeInfo::ExchangeInfo::ExchangeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExchangeInfo)
{
    ui->setupUi(this);
    ui->lineEdit_filter->setPlaceholderText("Filter By Name");

    mModel = ExchangeModel::instance();

    ui->tableView->setModel(ExchangeModel::instance()->model());
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    mTableViewDelegate = new TableViewDelegateWritable(ui->tableView);


    QObject::connect(ui->tableView,&QTableView::doubleClicked,[=, this]( const QModelIndex &index){
        if( index.data(ExchangeModel::status).toString() == "TRADING" ){
            emit selectedPair(index.data(ExchangeModel::pair).toString());
            mTableViewDelegate->append(index.data().toString());
        }
    });

    QObject::connect(ui->pushButton_addALL,&QPushButton::clicked , this ,[=,this](){

        for( int i = 0 ; i < mModel->rowCount() ; i++ ) {
            const auto &index = mModel->index( i  , 0 );
            if( index.data(ExchangeModel::status).toString() == "TRADING" ){
                emit selectedPair(index.data(ExchangeModel::pair).toString());
                mTableViewDelegate->append(index.data().toString());
                QTest::qWait( 500 );
            }
        }


    });

    QObject::connect(ui->lineEdit_filter,&QLineEdit::textChanged,[=, this](const QString &text){
        mModel->setFilter(text);
    });


    for(int c = 0; c < ui->tableView->model()->columnCount(); c++)
    {
        ui->tableView->setItemDelegateForColumn(c, mTableViewDelegate);
    }

    QObject::connect(ui->pushButton_updateInfo,&QPushButton::clicked,[=](){
        mModel->updateInfo();
    });

    QObject::connect(ui->comboBox_quotaAsset,&QComboBox::textActivated,[=](const QString &name){
        mModel->setQuotaFilterKey(name);
    });
    QObject::connect(ui->checkBox_isTrading,&QCheckBox::clicked,[=](const bool &checked){
        mModel->setHideNONTRADING(checked);
    });

    QObject::connect(ui->pushButton_updatePrice,&QPushButton::clicked,[=](){
        mModel->updatePricetoPercent();
    });
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

void ExchangeInfo::append(const QString &selectedCoin)
{
    mTableViewDelegate->append(selectedCoin);
}



}

