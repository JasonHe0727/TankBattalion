#include "BattlefieldScene.hpp"
#include <QGraphicsPixmapItem>
#include <fstream>
BattlefieldScene::BattlefieldScene(double height, double width)
    : QGraphicsScene()
{
    setSceneRect(0, 0, height, width);
    setBackgroundBrush(QBrush(QColor(Qt::GlobalColor::black)));
    score1 = new Score("Player 1 Score: ");
    score2 = new Score("Player 2 Score: ");
    addItem(score1);
    addItem(score2);
    score1->setPos(0, 0);
    score2->setPos(0, 20);
    score1->setZValue(100);
    score2->setZValue(100);
}

void BattlefieldScene::AddWall(int x, int y)
{
    QGraphicsPixmapItem* item =
        new QGraphicsPixmapItem(QPixmap(":/images/walls.gif"));
    item->setPos(x, y);
    addItem(item);
}

void BattlefieldScene::AddSteel(int x, int y)
{
    QGraphicsPixmapItem* item =
        new QGraphicsPixmapItem(QPixmap(":/images/steels.gif"));
    item->setPos(x, y);
    addItem(item);
}

void BattlefieldScene::LoadMap(std::string path)
{
    std::ifstream file(path);
    while (file.peek() != EOF)
    {
        int x;
        int y;
        int type;
        file >> x >> y >> type;
        if (type == 1)
        {
            AddSteel(x, y);
        }
        else if (type == 2)
        {
            AddWall(x, y);
        }
    }
}

void BattlefieldScene::AddPlayer1Score(int n)
{
    score1->Increase(n);
}

void BattlefieldScene::AddPlayer2Score(int n)
{
    score2->Increase(n);
}
