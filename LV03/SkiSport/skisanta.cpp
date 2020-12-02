#include "skisanta.h"

SkiSanta::SkiSanta(){
    x = y = 0;

    sprite.append( new QImage(":/santa/front/resources/santa1.png"));
    sprite.append( new QImage(":/santa/front/resources/santa2.png"));
    sprite.append( new QImage(":/santa/left/resources/santa-left1.png"));
    sprite.append( new QImage(":/santa/left/resources/santa-left2.png"));
    sprite.append( new QImage(":/santa/right/resources/santa-right1.png"));
    sprite.append( new QImage(":/santa/right/resources/santa-right2.png"));

    w = sprite[0]->width();
    h = sprite[0]->height();
}
SkiSanta::SkiSanta(int x, int y){
    this->x = x;
    this->y = y;

    sprite.append( new QImage(":/santa/front/resources/santa1.png"));
    sprite.append( new QImage(":/santa/front/resources/santa2.png"));
    sprite.append( new QImage(":/santa/left/resources/santa-left1.png"));
    sprite.append( new QImage(":/santa/left/resources/santa-left2.png"));
    sprite.append( new QImage(":/santa/right/resources/santa-right1.png"));
    sprite.append( new QImage(":/santa/right/resources/santa-right2.png"));

    w = sprite[0]->width();
    h = sprite[0]->height();
}

SkiSanta::~SkiSanta(){
    for(int i=0;i<6;i++){
        if(sprite[i] != nullptr){
            delete sprite[i];
            sprite[i] = nullptr;
        }
    }
}

void SkiSanta::setXY(int x, int y){
    this->x = x;
    this->y = y;
}
void SkiSanta::setState(int state){
    this->state = state;
}
