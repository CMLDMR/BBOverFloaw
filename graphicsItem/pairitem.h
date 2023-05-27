#ifndef GRAPHIC_PAIRITEM_H
#define GRAPHIC_PAIRITEM_H

#include <QObject>
#include <QGraphicsItem>
#include "series/series.h"


namespace Graphic {

class PairItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit PairItem(QObject *parent = nullptr);

signals:


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Series::Series *mSeries;
};

} // namespace Graphic

#endif // GRAPHIC_PAIRITEM_H
