#include "scene.h"
#include <QDebug>

#include <QGraphicsSceneMouseEvent>

namespace Screen {

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}
{

}

} // namespace Screen


void Screen::Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "GraphicsScene Mouse Move" << event->scenePos();
    QGraphicsScene::mouseMoveEvent(event);
}
