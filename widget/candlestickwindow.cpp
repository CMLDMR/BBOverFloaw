#include "candlestickwindow.h"
#include "ui_candlestickwindow.h"

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



void CandleStickWindow::timerEvent(QTimerEvent *event)
{
}

} // namespace Screen


void Screen::CandleStickWindow::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}
