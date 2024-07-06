#include "OrderBookViewWidget.h"

#include "orderbookitem.h"
#include "OrderBookTimeLineDiff.h"


OrderBookViewWidget::OrderBookViewWidget(QWidget *parent)
    :QGraphicsView( parent )
{
    setWindowFlags( Qt::Tool | Qt::WindowStaysOnTopHint );

    m_scene = new QGraphicsScene( this );

    this->setScene( m_scene );


}

QString OrderBookViewWidget::pair() const
{
    return m_pair;
}

void OrderBookViewWidget::setPair(const QString &newPair)
{
    m_pair = newPair;

    setWindowTitle( m_pair );

    auto orderBook = new Main::OrderBookItem( m_pair );

    m_scene->addItem( orderBook );

    auto orderBookDiff = new OrderBookTimeLineDiff();

    m_scene->addItem( orderBookDiff );

    orderBookDiff->setPos(0,orderBook->boundingRect().height() + 10 );

    connect( orderBook , &Main::OrderBookItem::updatedOrderBookVol , orderBookDiff , &OrderBookTimeLineDiff::updateOrderBookVol );


}
