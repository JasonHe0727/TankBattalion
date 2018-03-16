#include "Tank.hpp"
#include "Shell.hpp"
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <random>
Tank::Tank(qreal x, qreal y, int health, TankDirection direction, int player,
           double step, int loadTime, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
    , health{health}
    , direction{direction}
    , player{player}
    , step{step}
    , loadTime{loadTime}
    , lastFiring(QTime::currentTime())
{
    SetImage();
    setPos(x, y);
}

void Tank::MoveUp()
{
    direction = TankDirection::Up;
    SetImage();
    if (y() - step >= 0)
    {
        if (CanMove(x(), y() - step))
        {
            setPos(x(), y() - step);
        }
    }
}

void Tank::MoveDown()
{
    direction = TankDirection::Down;
    SetImage();
    if (y() + step + pixmap().height() <= scene()->height())
    {
        if (CanMove(x(), y() + step))
        {
            setPos(x(), y() + step);
        }
    }
}

void Tank::MoveLeft()
{
    direction = TankDirection::Left;
    SetImage();
    if (pos().x() - step >= 0)
    {
        if (CanMove(x() - step, y()))
        {
            setPos(x() - step, y());
        }
    }
}

void Tank::MoveRight()
{
    direction = TankDirection::Right;
    SetImage();
    if (pos().x() + step + pixmap().width() <= scene()->width())
    {
        if (CanMove(x() + step, y()))
        {
            setPos(x() + step, y());
        }
    }
}

void Tank::Fire()
{
    QTime now = QTime::currentTime();
    int diff = now.msecsSinceStartOfDay() - lastFiring.msecsSinceStartOfDay();
    if (diff >= loadTime)
    {
        double width = pixmap().width();
        double half = width / 2.0;
        double adjustment = 20;
        double shellStep = 30;

        if (direction == TankDirection::Up)
        {
            Shell* shell = new Shell(x() + half, y() - adjustment,
                                     ShellDirection::Up, shellStep, player);
            scene()->addItem(shell);
        }
        else if (direction == TankDirection::Down)
        {
            Shell* shell = new Shell(x() + half, y() + width + adjustment,
                                     ShellDirection::Down, shellStep, player);
            scene()->addItem(shell);
        }
        else if (direction == TankDirection::Left)
        {
            Shell* shell = new Shell(x() - adjustment, y() + half,
                                     ShellDirection::Left, shellStep, player);
            scene()->addItem(shell);
        }
        else
        {
            Shell* shell = new Shell(x() + width + adjustment, y() + half,
                                     ShellDirection::Right, shellStep, player);
            scene()->addItem(shell);
        }
        lastFiring = QTime::currentTime();
    }
}

void Tank::SetImage()
{
    if (player == 1)
    {
        if (direction == TankDirection::Up)
        {
            setPixmap(QPixmap(":/images/p1tankU.gif"));
        }
        else if (direction == TankDirection::Down)
        {
            setPixmap(QPixmap(":/images/p1tankD.gif"));
        }
        else if (direction == TankDirection::Left)
        {
            setPixmap(QPixmap(":/images/p1tankL.gif"));
        }
        else
        {
            setPixmap(QPixmap(":/images/p1tankR.gif"));
        }
    }
    else if (player == 2)
    {
        if (direction == TankDirection::Up)
        {
            setPixmap(QPixmap(":/images/p2tankU.gif"));
        }
        else if (direction == TankDirection::Down)
        {
            setPixmap(QPixmap(":/images/p2tankD.gif"));
        }
        else if (direction == TankDirection::Left)
        {
            setPixmap(QPixmap(":/images/p2tankL.gif"));
        }
        else
        {
            setPixmap(QPixmap(":/images/p2tankR.gif"));
        }
    }
    else
    {
        if (direction == TankDirection::Up)
        {
            setPixmap(QPixmap(":/images/enemy1U.gif"));
        }
        else if (direction == TankDirection::Down)
        {
            setPixmap(QPixmap(":/images/enemy1D.gif"));
        }
        else if (direction == TankDirection::Left)
        {
            setPixmap(QPixmap(":/images/enemy1L.gif"));
        }
        else
        {
            setPixmap(QPixmap(":/images/enemy1R.gif"));
        }
    }
}

void Tank::SetStep(double step)
{
    this->step = step;
}

bool Tank::CanMove(double x, double y)
{
    QList<QGraphicsItem*> list =
        scene()->items(x, y, pixmap().width(), pixmap().height(),
                       Qt::IntersectsItemShape, Qt::DescendingOrder);
    if (list.count() > 1) // ignore this tank
    {
        return false;
    }
    else
    {
        return true;
    }
}

EnemyTank::EnemyTank(qreal x, qreal y, int health, TankDirection direction,
                     double step, int loadTime)
    : Tank(x, y, health, direction, 0, step, loadTime)
    , timer(this)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(RandomMove()));
    timer.start(500);
}

EnemyTank::~EnemyTank()
{
}

void EnemyTank::HitByAShell()
{
    health--;
    if (health == 0)
    {
        this->scene()->removeItem(this);
        delete this;
    }
}

void EnemyTank::RandomMove()
{
    static std::default_random_engine generator;
    static std::uniform_int_distribution<int> distribution(0, 3);
    int choice = distribution(generator);
    if (choice == 0)
    {
        MoveUp();
        MoveUp();
    }
    else if (choice == 1)
    {
        MoveDown();
        MoveDown();
    }
    else if (choice == 2)
    {
        MoveLeft();
        MoveLeft();
    }
    else
    {
        MoveRight();
        MoveRight();
    }
    Fire();
}

PlayerTank::PlayerTank(qreal x, qreal y, int health, TankDirection direction,
                       double step, int player, int loadTime)
    : Tank(x, y, health, direction, player, step, loadTime)
{
}

PlayerTank::~PlayerTank()
{
}

void PlayerTank::HitByAShell()
{
    health--;
    qDebug() << "player is hit by a shell";
}
