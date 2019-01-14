#include "wall.hpp"

#include <QPen>
#include <QBrush>

/************************************************************************/

Wall::Wall( int x, int y )
{
    initPen();
    initBrush();

    setRect( 0, 0, 18, 18 );
    setPos( x * 18, y * 18 );
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
