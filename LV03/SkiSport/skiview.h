#ifndef SKIVIEW_H
#define SKIVIEW_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include "skigame.h"

class SkiView : public QWidget
{
    Q_OBJECT
private:
    SkiGame game;
    QTimer timer;
public:
    explicit SkiView(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent* e);
public slots:
    void tick();

};

#endif // SKIVIEW_H
