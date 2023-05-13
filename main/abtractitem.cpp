#include "abtractitem.h"

#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QGraphicsColorizeEffect>
#include <QApplication>
#include <QPainter>



namespace Main {

AbtractItem::AbtractItem(QObject *parent)
    : QObject{parent}
{
//    setFlag(ItemIsMovable);
    this->setAcceptHoverEvents(true);

}

bool AbtractItem::selectedItem() const
{
    return mSelectedItem;
}

void AbtractItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{



}

void AbtractItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug() << event->scenePos();


    QGraphicsItem::hoverMoveEvent(event);
}

void AbtractItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if( event->button() == Qt::RightButton ){
        QMenu menu;
        if( mSelectedItem ){
            menu.addAction("UnSelect",[=](){
                mSelectedItem = false;
            });
        }else{
            menu.addAction("Select",[=](){
                mSelectedItem = true;
            });
        }
        menu.addSeparator();
        menu.addAction("Open Candle Stick",[=](){
            emit openCandled(event->screenPos());
        });
        menu.addAction("Delete Pair",[=](){
            emit deleteClicked();
        });
        menu.exec(event->screenPos());
    }
//    QGraphicsItem::mousePressEvent(event);
}

void AbtractItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if( !mSelectedItemEffect ){
        mSelectedItemEffect = new QGraphicsDropShadowEffect();
        mSelectedItemEffect->setBlurRadius(20);
        mSelectedItemEffect->setOffset(0);
    }
    this->setGraphicsEffect(mSelectedItemEffect);

    QGraphicsItem::hoverEnterEvent(event);
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void AbtractItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{

    this->setGraphicsEffect(nullptr);
    mSelectedItemEffect = nullptr;
    QGraphicsItem::hoverLeaveEvent(event);
    QApplication::restoreOverrideCursor();
}



} // namespace Main
