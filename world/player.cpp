#include "player.hpp"

#include "gameplay/snake.hpp"
#include "gameplay/food.hpp"
#include "gameplay/wall.hpp"

#include <QGraphicsScene>

/************************************************************************/

Player::Player(
        QGraphicsScene* _scene
    ,   NeuralNet* _brain
)
    :   m_pBrain{ _brain }
    ,   m_gameField{ _scene }
{
    drawBoundingWalls();
    initGameplay();
}

/************************************************************************/

Player::~Player()
{
    loseGame();
}

/************************************************************************/

int
Player::getGameScore() const noexcept
{
    return m_gameScore;
}

/************************************************************************/

int
Player::getStepsCount() const noexcept
{
    return m_gameSteps;
}

/************************************************************************/

bool
Player::isGameOver() const noexcept
{
    return m_gameOver;
}

/************************************************************************/

void
Player::drawBoundingWalls() noexcept
{
    for( int i = 0; i < 25; ++i )
        for( int j = 0; j < 25; ++j )
            if(
                    i == 0
                ||  i == 24
                ||  j == 0
                ||  j == 24
            )
            {
                auto pWall = new Wall( QPoint( i, j ) );
                m_gameField->addItem( pWall );
            }
}

/************************************************************************/

void
Player::initGameplay() noexcept
{
    m_gameScore = 0;
    m_gameSteps = 0;

    m_gameOver = false;

    m_snake = new Snake;
    m_food = new Food( getNewFoodCoord() );

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
        loseGame();
    else if( !inBounds( snakeHead ) )
        loseGame();
    else
        continueGame();

    m_gameField->update();
}

/************************************************************************/

void
Player::handleFoodCollision() noexcept
{
    m_gameScore += 100;
    m_gameSteps = 0;

    delete m_food;
    m_food = new Food( getNewFoodCoord() );
}

/************************************************************************/

void
Player::continueGame() noexcept
{
    if( m_gameSteps > 100 )
    {
        m_gameSteps = 0;
        loseGame();
    }
    else
    {
        m_snake->removeTail();
        m_gameSteps++;
    }
}

/************************************************************************/

void
Player::nextStep()
{
    if( !m_gameOver )
    {
        auto inputData = collectInputs();
        m_pBrain->feedForward( inputData );

        auto output = m_pBrain->getResults();
        analyzeOutputs( output );
    }
}

/************************************************************************/

// TODO: refactoring
std::vector<double>
Player::collectInputs() const noexcept
{
    std::vector< double > result;

    auto head =  m_snake->getHeadPosition();
    auto food = m_food->getPosition();

    // Distance to Wall [0-1]
    result.push_back( head.x() / 25.0 );
    result.push_back( ( 24 - head.x() ) / 25.0 );
    result.push_back( head.y() / 25.0 );
    result.push_back( ( 24 - head.y() ) / 25.0 );

    // Distance to self body [0-1]
    double leftDist = 1.0;
    double rightDist = 1.0;
    double topDist = 1.0;
    double bottomDist = 1.0;

    for( int i = 24; i > 0; --i )
    {
        if( m_snake->bodyHasCoords( QPoint( head.x() - i, head.y() ) ) )
            leftDist = i / 25.0;
        if( m_snake->bodyHasCoords( QPoint( head.x() + i, head.y() ) ) )
            rightDist = i / 25.0;
        if( m_snake->bodyHasCoords( QPoint( head.x(), head.y() - i ) ) )
            topDist = i / 25.0;
        if( m_snake->bodyHasCoords( QPoint( head.x(), head.y() + 1 ) ) )
            bottomDist = i / 25.0;
    }

    result.push_back( leftDist );
    result.push_back( rightDist );
    result.push_back( topDist );
    result.push_back( bottomDist );

    // Distance to food [0-1]
    if( head.y() == food.y() )
    {
        if( food.x() < head.x() )
        {
            result.push_back( ( head.x() - food.x() ) / 25.0 );
            result.push_back( 1.0 );
        }
        else
        {
            result.push_back( 1.0 );
            result.push_back( ( food.x() - head.x() ) / 25.0 );
        }
    }
    else
    {
        result.push_back( 1.0 );
        result.push_back( 1.0 );
    }
    if( head.x() == food.x() )
    {
        if( food.y() < head.y() )
        {
            result.push_back( ( head.y() - food.y() ) / 25.0 );
            result.push_back( 1.0 );
        }
        else
        {
            result.push_back( 1.0 );
            result.push_back( ( food.y() - head.y() ) / 25.0 );
        }
    }
    else
    {
        result.push_back( 1.0 );
        result.push_back( 1.0 );
    }

    // Reversed value
    for( auto input : result )
        input = 1.0 - input;

    return result;
}

/************************************************************************/

// TODO: refactoring?
void
Player::analyzeOutputs( std::vector<double> _data ) noexcept
{
    auto index = std::distance(
            std::max_element(
                    _data.cbegin()
                ,   _data.cend()
            )
        ,
            _data.cbegin()
    );

    switch( index )
    {
        case 0:
            m_snake->move_left();
            break;
        case 1:
            m_snake->move_right();
            break;
        case 2:
            m_snake->move_up();
            break;
        case 3:
            m_snake->move_down();
            break;
    }

    handleCollisions();
}

/************************************************************************/

bool
Player::inBounds( QPoint _point ) noexcept
{
    if( _point.x() > 0 && _point.x() < 24 )
        if( _point.y() > 0 && _point.y() < 24 )
            return true;

    return false;
}

/************************************************************************/

QPoint
Player::getNewFoodCoord() const noexcept
{
    QPoint result;
    bool generated{ false };

    while( !generated )
    {
        result.rx() = std::rand() % 23 + 1;
        result.ry() = std::rand() % 23 + 1;

        generated = m_snake->getHeadPosition() != result
                &&  !m_snake->bodyHasCoords( result );
    }

    return result;
}

/************************************************************************/

void
Player::loseGame()
{
    if( !m_gameOver )
    {
        delete m_snake;
        delete m_food;

        m_gameOver = true;
    }
}

/************************************************************************/
