#include "candlestickwindow.h"
#include "ui_candlestickwindow.h"
#include "candlestick.h"
#include "main/series.h"
#include "main/candleitem.h"

#include <QMouseEvent>

namespace Screen {

CandleStickWindow::CandleStickWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CandleStickWindow)
{
    ui->setupUi(this);

//    this->setMouseTracking(true);
    mGraphicView = new GraphicView();
    ui->mMainLayout->addWidget(mGraphicView);

    mScene = new Scene();
    mGraphicView->setScene(mScene);
//    this->activateWindow();

//    this->setWindowFlags(Qt::WindowStaysOnTopHint);
}

CandleStickWindow::~CandleStickWindow()
{
    mGraphicView->deleteLater();
    mScene->deleteLater();
    delete ui;
}

void CandleStickWindow::setSeries(QVector<Main::Series_Legacy *> *newSeries)
{
    mSeries = newSeries;

    if( mSeries ){
        if( !mScene->items().size() ){
            int i = 0;
            int j = 0;
            for( auto &item : *mSeries ){
                auto seriItem = new CandleStickItem();
                seriItem->setSeries(item);
                seriItem->setPos(i*(seriItem->boundingRect().width()+15),j*(seriItem->boundingRect().height()+15));

                this->mScene->addItem(seriItem);
                i++;
                if( i >= 2 ){
                    i = 0;
                    j++;
                }
            }
        }
    }
}

void CandleStickWindow::timerEvent(QTimerEvent *event)
{
}

} // namespace Screen


void Screen::CandleStickWindow::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}
