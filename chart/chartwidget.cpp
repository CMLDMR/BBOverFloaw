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

    mView->setRenderHint(QPainter::Antialiasing); // Kenar yumuşatma


    ui->gridLayout->addWidget(mView,0,0);



}

ChartWidget::~ChartWidget()
{
    delete ui;
}

void ChartWidget::on_zoomOutPushButton_clicked()
{
    m_xScaleFactor = 1.25 * m_xScaleFactor;
    m_yScaleFactor = 1.25 * m_yScaleFactor;
    qDebug() << "Scale Factor: " << m_xScaleFactor << m_yScaleFactor;
    mView->scale( 1.25 , 1.25 );
}

void ChartWidget::on_zoomInPushButton_clicked()
{

    m_xScaleFactor = 0.8 * m_xScaleFactor;
    m_yScaleFactor = 0.8 * m_yScaleFactor;
    qDebug() << "Scale Factor: " << m_xScaleFactor << m_yScaleFactor;
    mView->scale( 0.8 , 0.8 );
}



} // namespace Chart
