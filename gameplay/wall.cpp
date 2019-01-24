#include "wall.hpp"

#include <QPen>
#include <QBrush>

/************************************************************************/

Wall::Wall( QPoint _position )
{
    initPen();
    initBrush();

    setRect( 0, 0, 18, 18 );
    setPos(
            _position.x() * 18
        ,   _position.y() * 18
    );
}

/************************************************************************/

void
Wall::initPen()
{
    QPen pen;
    pen.setStyle( Qt::NoPen );

    setPen( pen );
}

/************************************************************************/

void
Wall::initBrush()
{
    QBrush brush;
    brush.setStyle( Qt::SolidPattern );
    brush.setColor( Qt::darkGray );

    setBrush( brush );
}

/************************************************************************/
