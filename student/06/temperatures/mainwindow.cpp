#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEditScale_editingFinished()
{
    scale_ = ui->lineEditScale->text();
}


void MainWindow::on_spinBoxDegrees_valueChanged(int arg1)
{
    input_degrees_ = arg1;

}




void MainWindow::on_pushButtonConvert_clicked()
{
    QString result_s;

    if (scale_ == "Celsius") {
        int result_celcius = 1.8 * input_degrees_ + 32.0;
        result_s = QString::number(result_celcius);
    } else if (scale_ == "Fahrenheit") {
        int result_fahr = (input_degrees_ - 32.0) / 1.8;
        result_s = QString::number(result_fahr);
    } else {
        result_s = "Unknown scale";
    }

    ui->textBrowser->setText(result_s);
}

