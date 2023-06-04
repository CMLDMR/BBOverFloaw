#include "chartwidget.h"
#include "ui_chartwidget.h"

#include "series/series.h"
#include "series/seri.h"

#include <QCandlestickSeries>
#include <QCandlestickSet>
#include <QBarCategoryAxis>
#include <QValueAxis>


namespace Chart {

ChartWidget::ChartWidget(Series::Series *_mSeries, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartWidget),
    mSeries(_mSeries)
{
    ui->setupUi(this);


    int row = 0, column = 0;
    for(const  auto &item : mSeries->seriList() ){
        addChart(row,column,item);
        column++;
        if( column >= 2 ){
            column = 0;
            row++;
        }
    }










}

ChartWidget::~ChartWidget()
{
    delete ui;
}

void ChartWidget::addChart(const int row, const int column, Series::Seri *_mSeri)
{
    chartView = new QChartView();
    ui->gridLayout->addWidget(chartView,row,column);

    QList<QCandlestickSet*> setList;

    for( const auto &item : *_mSeri){

        QCandlestickSet* set = new QCandlestickSet(item.openPrice().toDouble(),
                                                   item.highPrice().toDouble(),
                                                   item.lowPrice().toDouble(),
                                                   item.closePrice().toDouble(),
                                                   item.openTime());
        setList.append(set);
    }


    QCandlestickSeries *acmeSeries = new QCandlestickSeries();
    acmeSeries->setName(mSeries->pair());
    acmeSeries->append(setList);
    acmeSeries->setIncreasingColor(QColor(Qt::green));
    acmeSeries->setDecreasingColor(QColor(Qt::red));
    acmeSeries->setCapsWidth(.05);


    QChart *chart = new QChart();
    chart->addSeries(acmeSeries);
    chart->setTitle(_mSeri->interval());
    //    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes();


    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.001);
    axisY->setMin(axisY->min() * 0.999);

    //                chart->addSeries(acmeSeries);

    chartView->setChart(chart);

    acmeSeries->setUseOpenGL(true);

    QObject::connect(mSeries,&Series::Series::dataUpdated,[=](const bool &newCandle){
        acmeSeries->sets().last()->setClose(mSeries->close());
    });
}

} // namespace Chart
