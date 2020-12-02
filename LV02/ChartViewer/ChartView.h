#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QWidget>
#include <ChartDoc.h>
#include <QPainter>
#include <QMouseEvent>
#include "chartpointdialog.h"

class ChartView : public QWidget
{
    Q_OBJECT

private:
    ChartDoc* m_chartDoc; //pamti podatke o stubovima
    QList<QRect*> bars; // pamti QRect koji predstavljaju stubove - za iscrtavanje

public:
    explicit ChartView(QWidget *parent = nullptr);
    ~ChartView();
    void setChartDoc(ChartDoc* obj) {this->m_chartDoc = obj;}
    void mouseDoubleClickEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent*);

public slots:
    void onChartDataChanged();

};

#endif // CHARTVIEW_H
