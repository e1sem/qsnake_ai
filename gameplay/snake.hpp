#ifndef QSNAKE_GAMEPLAY_SNAKE_HPP_
#define QSNAKE_GAMEPLAY_SNAKE_HPP_

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

    bool bodyHasCoords( QPoint _coords ) const noexcept;

    QPoint getHeadPosition() const noexcept;

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

#endif // QSNAKE_GAMEPLAY_SNAKE_HPP_
