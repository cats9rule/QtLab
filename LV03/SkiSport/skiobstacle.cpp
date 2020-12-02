#include "skiobstacle.h"

SkiObstacle::SkiObstacle(){
    x = y = 0;
    int a = qrand();
    if(a%3 == 0){
        sprite.load(":/snowman/resources/snowman.png");
    }
    else{
        sprite.load(":/tree/resources/tree.png");
    }
    w = sprite.width();
    h = sprite.height();
}
SkiObstacle::SkiObstacle(int x, int y){
    this->x = x;
    this->y = y;

    int a = qrand();

    if(a%3 == 0){
        sprite.load(":/snowman/resources/snowman.png");
    }
    else {
        sprite.load(":/tree/resources/tree.png");
    }
    w = sprite.width();
    h = sprite.height();
}
void SkiObstacle::setXY(int x, int y){
    this->x = x;
    this->y = y;
}
void SkiObstacle::setY(int y){
    this->y = y;
}
