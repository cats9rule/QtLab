#ifndef SKIOBSTACLE_H
#define SKIOBSTACLE_H

#include <QImage>

class SkiObstacle
{
private:
    int x, y;
    int w, h;

public:
    QImage sprite;

public:
    SkiObstacle();
    SkiObstacle(int x, int y);

    int getX(){return x;}
    int getY(){return y;}
    void setY(int y);
    void setXY(int x, int y);
    int getW(){return w;}
    int getH(){return h;}
};

#endif // SKIOBSTACLE_H
