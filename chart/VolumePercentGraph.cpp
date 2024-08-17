#include "VolumePercentGraph.h"
#include "series/series.h"

#include <QTimer>

VolumePercentGraph::VolumePercentGraph(const QString &_mPair)
    :m_pair( _mPair )
{
    m_candle.close = 0;
    m_candle.nextCandle();

    QTimer* timer = new QTimer();
    connect( timer , &QTimer::timeout , this , [=,this](){
        getNextCandle = true;
    });

    timer->start( 10000 );

}

void VolumePercentGraph::addAggregate(const Binance::Public::WebSocketAPI::Aggregate &aggregate)
{
    m_candle.update( aggregate );

    if( getNextCandle ) {
        getNextCandle = false;
        m_candleList.push_back( m_candle );
    }

    this->update();


}


QRectF VolumePercentGraph::boundingRect() const
{
    return QRectF( 0 , 0 , m_width , m_height );
}

void VolumePercentGraph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{


    int index = 1;
    const int heightIndex = 18;
    const double fullPercent = 200;

    for( const auto &candle : m_candleList ) {
        painter->fillRect(QRectF( 20 , heightIndex*(index-1)+5 , fullPercent , heightIndex ) , QBrush(QColor(255,100,100)));

        painter->fillRect(QRectF( 20 , heightIndex*(index-1)+5 , fullPercent * candle.buyPercent() , heightIndex ) , QBrush(QColor(100,255,100)));

        painter->drawText( 20 , heightIndex*index , QString("%1 %2  ||  P%3 %4")
                                                       .arg(formatLargeNumber(candle.buyVolume).data())
                                                       .arg(formatLargeNumber(candle.sellVolume).data())
                                                       .arg(formatLargeNumber(candle.buyPercent()).data())
                                                       .arg(candle.close));

        index++;
    }
    painter->fillRect(QRectF( 20 , heightIndex*(index-1)+5 , fullPercent , heightIndex ) , QBrush(QColor(255,100,100)));

    painter->fillRect(QRectF( 20 , heightIndex*(index-1)+5 , fullPercent * m_candle.buyPercent() , heightIndex ) , QBrush(QColor(100,255,100)));
    painter->drawText( 20 , heightIndex*index , QString("%1 %2  ||  P%3 %4")
                                                   .arg(formatLargeNumber(m_candle.buyVolume).data())
                                                   .arg(formatLargeNumber(m_candle.sellVolume).data())
                                                   .arg(formatLargeNumber(m_candle.buyPercent()).data())
                                                   .arg(m_candle.close));
    m_height = heightIndex*index + 10 ;

    painter->drawRect( this->boundingRect() );

}
VolumePercentGraphWidget::VolumePercentGraphWidget( Series::Series* _series , QWidget *parent)
    :QGraphicsView( parent )
    , m_series( _series )
{
    m_scene = new QGraphicsScene( this );

    this->setScene( m_scene );

    m_volumePercentGraph = new VolumePercentGraph("BTCUSDT");

    m_scene->addItem( m_volumePercentGraph );

    connect( m_series , &Series::Series::aggregateSignal , this , [=, this](const Binance::Public::WebSocketAPI::Aggregate &aggregate){

        m_volumePercentGraph->addAggregate( aggregate );
        // this->setGeometry( this->geometry().x() , this->geometry().y() , m_volumePercentGraph->boundingRect().width() * 1.1 , m_volumePercentGraph->boundingRect().height() *1.1 );

    });

    // this->setGeometry( this->geometry().x() , this->geometry().y() , m_volumePercentGraph->boundingRect().width() * 1.1 , m_volumePercentGraph->boundingRect().height() *1.1 );
}

void Candle::update(const Binance::Public::WebSocketAPI::Aggregate &aggregate)
{
    this->close = aggregate.price();
    if( high < close ) high = close;
    if( low > close ) low = close;

    if( aggregate.isMaker() ) {
        buyVolume += aggregate.price() * aggregate.quantity();
    }
    else{
        sellVolume += aggregate.price() * aggregate.quantity();
    }
}
