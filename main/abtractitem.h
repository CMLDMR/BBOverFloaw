#ifndef MAIN_ABTRACTITEM_H
#define MAIN_ABTRACTITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsColorizeEffect>

namespace Main {

class AbtractItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit AbtractItem(QObject *parent = nullptr);



signals:
    void deleteClicked();
    void openCandled(const QPoint&);
    void openUrlCliked();
    void openInTradingView();
    void openVolumeGraph();

private:
    enum class MouseState{
        Clicked = 0,
        Hovered,
        Out
    };

    MouseState mMouseStat = MouseState::Out;

    QGraphicsDropShadowEffect* mSelectedItemEffect{nullptr};
    QGraphicsColorizeEffect* mOnClickedEffect{nullptr};

    bool mSelectedItem{false};

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    bool selectedItem() const;

protected:
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

};

} // namespace Main

#endif // MAIN_ABTRACTITEM_H
