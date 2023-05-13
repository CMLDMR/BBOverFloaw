#ifndef SCREEN_SCENE_H
#define SCREEN_SCENE_H

#include <QGraphicsScene>
#include <QObject>

namespace Screen {

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    // QGraphicsScene interface
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

} // namespace Screen

#endif // SCREEN_SCENE_H
