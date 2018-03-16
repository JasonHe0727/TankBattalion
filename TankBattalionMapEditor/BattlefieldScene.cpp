#include "BattlefieldScene.hpp"
#include <QGraphicsSceneMouseEvent>
BattlefieldScene::BattlefieldScene()
    : QGraphicsScene()
    , items(mapRows * mapColumns)
{
    setSceneRect(0, 0, mapRows * rectHeight, mapColumns * rectWidth);
    for (int i = 0; i < items.size(); i++)
    {
        items[i] = nullptr;
    }
    rect = new QGraphicsRectItem();
    rect->setBrush(QBrush(Qt::NoBrush));
    addItem(rect);
    rect->setRect(0, 0, rectWidth, rectHeight);
}

void BattlefieldScene::AddWalls()
{
    int row = static_cast<int>(rect->x()) / rectHeight;
    int col = static_cast<int>(rect->y()) / rectWidth;
    RemoveExistingItem(row, col);
    QGraphicsPixmapItem* item =
        new QGraphicsPixmapItem(QPixmap(":/images/walls.gif"));
    item->setPos(rect->x(), rect->y());
    addItem(item);
    AddNewItem(row, col, item);
}

void BattlefieldScene::AddSteels()
{
    int row = static_cast<int>(rect->x()) / rectHeight;
    int col = static_cast<int>(rect->y()) / rectWidth;
    RemoveExistingItem(row, col);
    QGraphicsPixmapItem* item =
        new QGraphicsPixmapItem(QPixmap(":/images/steels.gif"));
    item->setPos(rect->x(), rect->y());
    addItem(item);
    AddNewItem(row, col, item);
}

void BattlefieldScene::AddWater()
{
    int row = static_cast<int>(rect->x()) / rectHeight;
    int col = static_cast<int>(rect->y()) / rectWidth;
    RemoveExistingItem(row, col);
    QGraphicsPixmapItem* item =
        new QGraphicsPixmapItem(QPixmap(":/images/water.gif"));
    item->setPos(rect->x(), rect->y());
    addItem(item);
    AddNewItem(row, col, item);
}

void BattlefieldScene::AddGrass()
{
    int row = static_cast<int>(rect->x()) / rectHeight;
    int col = static_cast<int>(rect->y()) / rectWidth;
    RemoveExistingItem(row, col);
    QGraphicsPixmapItem* item =
        new QGraphicsPixmapItem(QPixmap(":/images/grass.png"));
    item->setPos(rect->x(), rect->y());
    addItem(item);
    AddNewItem(row, col, item);
}

void BattlefieldScene::AddNewItem(int row, int col, QGraphicsPixmapItem* item)
{
    items[row * mapColumns + col] = item;
}

void BattlefieldScene::RemoveExistingItem(int row, int col)
{
    if (items.at(row * mapColumns + col) != nullptr)
    {
        removeItem(items[row * mapColumns + col]);
        delete items[row * mapColumns + col];
        items[row * mapColumns + col] = nullptr;
    }
}

void BattlefieldScene::DeleteSelectedItem()
{
    int row = static_cast<int>(rect->x()) / rectHeight;
    int col = static_cast<int>(rect->y()) / rectWidth;
    RemoveExistingItem(row, col);
}

void BattlefieldScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF position = event->scenePos();
    int rectX = static_cast<int>(position.x()) / rectHeight * rectHeight;
    int rectY = static_cast<int>(position.y()) / rectWidth * rectWidth;
    rect->setPos(rectX, rectY);
}
