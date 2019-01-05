#include "food.hpp"
#include "snake.hpp"

#include <QPen>
#include <QBrush>

#include <utility>
#include <random>

/************************************************************************/

Food::Food( Snake* _snake )
{
    std::uniform_int_distribution< int > distr( 1, 16 );
    std::random_device device;
    std::default_random_engine generator( device() );

	do {
        m_position.setX( distr( generator ) );
        m_position.setY( distr( generator ) );

    } while( _snake->hasCoords( m_position ) );

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

