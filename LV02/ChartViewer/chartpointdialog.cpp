#include "chartpointdialog.h"
#include "ui_chartpointdialog.h"

ChartPointDialog::ChartPointDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartPointDialog)
{
    ui->setupUi(this);
    ui->leValue->setValidator(new QIntValidator(0, 100, this));
}
ChartPointDialog::ChartPointDialog(QString label, float value, QColor colour, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartPointDialog)
{
    ui->setupUi(this);
    ui->leValue->setValidator(new QIntValidator(0, 100, this));
    ui->leLabel->setText(label);
    ui->leValue->setText(QString::number(value));
    ui->leColour->setText(colour.name());
}

ChartPointDialog::~ChartPointDialog()
{
    delete ui;
}

QString ChartPointDialog::getLabel(){
    QString label = ui->leLabel->text();
    return label;
}

float ChartPointDialog::getValue(){
    float value = ui->leValue->text().toFloat();
    return value;
}

QColor ChartPointDialog::getColour(){
    QColor color;
    color.setNamedColor(ui->leColour->text());
    return color;
}

void ChartPointDialog::on_tbColour_clicked()
{
    QColorDialog colorDialog;
    if(colorDialog.exec() == QDialog::Accepted)
    {
        QColor temp = colorDialog.selectedColor();
        ui->leColour->setText(temp.name());
    }
}
