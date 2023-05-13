#include "graphicview.h"
#include <QDebug>
namespace Screen {

GraphicView::GraphicView()
{
    this->setMouseTracking(true);
}

} // namespace Screen


void Screen::GraphicView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}
