#ifndef CHARTDOC_H
#define CHARTDOC_H

#include <QObject>
#include "ChartPoint.h"

class ChartDoc : public QObject
{
    Q_OBJECT

public:
    QList<ChartPoint*> m_points;

signals:
    void chartDataChanged();


public:
    explicit ChartDoc(QObject *parent = nullptr);

    ~ChartDoc();

    void loadChartFromFile(QString file);
    void saveChartToFile(QString file);

};

#endif // CHARTDOC_H
