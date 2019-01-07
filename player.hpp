#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

/************************************************************************/

#include <QObject>

/************************************************************************/

class QGraphicsScene;

class Snake;
class Food;

/************************************************************************/

class Player
    : public QObject
{

/************************************************************************/

    Q_OBJECT

/************************************************************************/

public:

/************************************************************************/

    Player(
            QGraphicsScene* _scene
        ,   QObject* _parent = nullptr
    );

/************************************************************************/

    int getGameScore() const noexcept;

/************************************************************************/

signals:

/************************************************************************/

    void gameOver();

/************************************************************************/

private:

/************************************************************************/

    void drawBoundingWalls() noexcept;

    void initGameplay() noexcept;

    void handleCollisions() noexcept;

/************************************************************************/

    void handleWallCollision() noexcept;

    void handleSnakeCollision() noexcept;

    void handleFoodCollision() noexcept;

/************************************************************************/

    QGraphicsScene* m_gameField;

    int m_gameScore;

    Snake* m_snake;

    Food* m_food;

/************************************************************************/

}; // class Player

/************************************************************************/

#endif // __PLAYER_HPP__