#ifndef CHARTPOINTDIALOG_H
#define CHARTPOINTDIALOG_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>

namespace Ui {
class ChartPointDialog;
}

class ChartPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChartPointDialog(QWidget *parent = nullptr);
    ChartPointDialog(QString label, float value, QColor colour, QWidget *parent = nullptr);
    ~ChartPointDialog();

    QString getLabel();
    float getValue();
    QColor getColour();

private slots:
    void on_tbColour_clicked();

private:
    Ui::ChartPointDialog *ui;
};

#endif // CHARTPOINTDIALOG_H
