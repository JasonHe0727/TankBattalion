#include "Battlefield.hpp"

Battlefield::Battlefield(int rows, int cols)
    : rows{rows}
    , cols{cols}
    , data(rows * cols)
{
    for (int i = 0; i < data.size(); i++)
    {
        data[i] = 0;
    }
}

Battlefield::Battlefield(int rows, int cols, QVector<int> data)
    : rows{rows}
    , cols{cols}
    , data{data}
{
}

int Battlefield::Get(int row, int col)
{
    return data[row * cols + col];
}

BattlefieldKind Battlefield::GetKind(int row, int col)
{
    return static_cast<BattlefieldKind>(data[row * cols + col]);
}

void Battlefield::Set(int row, int col, BattlefieldKind kind)
{
    data[row * cols + col] = static_cast<int>(kind);
}
