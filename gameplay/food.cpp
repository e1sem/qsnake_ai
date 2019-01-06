#include "food.hpp"
#include "snake.hpp"

#include <QPen>
#include <QBrush>

#include <QDateTime>
#include <QRandomGenerator>

/************************************************************************/

Food::Food( Snake* _snake )
{
    QRandomGenerator generator;
    generator.seed( QDateTime::currentMSecsSinceEpoch() );

	do {
        m_position.setX( generator.bounded( 16 ) + 1 );
        m_position.setY( generator.bounded( 16 ) + 1 );

    } while(
                _snake->bodyHasCoords( m_position )
            ||  _snake->getHeadPosition() == m_position
    );

    initPen();
    initBrush();

    setRect( 0, 0, 25, 25 );
    setPos(
            m_position.x() * 25
        ,   m_position.y() * 25
    );
}

/************************************************************************/

QPoint
Food::getPosition() const noexcept
{
    return m_position;
}

/************************************************************************/

void
Food::initPen()
{
    QPen pen;
    pen.setStyle( Qt::NoPen );

    setPen( pen );
}

/************************************************************************/

void
Food::initBrush()
{
    QBrush brush;
    brush.setStyle( Qt::SolidPattern );
    brush.setColor( Qt::green );

    setBrush( brush );
}

/************************************************************************/

