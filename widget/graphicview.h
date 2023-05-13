#ifndef SCREEN_GRAPHICVIEW_H
#define SCREEN_GRAPHICVIEW_H

#include <QGraphicsView>
#include <QObject>

namespace Screen {

class GraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicView();

    // QWidget interface
protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};

} // namespace Screen

#endif // SCREEN_GRAPHICVIEW_H
