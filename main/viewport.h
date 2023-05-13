#ifndef MAIN_VIEWPORT_H
#define MAIN_VIEWPORT_H

#include <QGraphicsView>
#include <QObject>

class QGraphicsScene;
namespace Screen{
class CandleStickWindow;
}


namespace Main {

class ViewScene;
class PairTableItem;

class ViewPort : public QGraphicsView
{
    Q_OBJECT
public:
    ViewPort();

    void addItem( const QString &pairName );
    void setPairItem( const QString &pairName );


private:
    ViewScene* mScene;


    int mAddedInternal{0};
    int rowCount{0};

//    QStringList mPairList;

    QVector<Screen::CandleStickWindow*> mWindowList;





    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
};

} // namespace Main

#endif // MAIN_VIEWPORT_H
