#include "skigame.h"


SkiGame::SkiGame(int numOfObstacles)
{

    int Y = 360;

    for(int i=0;i<numOfObstacles;i++){
        obstacles.append( new SkiObstacle());
        obstacles[i]->setXY(qrand()%480,Y+obstacles[i]->getY());
        Y += (qrand()%10)*10;
    }

    santa.setXY((480-santa.getW())/2, santa.getY()+50);
}

SkiGame::~SkiGame(){
    if(!obstacles.isEmpty()){
        for (int i=0;i<obstacles.count();i++){
            if(obstacles[i] != nullptr){
                delete obstacles[i];
                obstacles[i] = nullptr;
            }
        }
    }
}

void SkiGame::tick(){
    for(int i=0;i<obstacles.count();i++){
        obstacles[i]->setY(obstacles[i]->getY()-2);
        if(obstacles[i]->getY()+obstacles[i]->getH()<0){
            obstacles[i]->setXY(qrand()%480, obstacles[i]->getH() + 360);
        }
    }
}

void SkiGame::moveSanta(int dx){
    dx=dx*santaSpeed;

    if(dx<0){
        santa.setState(1);
    }
    else{
        santa.setState(2);
    }

    santa.x += dx;
    if(santa.x < 0){
        santa.x = 0;
    }
    else if(santa.x + santa.getW() > 480){
        santa.x = 480 - santa.getW();
    }
}

QImage SkiGame::draw(){
    // vraca santa img koja treba da se iscrta
    QImage* spriteToDraw = nullptr;

    if(santa.animationImg == 0){
        santa.animationImg = 1;
    }
    else{
        santa.animationImg = 0;
    }
    int index = santa.getState()*2+santa.animationImg;
    spriteToDraw = santa.sprite[index];
    santa.setState(0);
    return *spriteToDraw;
}
