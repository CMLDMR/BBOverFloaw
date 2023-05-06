#ifndef MAIN_VIEWPORT_H
#define MAIN_VIEWPORT_H

#include <QGraphicsView>
#include <QObject>

class QGraphicsScene;

namespace Main {

class ViewScene;

class ViewPort : public QGraphicsView
{
    Q_OBJECT
public:
    ViewPort();


private:
    ViewScene* mScene;


};

} // namespace Main

#endif // MAIN_VIEWPORT_H
