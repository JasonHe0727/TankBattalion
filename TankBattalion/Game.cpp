#include "Game.hpp"
#include <QDebug>
#include <random>
Game::Game()
    : QGraphicsView()

{
    double height = 1024;
    double width = 768;

    battlefield = new BattlefieldScene(height, width);
    setFixedSize(height, width);
    setScene(battlefield);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    static std::default_random_engine generator;
    static std::uniform_real_distribution<> distribution(0, 1);
    for (int i = 0; i < height; i += 100)
    {
        for (int j = 0; j < width; j += 100)
        {
            if (distribution(generator) > 0.8)
            {
                qDebug() << i << "," << j;
                battlefield->AddSteel(i, j);
            }
        }
    }
    connect(&timer, SIGNAL(timeout()), this, SLOT(SpawnEnemy()));
    timer.start(3000);
    InitializePlayers();

    connect(&keysTimer, SIGNAL(timeout()), this, SLOT(ProcessKey()));
    keysTimer.start(50);
}

Game::~Game()
{
}

void Game::keyPressEvent(QKeyEvent* event)
{
    keysPressed.insert(event->key());
}

void Game::keyReleaseEvent(QKeyEvent* event)
{
    keysPressed.remove(event->key());
}

void Game::InitializePlayers()
{
    int x;
    int y;
    std::tie(x, y) = FindPosition();
    player1 = new PlayerTank(x, y, 10, TankDirection::Up, 10, 1, 500);
    battlefield->addItem(player1);
    std::tie(x, y) = FindPosition();
    player2 = new PlayerTank(x, y, 10, TankDirection::Up, 10, 2, 500);
    battlefield->addItem(player2);
}

inline bool Game::HasKey(int key)
{
    return keysPressed.find(key) != keysPressed.end();
}

std::tuple<int, int> Game::FindPosition()
{
    static std::default_random_engine generator;
    static std::uniform_int_distribution<int> distribution(0, 400);
    while (true)
    {
        int i = distribution(generator);
        int j = distribution(generator);
        if (scene()
                ->items(i, j, 60, 60, Qt::IntersectsItemShape,
                        Qt::DescendingOrder)
                .count() == 0)
        {
            return std::make_tuple(i, j);
        }
    }
}

void Game::SpawnEnemy()
{
    static std::default_random_engine generator;
    static std::uniform_int_distribution<int> distribution(0, 400);
    bool done = false;
    while (!done)
    {
        int i = distribution(generator);
        int j = distribution(generator);
        if (scene()
                ->items(i, j, 60, 60, Qt::IntersectsItemShape,
                        Qt::DescendingOrder)
                .count() == 0)
        {
            EnemyTank* enemy =
                new EnemyTank(i, j, 1, TankDirection::Up, 10, 500);
            battlefield->addItem(enemy);
            done = true;
        }
    }
}

void Game::ProcessKey()
{
    if (HasKey(Qt::Key_W))
    {
        player1->MoveUp();
    }
    else if (HasKey(Qt::Key_S))
    {
        player1->MoveDown();
    }
    else if (HasKey(Qt::Key_A))
    {
        player1->MoveLeft();
    }
    else if (HasKey(Qt::Key_D))
    {
        player1->MoveRight();
    }

    if (HasKey(Qt::Key_Up))
    {
        player2->MoveUp();
    }
    else if (HasKey(Qt::Key_Down))
    {
        player2->MoveDown();
    }
    else if (HasKey(Qt::Key_Left))
    {
        player2->MoveLeft();
    }
    else if (HasKey(Qt::Key_Right))
    {
        player2->MoveRight();
    }

    if (HasKey(Qt::Key_Space))
    {
        player1->Fire();
    }

    if (HasKey(Qt::Key_Enter))
    {
        player2->Fire();
    }
}
