#include "snake.hpp"

#include <QPen>
#include <QBrush>
#include <QPainter>

/************************************************************************/

Snake::Snake()
{
    m_snakeCoords.push_back( QPoint( 9, 8 ) );
    m_snakeCoords.push_back( QPoint( 9, 9 ) );
    m_snakeCoords.push_back( QPoint( 9, 10 ) );

	m_currentDirection = up;
}

/************************************************************************/

void
Snake::move_left() noexcept
{
	auto lp = m_snakeCoords.front();

	switch( m_currentDirection )
	{
		case up:
            lp.rx()--;
			m_currentDirection = left;
			break;
		case down:
            lp.rx()++;
			m_currentDirection = right;
			break;
		case left:
            lp.ry()++;
			m_currentDirection = down;
			break;
		case right:
            lp.ry()--;
			m_currentDirection = up;
			break;
	}

	m_snakeCoords.push_front( lp );
}

/************************************************************************/

void
Snake::move_right() noexcept
{
	auto lp = m_snakeCoords.front();

	switch( m_currentDirection )
	{
		case up:
            lp.rx()++;
			m_currentDirection = right;
			break;
		case down:
            lp.rx()--;
			m_currentDirection = left;
			break;
		case left:
            lp.ry()--;
			m_currentDirection = up;
			break;
		case right:
            lp.ry()++;
			m_currentDirection = down;
			break;
	}

	m_snakeCoords.push_front( lp );
}

/************************************************************************/

void
Snake::move_straight() noexcept
{
	auto lp = m_snakeCoords.front();

	switch( m_currentDirection )
	{
		case up:
            lp.ry()--;
			break;
		case down:
            lp.ry()++;
			break;
		case left:
            lp.rx()--;
			break;
		case right:
            lp.rx()++;
			break;
	}

	m_snakeCoords.push_front( lp );
}

/************************************************************************/

bool
Snake::bodyHasCoords( QPoint _coords ) const
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
Snake::getHeadPosition() const
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
    QPainterPath snakeBody;
    snakeBody.setFillRule( Qt::WindingFill );


    for( auto && item : m_snakeCoords )
        snakeBody.addRect(
            QRect(
                    item.x() * 25
                ,   item.y() * 25
                ,   25
                ,   25
            )
        );

    return snakeBody;
}

/************************************************************************/

QRectF
Snake::boundingRect() const
{
    int minX{ 20 };
    int maxX{ -1 };
    int minY{ 20 };
    int maxY{ -1 };

    for( auto && pos : m_snakeCoords )
    {
        minX = pos.x() < minX ? pos.x() : minX;
        maxX = pos.x() > maxX ? pos.x() : maxX;
        minY = pos.y() < minY ? pos.y() : minY;
        maxY = pos.y() > maxY ? pos.y() : maxY;
    }

    QPointF start = mapFromScene( QPointF( minX * 25, minY * 25 ) );
    QPointF finish = mapFromScene( QPointF( maxX * 25, maxY * 25 ) );

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
