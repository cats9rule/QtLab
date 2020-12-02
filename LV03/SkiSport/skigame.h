#ifndef SKIGAME_H
#define SKIGAME_H

#include <QWidget>
#include "skisanta.h"
#include "skiobstacle.h"

class SkiGame : public QObject
{
private:
    int santaSpeed =5;

public:
    SkiSanta santa;
    QList<SkiObstacle*> obstacles;

public:
    //SkiGame(QObject* parent);
    SkiGame(int numOfObstacles);
    ~SkiGame();

    void tick();
    void moveSanta(int dx);
    QImage draw();
};

#endif // SKIGAME_H
