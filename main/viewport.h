#ifndef MAIN_VIEWPORT_H
#define MAIN_VIEWPORT_H

#include <QGraphicsView>
#include <QObject>
#include <vector>

class QGraphicsScene;
namespace Screen{
class CandleStickWindow;
}

namespace Graphic{
class PairItem;
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


private:
    ViewScene* mScene;


    int mAddedInternal{0};
    int rowCount{0};

//    QStringList mPairList;

    QVector<Screen::CandleStickWindow*> mWindowList;

    std::vector<Graphic::PairItem*> mItemList;

    const int mMaxRowCount{10};





    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
};

} // namespace Main

#endif // MAIN_VIEWPORT_H
