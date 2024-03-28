#include "OrderBookTimeLineDiff.h"

#include <QRectF>
#include <QPainter>
#include <QDateTime>

OrderBookTimeLineDiff::OrderBookTimeLineDiff()
{

}

void OrderBookTimeLineDiff::updateOrderBookVol(const qreal buySide, const qreal sellSide)
{


    m_updateTime = QDateTime::currentMSecsSinceEpoch();

    // yeni dakike geldiyse
    if( m_lastUpdateTime != QDateTime::currentDateTime().time().minute() ) {
        m_lastUpdateTime = QDateTime::currentDateTime().time().minute();

        if( ! firstAppen )
            m_list.prepend( { m_buySide , m_sellSide , m_updateRate } );

        firstAppen = false;

        m_buySide   = buySide;
        m_sellSide  = sellSide;
        m_updateRate = 1;
    }
    // emvcut dakikanon içerisindeyse
    else {
        m_updateRate++;
        // m_buySide   += /*qAbs*/( buySide - m_lastBuySide);
        // m_sellSide  += /*qAbs*/( sellSide - m_lastSellSide);;

        m_buySide   += buySide;
        m_sellSide  += sellSide;
    }

    // qDebug() << QDateTime::currentDateTime().time().toString("hh:mm:ss") << "BuySide: " << m_buySide << doubleToHumanReadable( m_buySide ) << "SellSide: " << m_sellSide << doubleToHumanReadable( m_sellSide );

    this->update();

    m_lastBuySide = buySide;
    m_lastSellSide = sellSide;

}


QRectF OrderBookTimeLineDiff::boundingRect() const
{
    return QRectF( 0 , 0 , m_width , m_height );
}

void OrderBookTimeLineDiff::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawRect( this->boundingRect() );

    if( m_updateRate > m_width )
        m_width = m_updateRate + 40 ;

    if( m_height < 50 )
        m_height = 50 ;

    int iindex = 1;
    for( const auto &item : m_list  ) {
        const auto [ buyside , sellside , updateRate ] = item;

        painter->drawRect( 20 , 22 * iindex + 40 , updateRate , 15 );

        painter->drawText( 20 , 22 * iindex + 12 + 40  , QString("%4. %1 %2 %3").arg( doubleToHumanReadable ( buyside / static_cast<double>( updateRate ) ) )
                                                                            .arg( doubleToHumanReadable ( sellside / static_cast<double>( updateRate ) ) )
                                                                            .arg( updateRate )
                                                                            .arg( m_list.size() - iindex ) );

        m_height = 22 * iindex + 12 + 40 + 40;
        iindex++;
    }


    painter->drawRect( 20 , 20  , m_updateRate , 15 );

    auto buysideStr = doubleToHumanReadable( m_buySide / static_cast<double>( m_updateRate ) );
    auto sellsideStr = doubleToHumanReadable( m_sellSide / static_cast<double>( m_updateRate ));

    painter->drawText( 20 , 20 + 12  , QString("%1 %2 %3").arg( buysideStr ).arg( sellsideStr ).arg( m_updateRate ) );


}

QString doubleToHumanReadable( double number )
{
    const double giga = 1000000000;
    const double mega = 1000000;
    const double kilo = 1000;

    if( number > giga ) {
        number = number / giga ;
        return QString::number( number , 'f' , 2 ) + "G";
    }
    else if( number > mega ) {
        number = number / mega;
        return QString::number( number , 'f' , 2 ) + "M";
    }
    else if( number > kilo ) {
        number = number / kilo;
        return QString::number( number , 'f' , 2 ) + "K";
    }

    return QString::number( number , 'f' , 2 );
}
