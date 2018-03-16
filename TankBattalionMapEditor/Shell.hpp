#ifndef SHELL_HPP
#define SHELL_HPP

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

enum class ShellDirection
{
    Up,
    Down,
    Left,
    Right
};
class Shell : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    QTimer timer;
    ShellDirection direction;
    double step;
    int player;
    Shell(qreal x, qreal y, ShellDirection direction, double step, int player,
          QGraphicsItem* parent = nullptr);
public slots:
    void Move();
};

#endif // SHELL_HPP
