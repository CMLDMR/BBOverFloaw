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

    mView = new GraphicsView(mSeries);

    ui->gridLayout->addWidget(mView,0,0);

}

ChartWidget::~ChartWidget()
{
    delete ui;
}

void ChartWidget::addChart(const int row, const int column, Series::Seri *_mSeri)
{
//    auto vLayout = new QVBoxLayout();
//    ui->gridLayout->addLayout(vLayout,row,column);

//    chartView = new QChartView();
//    vLayout->addWidget(chartView);


//    QList<QCandlestickSet*> setList;
//    QBarSet* mBuySideBar = new QBarSet("Buy");
//    QBarSet* mSellSideBar = new QBarSet("Sell");

//    for( const auto &item : *_mSeri){

//        QCandlestickSet* set = new QCandlestickSet(item.openPrice(),
//                                                   item.highPrice(),
//                                                   item.lowPrice(),
//                                                   item.closePrice(),
//                                                   item.openTime());
//        setList.append(set);
//        mBuySideBar->append(item.takerBuyQuoteAssetVolume());
//        mSellSideBar->append(item.quoteAssetVolume() - item.takerBuyQuoteAssetVolume());

//    }




//    QCandlestickSeries *acmeSeries = new QCandlestickSeries();
//    acmeSeries->setName(mSeries->pair());
//    acmeSeries->append(setList);
//    acmeSeries->setIncreasingColor(QColor(Qt::green));
//    acmeSeries->setDecreasingColor(QColor(Qt::red));
//    acmeSeries->setCapsWidth(.05);


//    QChart *chart = new QChart();
//    chart->addSeries(acmeSeries);
//    chart->setTitle(_mSeri->interval());
//    //    chart->setAnimationOptions(QChart::SeriesAnimations);
//    chart->createDefaultAxes();


//    QBarSeries *series = new QBarSeries();
////    series->append(mBuySideBar);
////    series->append(mSellSideBar);

//    chart->addSeries(series);
//    QBarCategoryAxis *axisX = new QBarCategoryAxis();
//    chart->addAxis(axisX, Qt::AlignBottom);
//    series->attachAxis(axisX);
//    acmeSeries->attachAxis(axisX);


//    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
////    axisY->setMax(axisY->max() * 1.001);
////    axisY->setMin(axisY->min() * 0.999);

//    //                chart->addSeries(acmeSeries);

//    chartView->setChart(chart);


//    acmeSeries->setUseOpenGL(true);

//    QObject::connect(mSeries,&Series::Series::dataUpdated,[=](const bool &newCandle){

//        if( newCandle ){
//            auto item = _mSeri->kLineContainer().last();
//            QCandlestickSet* set = new QCandlestickSet(item.openPrice(),
//                                                       item.highPrice(),
//                                                       item.lowPrice(),
//                                                       item.closePrice(),
//                                                       item.openTime());
//            acmeSeries->append(set);
//            acmeSeries->remove(acmeSeries->sets().first());
//        }else{
//            acmeSeries->sets().last()->setClose(_mSeri->close());
//            mBuySideBar->replace(mBuySideBar->count()-1,_mSeri->kLineContainer().last().takerBuyQuoteAssetVolume());
////            qDebug() <<newCandle << "TakerBuy Asset Volume: " <<_mSeri->kLineContainer().last().takerBuyQuoteAssetVolume().toDouble();
//        }

////        axisY->setMax(axisY->max() * 1.001);
////        axisY->setMin(axisY->min() * 0.999);



//    });





}

} // namespace Chart
