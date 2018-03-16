#ifndef BATTLEFIELD_HPP
#define BATTLEFIELD_HPP
#include <QVector>

enum class BattlefieldKind
{
    Steel = 0,
    Wall = 1,
    Grass = 2,
    Water = 3
};

class Battlefield
{
public:
    Battlefield(int rows, int cols);
    Battlefield(int rows, int cols, QVector<int> data);
    int rows;
    int cols;
    QVector<int> data;
    int Get(int row, int col);
    BattlefieldKind GetKind(int row, int col);
    void Set(int row, int col, BattlefieldKind kind);
};

#endif // BATTLEFIELD_HPP
