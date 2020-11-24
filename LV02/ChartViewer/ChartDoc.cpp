#include "ChartDoc.h"
#include <QFile>
#include <QTextStream>

ChartDoc::ChartDoc(QObject *parent) : QObject(parent){

}

ChartDoc::~ChartDoc(){
    if(!m_points.isEmpty()){
        for(int i=0;i<m_points.count();i++){
            if(m_points[i]!=nullptr){
                delete m_points[i];
            }
        }
    }
}

void ChartDoc::loadChartFromFile(QString file){
    QFile source(file);
    if(!source.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    if(!m_points.isEmpty()){
        for(int i=0;i<m_points.count();i++){
            delete m_points[i];
            m_points[i] = nullptr;
        }
        m_points.clear();
    }

    QTextStream in(&source);
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList data = line.split(",");

        ChartPoint* stub = new ChartPoint();

        // check format data needed here!!!
        stub->setLabel(data[0]);

        if(data[1].toFloat()<0){
            data[1] = "0";
        }
        else if(data[1].toFloat()>100){
            data[1] = "100";
        }

        stub->setValue(data[1].toFloat());
        stub->setColour(data[2]);

        m_points.append(stub);
    }
    source.close();
    emit chartDataChanged();
}

void  ChartDoc::saveChartToFile(QString file){
    QFile output(file);
    if(!output.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    QTextStream out(&output);
    for(int i = 0; i < m_points.count(); i++){
        QString line = m_points[i]->getLabel() + ","
                + QString::number(m_points[i]->getValue()) + ","
                + m_points[i]->getColour().name() + "\n";
        out << line;
    }
    output.close();
}
