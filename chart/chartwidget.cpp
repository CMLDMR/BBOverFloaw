#include "chartwidget.h"
#include "ui_chartwidget.h"

#include "series/series.h"
#include "series/seri.h"

#include "graphicsview.h"


namespace Chart {

ChartWidget::ChartWidget(Series::Series *_mSeries, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartWidget),
    mSeries(_mSeries)
{
    ui->setupUi(this);
    this->setWindowTitle("Multi Chart - " + mSeries->pair() );

    mView = new GraphicsView(mSeries);

    ui->gridLayout->addWidget(mView,0,0);

}

ChartWidget::~ChartWidget()
{
    delete ui;
}

} // namespace Chart
