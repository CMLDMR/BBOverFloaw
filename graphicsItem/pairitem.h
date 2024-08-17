#ifndef GRAPHIC_PAIRITEM_H
#define GRAPHIC_PAIRITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QAction>
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
    void openVolumePercent();

    void sort(const QString &);
    void autoSort( const bool , const QString &);
    void alarmed( const QString &);

    void viewOnlyPositive( const bool );


    void openOrderTimeLineBook();

    void openVolumeGraph();



    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QString pair() const;

    Series::Series *series() const;

    void setFocusIndicate(bool newFocusIndicate);

private:
    Series::Series *mSeries{nullptr};

    bool mSelected{false};
    bool mHovered{false};
    bool mFocusIndicate{false};
    bool mViewOnlyPositiveLine{true};
    QString mPair;

    qreal mWidth{285};
    qreal mHeight{170};

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


private:
    QAction* createAction( QMenu* menu, const QString &title , const QString &interval );

    QAction* m_ema20AutoSort1m { nullptr };
    QAction* m_ema20AutoSort5m { nullptr };
    QAction* m_ema20AutoSort15m { nullptr };
    QAction* m_ema20AutoSort1h { nullptr };
    QAction* m_ema20AutoSort4h { nullptr };
    QAction* m_ema20AutoSort1d { nullptr };
    QAction* m_ema20AutoSort1w { nullptr };




};

} // namespace Graphic

#endif // GRAPHIC_PAIRITEM_H
