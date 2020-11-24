#ifndef CHARTPOINT_H
#define CHARTPOINT_H

#include <QString>
#include <QColor>

class ChartPoint {
private:
    QString label;
    float value;
    QColor colour;

public:
    ChartPoint();
    ~ChartPoint();

    void setLabel(QString label){this->label = label;}
    void setValue(float value){this->value = value;}
    void setColour(QColor colour){this->colour = colour;}

    QString getLabel(){return label;}
    float getValue(){return value;}
    QColor getColour(){return colour;}
};


#endif // CHARTPOINT_H
