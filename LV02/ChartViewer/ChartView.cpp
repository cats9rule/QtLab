#include "ChartView.h"

ChartView::ChartView(QWidget *parent) : QWidget(parent)
{

}

void ChartView::onChartDataChanged(){
    repaint();
}

ChartView::~ChartView(){
    int count = bars.count();
    if(count > 0){
        for(int i=0;i<count;i++){
            if(bars[i] != nullptr){
                delete bars[i];
                bars[i] = nullptr;
            }
        }
    }
}

void ChartView::paintEvent(QPaintEvent*){

    const int W = this->width();
    const int H = this->height();
    const int Xm = W/20; // koordinate MAX tacke
    const int Ym = H/20; // MAX - pocetna tacka grafa (najbliza koor. poc.)
    const int l = W - 2*Xm; // duzina x-ose
    const int a = H - 2*Ym; // duzina y-ose
    const int r = a/10; // jedinicna duz skale
    int razmak = l/10; // razmak izmedju stubaca
    const int crta = razmak/10; // duzina crte na skali

    QPainter p(this);
    QPen pen(Qt::black,1);
    p.setPen(pen);

    // iscrtavanje osa i podeoka na osama
    p.drawLine(Xm, Ym, Xm, Ym+a); // y-osa
    p.drawLine(Xm, Ym+a, Xm+l, Ym+a); // x-osa
    int broj = 100;
    for(int i=0;i<=10;i++){ // skala
        p.drawLine(Xm-crta,Ym+i*r, Xm,Ym+i*r);
        p.drawText(Xm-4*crta,Ym+i*r, QString::number(broj));
        broj-=10;
    }

    // using data from chartDoc
    int count = m_chartDoc->m_points.count(); // br stubaca
    if(count!=0){
        if(!bars.isEmpty()){
            for(int i=0;i<bars.count();i++){
                if(bars[i]!= nullptr){
                    delete bars[i];
                }
            }
        }
        bars.clear(); // lista stubaca, pamti QRect
        razmak /= count;
        int d = (l-razmak*count)/count; // sirina jednog stuba
        for(int i=0;i<count;i++){
            int h = m_chartDoc->m_points[i]->getValue()*a / 100; //visina stuba skalirana
            p.setBrush(m_chartDoc->m_points[i]->getColour());

            //kreiranje pravougaonika
            QRect* bar = new QRect(Xm+i*(d+razmak),Ym+a-h, d,h);
            bars.append(bar);
            p.drawRect(*bar);

            // za labelu
            QRect textBounds(Xm+i*(d+razmak),Ym+a, d,Ym/2);
            QString text = m_chartDoc->m_points[i]->getLabel();
            p.drawText(textBounds, Qt::AlignCenter | Qt::TextWordWrap, text);
        }
    }
}
void ChartView::mouseDoubleClickEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        // odredjivanje gde je kliknuto
        QPoint clickedPoint(event->x(),event->y());
        if(bars.isEmpty()){
            return;
        }
        int index = -1;
        for(int i=0;i<bars.count();i++){
            if(bars[i]->contains(clickedPoint)){
                index = i;
            }
        }
        if(index == -1){
            return;
        }

        // prosledjivanje podataka dijalogu
        QString label = m_chartDoc->m_points[index]->getLabel();
        float value = m_chartDoc->m_points[index]->getValue();
        QColor colour = m_chartDoc->m_points[index]->getColour();
        ChartPointDialog dialog(label, value, colour);

        if (dialog.exec() == QDialog::Accepted){
            m_chartDoc->m_points[index]->setLabel(dialog.getLabel());
            m_chartDoc->m_points[index]->setValue(dialog.getValue());
            m_chartDoc->m_points[index]->setColour(dialog.getColour());
        }
        emit m_chartDoc->chartDataChanged();
    }
}
