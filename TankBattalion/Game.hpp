#ifndef GAME_HPP
#define GAME_HPP
#include <BattlefieldScene.hpp>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QSet>
#include <QTimer>
#include <Tank.hpp>
#include <tuple>
class Game : public QGraphicsView
{
    Q_OBJECT
public:
    BattlefieldScene* battlefield;
    PlayerTank* player1;
    PlayerTank* player2;
    QTimer timer;
    QSet<int> keysPressed;
    QTimer keysTimer;
    Game();
    ~Game();

    void InitializePlayers();
    bool HasKey(int key);
    std::tuple<int, int> FindPosition();
public slots:
    void SpawnEnemy();
    void ProcessKey();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
};

#endif // GAME_HPP
