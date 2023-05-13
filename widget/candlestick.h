#ifndef SCREEN_CANDLESTICK_H
#define SCREEN_CANDLESTICK_H

#include <QObject>
#include <QGraphicsItem>
#include <QVector>

namespace Main{
class Series;
}

namespace Screen {

class CandleStickItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit CandleStickItem(QObject *parent = nullptr);
    virtual ~CandleStickItem(){
        mSeries = nullptr;
    }

signals:


private:

    Main::Series* mSeries{nullptr};

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;





    // QGraphicsItem interface
    void setSeries(Main::Series *newSeries);

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
};

} // namespace Screen

#endif // SCREEN_CANDLESTICK_H
