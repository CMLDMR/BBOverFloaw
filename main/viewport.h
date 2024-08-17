#ifndef MAIN_VIEWPORT_H
#define MAIN_VIEWPORT_H

#include <QGraphicsView>
#include <QObject>
#include <vector>
#include <QMetaObject>

#include "global/alarmwidget.h"


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
    ViewPort( QWidget *parent = nullptr );

    void addItem( const QString &pairName );


private:
    ViewScene* mScene;


    int mAddedInternal{0};
    int rowCount{0};

//    QStringList mPairList;

    QVector<Screen::CandleStickWindow*> mWindowList;

    std::vector<Graphic::PairItem*> mItemList;

    const int mMaxRowCount{8};


    QTimer * m_autoSortTimer { nullptr };
    bool m_autoSortEnabled = false;
    QString m_sortParameter;

private slots:
    void autoSort();

private:
    void sortPairs(const QString &interval );

    const int m_leftRightMargin = 15;
    const int m_topBottomMargin = 3;

    Global::Alarm::AlarmWidget* m_alarmWidget { nullptr };




    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
};

} // namespace Main

#endif // MAIN_VIEWPORT_H
