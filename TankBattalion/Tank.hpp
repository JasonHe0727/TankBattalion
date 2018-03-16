#ifndef TANK_HPP
#define TANK_HPP
#include <QGraphicsPixmapItem>
#include <QTime>
#include <QTimer>
enum TankDirection
{
    Up,
    Down,
    Left,
    Right
};
class Tank : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    int health;
    TankDirection direction;
    int player; // 0: enemy, 1: player1, 2: player2
    double step;
    int loadTime;
    QTime lastFiring;
    Tank(qreal x, qreal y, int health, TankDirection direction, int player,
         double step, int loadTime, QGraphicsItem* parent = nullptr);
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Fire();
    void SetImage();
    void SetStep(double step);
    bool CanMove(double x, double y);
    virtual void HitByAShell() = 0;
};

class EnemyTank : public Tank
{
    Q_OBJECT
public:
    QTimer timer;
    EnemyTank(qreal x, qreal y, int health, TankDirection direction,
              double step, int loadTime);
    ~EnemyTank() override;
    void HitByAShell() override;
public slots:
    void RandomMove();
};

class PlayerTank : public Tank
{
    Q_OBJECT
public:
    PlayerTank(qreal x, qreal y, int health, TankDirection direction,
               double step, int player, int loadTime);
    ~PlayerTank() override;
    void HitByAShell() override;
};
#endif // TANK_HPP
