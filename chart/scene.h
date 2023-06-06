#ifndef CHART_SCENE_H
#define CHART_SCENE_H

#include <QGraphicsScene>
#include <QObject>

namespace Chart {

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
};

} // namespace Chart

#endif // CHART_SCENE_H
