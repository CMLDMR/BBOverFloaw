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
    explicit PairItem(const QString &_pair , QObject *parent = nullptr);

signals:

    void openCandles(const QPoint &);
    void openUrlCliked();
    void openInTradingView();

    void sort5m();
    void sort15m();
    void sort1h();

    void sortAllm();

    void sort(const QString &);


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QString pair() const;

    Series::Series *series() const;

    void setFocusIndicate(bool newFocusIndicate);

private:
    Series::Series *mSeries;

    bool mSelected{false};
    bool mHovered{false};
    bool mFocusIndicate{false};
    QString mPair;

    qreal mWidth{285};
    qreal mHeight{140};

    int colorGradient{0};
    bool mAlarmActivated{false};
    int mUpdateDuration{0};

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    // QGraphicsItem interface
protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

} // namespace Graphic

#endif // GRAPHIC_PAIRITEM_H
