#ifndef CHART_CHARTWIDGET_H
#define CHART_CHARTWIDGET_H

#include <QWidget>
#include <QChart>
#include <QChartView>


namespace Chart {

namespace Ui {
class ChartWidget;
}

class ChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWidget(QWidget *parent = nullptr);
    ~ChartWidget();

private:
    Ui::ChartWidget *ui;

    QChartView *chartView;
};


} // namespace Chart
#endif // CHART_CHARTWIDGET_H
