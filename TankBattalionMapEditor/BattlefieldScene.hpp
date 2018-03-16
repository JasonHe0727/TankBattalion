#ifndef BATTLEFIELDSCENE_HPP
#define BATTLEFIELDSCENE_HPP
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QVector>
class BattlefieldScene : public QGraphicsScene
{
    Q_OBJECT
public:
    const int rectWidth = 60;
    const int rectHeight = 60;
    const int mapRows = 13;
    const int mapColumns = 13;
    QVector<QGraphicsPixmapItem*> items;
    QGraphicsRectItem* rect;
    BattlefieldScene();
    void AddWalls();
    void AddSteels();
    void AddWater();
    void AddGrass();
    void AddNewItem(int row, int col, QGraphicsPixmapItem* item);
    void RemoveExistingItem(int row, int col);
    void DeleteSelectedItem();
public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // BATTLEFIELDSCENE_HPP
