#ifndef SCREEN_CANDLESTICK_H
#define SCREEN_CANDLESTICK_H

#include <QObject>
#include <QGraphicsItem>
#include <QVector>




namespace Screen {

class CandleStickItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit CandleStickItem(QObject *parent = nullptr);
    virtual ~CandleStickItem(){
    }

signals:


private:


    bool mTrackMousePos{false};
    QPointF mMousePoistion;

    double mLowestPrice{0};
    double mHighesPrice{0};


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;



protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;

    // QGraphicsItem interface
protected:
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

} // namespace Screen

#endif // SCREEN_CANDLESTICK_H
