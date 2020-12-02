#include "skiview.h"

SkiView::SkiView(QWidget *parent) : QWidget(parent), game(15), timer(this)
{
    setFocusPolicy(Qt::StrongFocus);
    timer.start(100);
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
}
void SkiView::keyPressEvent(QKeyEvent* e)
{
    switch (e->key())
    {
    case Qt::Key_Right:
        game.moveSanta(1);
        break;
    case Qt::Key_Left:
        game.moveSanta(-1);
        break;
    default:
        QWidget::keyPressEvent(e);
    }
    repaint();
}
void SkiView::paintEvent(QPaintEvent*){
    QPainter p(this);
    p.drawImage(game.santa.x, game.santa.y, game.draw());

    for(int i=0;i<game.obstacles.count();i++){
        p.drawImage(game.obstacles[i]->getX(),game.obstacles[i]->getY(), game.obstacles[i]->sprite);
    }
}
void SkiView::tick()
{
    game.tick();
    repaint();
}
