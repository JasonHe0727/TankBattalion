#include "Shell.hpp"
#include "Tank.hpp"
#include <BattlefieldScene.hpp>
#include <QGraphicsScene>
Shell::Shell(qreal x, qreal y, ShellDirection direction, double step,
             int player, QGraphicsItem* parent)
    : QObject()
    , QGraphicsPixmapItem(parent)
    , timer(this)
    , direction{direction}
    , step{step}
    , player{player}
{
    setPixmap(QPixmap(":/images/shell.png"));
    setPos(x, y);
    connect(&timer, SIGNAL(timeout()), this, SLOT(Move()));
    timer.start(50);
}

void Shell::Move()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    int n = colliding_items.size();
    for (int i = 0; i < n; i++)
    {
        if (typeid(*(colliding_items[i])) == typeid(EnemyTank))
        {
            if (player == 1)
            {
                BattlefieldScene* battlefield =
                    static_cast<BattlefieldScene*>(scene());
                battlefield->AddPlayer1Score(1);
            }
            else if (player == 2)
            {
                BattlefieldScene* battlefield =
                    static_cast<BattlefieldScene*>(scene());
                battlefield->AddPlayer2Score(1);
            }

            Tank* tank = static_cast<Tank*>(colliding_items[i]);
            tank->HitByAShell();
            scene()->removeItem(this);

            delete this;
            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(PlayerTank))
        {
            PlayerTank* tank = static_cast<PlayerTank*>(colliding_items[i]);
            tank->HitByAShell();
            scene()->removeItem(this);
            delete this;
            return;
        }
        else
        {
            delete this;
            return;
        }
    }
    if (direction == ShellDirection::Up)
    {
        setPos(x(), y() - step);
    }
    else if (direction == ShellDirection::Down)
    {
        setPos(x(), y() + step);
    }
    else if (direction == ShellDirection::Left)
    {
        setPos(x() - step, y());
    }
    else
    {
        setPos(x() + step, y());
    }
    if (x() < 0 || y() < 0 || x() > scene()->width() || y() > scene()->height())
    {
        scene()->removeItem(this);
        delete this;
    }
}
