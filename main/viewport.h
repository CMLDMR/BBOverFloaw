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

    void addItem( const QString &pairName );

private:
    ViewScene* mScene;


    int mAddedInternal{0};
    int rowCount{0};

    QStringList pairList;


};

} // namespace Main

#endif // MAIN_VIEWPORT_H
