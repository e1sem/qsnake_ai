#include "food.hpp"
#include "snake.hpp"

#include <QPen>
#include <QBrush>

/************************************************************************/

Food::Food( QPoint position )
    : m_position{ position }
{
    initPen();
    initBrush();

    setRect( 0, 0, 18, 18 );
    setPos(
            m_position.x() * 18
        ,   m_position.y() * 18
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

