#include "bollignerbandpercent.h"
#include "ui_bollignerbandpercent.h"


#include "nearmodel.h"


Bollinger::BollignerBandPercent::BollignerBandPercent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BollignerBandPercent)
{
    ui->setupUi(this);

    mModel = new NearModel();
    ui->tableView->setModel(mModel);
}

Bollinger::BollignerBandPercent::~BollignerBandPercent()
{
    delete ui;
}
