#ifndef ORDERBOOKVIEWWIDGET_H
#define ORDERBOOKVIEWWIDGET_H

#include <QGraphicsView>
#include <QObject>
#include <QWidget>


class QGraphicsScene;

class OrderBookViewWidget : public QGraphicsView
{
    Q_OBJECT
public:
    OrderBookViewWidget( QWidget * parent = nullptr );


    QString pair() const;
    void setPair(const QString &newPair);

private:
    QString          m_pair;
    QGraphicsScene  *m_scene;
};

#endif // ORDERBOOKVIEWWIDGET_H
