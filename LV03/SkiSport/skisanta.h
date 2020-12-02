#ifndef SKISANTA_H
#define SKISANTA_H

#include <QImage>
class SkiSanta
{
private:

    int w, h; // dimenzije
    int state = 0;
    /* 0 - pravo; 1 - levo; 2 - desno */



public:
    int x, y; // koordinata
    int animationImg = 0; // prva ili druga animacija
    QList<QImage*> sprite; // cuva Santa slike
public:
    SkiSanta();
    SkiSanta(int x, int y); // prosledi spawn spot
    ~SkiSanta();

    void setXY(int x, int y);
    void setWH(int w, int h);
    int getX(){return x;}
    int getY(){return y;}
    int getW(){return w;}
    int getH(){return h;}

    void setState(int state);
    int getState(){return state;}
};

#endif // SKISANTA_H
