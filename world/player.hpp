#ifndef QSNAKE_WORLD_PLAYER_HPP_
#define QSNAKE_WORLD_PLAYER_HPP_

/************************************************************************/

#include "neural_net/neural_net.hpp"

#include <QPoint>

#include <memory>
#include <vector>

/************************************************************************/

class QGraphicsScene;

class Snake;
class Food;

/************************************************************************/

class Player
{

/************************************************************************/

public:

/************************************************************************/

    Player(
            QGraphicsScene* _scene
        ,   NeuralNet* _brain
    );

    ~Player();

/************************************************************************/

    void loseGame();

    void nextStep();

/************************************************************************/

    int getGameScore() const noexcept;

    int getStepsCount() const noexcept;

    bool isGameOver() const noexcept;

/************************************************************************/

private:

/************************************************************************/

    void drawBoundingWalls() noexcept;

    void initGameplay() noexcept;

    void handleCollisions() noexcept;

    void handleFoodCollision() noexcept;

    void continueGame() noexcept;

/************************************************************************/

    std::vector<double> collectInputs() const noexcept;

    void analyzeOutputs( std::vector<double> _data ) noexcept;

    static bool inBounds( QPoint _point ) noexcept;

    QPoint getNewFoodCoord() const noexcept;

/************************************************************************/

    std::unique_ptr< NeuralNet > m_pBrain;

    QGraphicsScene* m_gameField;

/************************************************************************/

    int m_gameScore;

    int m_gameSteps;

    bool m_gameOver;

/************************************************************************/

    Food* m_food;

    Snake* m_snake;

/************************************************************************/

}; // class Player

/************************************************************************/

#endif // QSNAKE_WORLD_PLAYER_HPP_
