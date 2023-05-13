#ifndef SCREEN_CANDLESTICKWINDOW_H
#define SCREEN_CANDLESTICKWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "graphicview.h"
#include "scene.h"

namespace Main{
class Series;
}

namespace Screen {

namespace Ui {
class CandleStickWindow;
}

class CandleStickWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CandleStickWindow(QWidget *parent = nullptr);
    ~CandleStickWindow();

    void setSeries(QVector<Main::Series *> *newSeries);

private:
    Ui::CandleStickWindow *ui;

    QVector<Main::Series*> *mSeries;

    GraphicView* mGraphicView;
    Scene* mScene;


    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;


    // QWidget interface
protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};


} // namespace Screen
#endif // SCREEN_CANDLESTICKWINDOW_H
