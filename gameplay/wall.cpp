#include "wall.hpp"

#include <QPen>
#include <QBrush>

/************************************************************************/

Wall::Wall( int x, int y )
{
    initPen();
    initBrush();

    setRect( 0, 0, 25, 25 );
    setPos( x * 25, y * 25 );
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
