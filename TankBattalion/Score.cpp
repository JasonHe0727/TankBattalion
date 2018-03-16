#include "Score.hpp"
#include <QFont>

Score::Score(QString prompt, QGraphicsItem* parent)
    : QGraphicsTextItem(parent)
    , prompt{prompt}
{
    // initialize the score to 0
    score = 0;

    // draw the text
    setPlainText(prompt + QString::number(score)); // Score: 0
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 16));
}

void Score::Increase(int n)
{
    score += n;
    setPlainText(prompt + QString::number(score)); // Score: 1
}
