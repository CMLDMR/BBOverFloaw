#ifndef CHART_GRAPHICSVIEW_H
#define CHART_GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QObject>

namespace Series{
    class Series;
    class Seri;
};

namespace Chart {

class Scene;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(Series::Series* _series);


private:
    Scene* mScene;

    Series::Series* mSeries;

private slots:
    void reArrageItem();
};

} // namespace Chart

#endif // CHART_GRAPHICSVIEW_H
