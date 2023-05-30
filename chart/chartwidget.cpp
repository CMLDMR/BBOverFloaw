#include "chartwidget.h"
#include "ui_chartwidget.h"

namespace Chart {

ChartWidget::ChartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartWidget)
{
    ui->setupUi(this);

    chartView = new QChartView();

    ui->gridLayout->addWidget(chartView,0,0);
}

ChartWidget::~ChartWidget()
{
    delete ui;
}

} // namespace Chart
