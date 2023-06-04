#ifndef CHART_CHARTWIDGET_H
#define CHART_CHARTWIDGET_H

#include <QWidget>
#include <QChart>
#include <QChartView>

namespace Series{
    class Series;
    class Seri;
};

namespace Chart {

namespace Ui {
class ChartWidget;
}

class ChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWidget(Series::Series* _mSeries, QWidget *parent = nullptr);
    ~ChartWidget();

private:
    Ui::ChartWidget *ui;

    QChartView *chartView;

    Series::Series* mSeries;

    void addChart(const int row , const int column , Series::Seri* _mSeri);

};


} // namespace Chart
#endif // CHART_CHARTWIDGET_H
