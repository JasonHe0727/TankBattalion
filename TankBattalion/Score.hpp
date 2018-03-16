#ifndef SCORE_HPP
#define SCORE_HPP
#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem
{
public:
    int score;
    QString prompt;
    Score(QString prompt, QGraphicsItem* parent = 0);
    void Increase(int n);
};
#endif // SCORE_HPP
