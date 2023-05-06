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

}

ExchangeInfo::ExchangeInfo::~ExchangeInfo()
{
    delete ui;
}
