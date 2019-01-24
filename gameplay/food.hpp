#ifndef QSNAKE_GAMEPLAY_FOOD_HPP_
#define QSNAKE_GAMEPLAY_FOOD_HPP_

/************************************************************************/

#include <QGraphicsRectItem>

/************************************************************************/

class Food
    : public QGraphicsRectItem
{

/************************************************************************/

public:

/************************************************************************/

    explicit Food( QPoint _position );

/************************************************************************/

    QPoint getPosition() const noexcept;

/************************************************************************/

private:

/************************************************************************/

    inline void initPen();

    inline void initBrush();

/************************************************************************/

    QPoint m_position;

/************************************************************************/

}; // class Food

/************************************************************************/

#endif // QSNAKE_GAMEPLAY_FOOD_HPP_

