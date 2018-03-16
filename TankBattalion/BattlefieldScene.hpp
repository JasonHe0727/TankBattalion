#ifndef BATTLEFIELDVIEW_HPP
#define BATTLEFIELDVIEW_HPP
#include "Score.hpp"
#include <QGraphicsScene>
#include <string>
class BattlefieldScene : public QGraphicsScene
{
    Q_OBJECT
public:
    Score* score1;
    Score* score2;
    BattlefieldScene(double height, double width);
    void AddWall(int x, int y);
    void AddSteel(int x, int y);
    void LoadMap(std::string path);

    void AddPlayer1Score(int n);
    void AddPlayer2Score(int n);
};

#endif // BATTLEFIELDVIEW_HPP
