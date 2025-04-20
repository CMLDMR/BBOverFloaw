#ifndef CHART_CHARTWIDGET_H
#define CHART_CHARTWIDGET_H

#include <QWidget>


namespace Series{
    class Series;
    class Seri;
};

namespace Chart {

class GraphicsView;


namespace Ui {
class ChartWidget;
}

class ChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWidget(Series::Series* _mSeries, QWidget *parent = nullptr);
    ~ChartWidget();

private slots:
    void on_zoomOutPushButton_clicked();

    void on_zoomInPushButton_clicked();

private:
    Ui::ChartWidget *ui;

    GraphicsView *mView;

    Series::Series* mSeries;

    qreal m_xScaleFactor{ 1 };
    qreal m_yScaleFactor{ 1 };

};


} // namespace Chart
#endif // CHART_CHARTWIDGET_H
