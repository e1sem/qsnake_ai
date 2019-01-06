#include "player.hpp"

#include "gameplay/snake.hpp"
#include "gameplay/food.hpp"
#include "gameplay/wall.hpp"

#include <QGraphicsScene>

/************************************************************************/

Player::Player(
        QGraphicsScene* _scene
    ,   QObject* _parent
)
    :   QObject{ _parent }
    ,   m_gameField{ _scene }
{
    drawBoundingWalls();
    initGameplay();
}

/************************************************************************/

int
Player::getGameScore() const noexcept
{
    return m_gameScore;
}

/************************************************************************/

void
Player::drawBoundingWalls() noexcept
{
    for( int i = 0; i < 18; ++i )
        for( int j = 0; j < 18; ++j )
            if(
                    i == 0
                ||  i == 17
                ||  j == 0
                ||  j == 17
            )
            {
                auto pWall = new Wall( i, j );
                m_gameField->addItem( pWall );
            }
}

/************************************************************************/

void
Player::initGameplay() noexcept
{
    m_gameScore = 0;

    m_snake = new Snake;
    m_food = new Food( m_snake );

    m_gameField->addItem( m_snake );
    m_gameField->addItem( m_food );
}

/************************************************************************/

void
Player::handleCollisions() noexcept
{
    auto snakeHead = m_snake->getHeadPosition();

    if( snakeHead == m_food->getPosition() )
        handleFoodCollision();
    else if( m_snake->bodyHasCoords( snakeHead ) )
        handleSnakeCollision();
    else if(
            snakeHead.x() == 0
        ||  snakeHead.x() == 17
        ||  snakeHead.y() == 0
        ||  snakeHead.y() == 17
    )
    {
        handleWallCollision();
    }
    else
        m_snake->removeTail();

    m_gameField->update();
}

/************************************************************************/

void
Player::handleWallCollision() noexcept
{
    emit gameOver();

    delete m_food;
    delete m_snake;

    initGameplay();
}

/************************************************************************/

void
Player::handleSnakeCollision() noexcept
{
    emit gameOver();

    delete m_food;
    delete m_snake;

    initGameplay();
}

/************************************************************************/

void
Player::handleFoodCollision() noexcept
{
    m_gameScore += 100;

    delete m_food;

    m_food = new Food( m_snake );
    m_gameField->addItem( m_food );
}

/************************************************************************/
