#ifndef __SNAKE_HPP__
#define __SNAKE_HPP__

/************************************************************************/

#include <QGraphicsItem>

#include <deque>

/************************************************************************/

class Snake
    : public QGraphicsItem
{

/************************************************************************/

public:

/************************************************************************/

    Snake();

/************************************************************************/

    void move_left() noexcept;

    void move_right() noexcept;

    void move_up() noexcept;

    void move_down() noexcept;

/************************************************************************/

    bool bodyHasCoords( QPoint _coords ) const;

    QPoint getHeadPosition() const;

    void removeTail() noexcept;

/************************************************************************/

    QPainterPath shape() const override;

    QRectF boundingRect() const override;

    void paint(
            QPainter* _painter
        ,   const QStyleOptionGraphicsItem*
        ,   QWidget*
    ) override;

/************************************************************************/

private:

/************************************************************************/

    std::deque< QPoint > m_snakeCoords;

/************************************************************************/

}; // class Snake

/************************************************************************/

#endif // __SNAKE_HPP__
