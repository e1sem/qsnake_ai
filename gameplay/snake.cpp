#include "snake.hpp"

#include <QPen>
#include <QBrush>
#include <QPainter>

/************************************************************************/

Snake::Snake()
{
    m_snakeCoords.emplace_back( 12, 11 );
    m_snakeCoords.emplace_back( 12, 11 );
    m_snakeCoords.emplace_back( 12, 11 );
}

/************************************************************************/

void
Snake::move_left() noexcept
{
    auto head = getHeadPosition();

    head.rx()--;

    m_snakeCoords.push_front( head );
}

/************************************************************************/

void
Snake::move_right() noexcept
{
    auto head = getHeadPosition();

    head.rx()++;

    m_snakeCoords.push_front( head );
}

/************************************************************************/

void
Snake::move_up() noexcept
{
    auto head = getHeadPosition();

    head.ry()--;

    m_snakeCoords.push_front( head );
}

/************************************************************************/

void
Snake::move_down() noexcept
{
    auto head = getHeadPosition();

    head.ry()++;

    m_snakeCoords.push_front( head );
}


/************************************************************************/

bool
Snake::bodyHasCoords( QPoint _coords ) const noexcept
{
	return std::find(
            ++m_snakeCoords.cbegin()
		,	m_snakeCoords.cend()
		,	_coords
	)
		!= m_snakeCoords.cend();
}

/************************************************************************/

QPoint
Snake::getHeadPosition() const noexcept
{
	return m_snakeCoords.front();
}

/************************************************************************/

void
Snake::removeTail() noexcept
{
    m_snakeCoords.pop_back();
}

/************************************************************************/

QPainterPath
Snake::shape() const
{
    QPainterPath snake;
    snake.setFillRule( Qt::WindingFill );


    for( auto && item : m_snakeCoords )
        snake.addRect(
            QRect(
                    item.x() * 18
                ,   item.y() * 18
                ,   18
                ,   18
            )
        );

    return snake;
}

/************************************************************************/

QRectF
Snake::boundingRect() const
{
    int minX{ 30 };
    int maxX{ -1 };
    int minY{ 30 };
    int maxY{ -1 };

    for( auto && pos : m_snakeCoords )
    {
        minX = pos.x() < minX ? pos.x() : minX;
        maxX = pos.x() > maxX ? pos.x() : maxX;
        minY = pos.y() < minY ? pos.y() : minY;
        maxY = pos.y() > maxY ? pos.y() : maxY;
    }

    QPointF start = mapFromScene( QPointF( minX * 18, minY * 18 ) );
    QPointF finish = mapFromScene( QPointF( maxX * 18, maxY * 18 ) );

    return QRectF(
            start.x()
        ,   start.y()
        ,   finish.x() - start.x()
        ,   finish.y() - start.y()
    );
}

/************************************************************************/

void
Snake::paint(
        QPainter *painter
    ,   const QStyleOptionGraphicsItem*
    ,   QWidget*
)
{
    painter->save();
    painter->fillPath( shape(), Qt::red );
    painter->restore();
}

/************************************************************************/
