#ifndef __WALL_HPP__
#define __WALL_HPP__

/************************************************************************/

#include <QGraphicsRectItem>

/************************************************************************/

class Wall
    : public QGraphicsRectItem
{

/************************************************************************/

public:

/************************************************************************/

    Wall( int x, int y );

/************************************************************************/

private:

/************************************************************************/

    inline void initPen();

    inline void initBrush();

/************************************************************************/

}; // class Wall

/************************************************************************/

#endif // __WALL_HPP__