#ifndef MAIN_VIEWSCENE_H
#define MAIN_VIEWSCENE_H

#include <QGraphicsScene>
#include <QObject>

namespace Main {

class ViewScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ViewScene(QObject *parent = nullptr);
};

} // namespace Main

#endif // MAIN_VIEWSCENE_H
