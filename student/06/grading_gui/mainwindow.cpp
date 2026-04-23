#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecalculator.hh"

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

void MainWindow::on_spinBoxN_valueChanged(int arg1)
{
    n = arg1;
}


void MainWindow::on_spinBoxP1_valueChanged(int arg1)
{
    p1 = arg1;
}


void MainWindow::on_spinBoxP2_valueChanged(int arg1)
{
    p2 = arg1;
}


void MainWindow::on_spinBoxB_valueChanged(int arg1)
{
    b = arg1;
}


void MainWindow::on_spinBoxE_valueChanged(int arg1)
{
    e = arg1;
}

void MainWindow::on_pushButtonCalculate_clicked()
{
    b = ui->spinBoxB->value();

    int totalN = n + b;

    if (totalN > 500) {
        totalN = 500;
    }

    int result_excercises = score_from_weekly_exercises(totalN);
    int result_projects = score_from_projects(p1, p2);
    int total_result = calculate_total_grade(n, p1, p2, e);

    QString result =
        "W-Score: " + QString::number(result_excercises) +
        "\nP-Score: " + QString::number(result_projects) +
        "\nTotal grade: " + QString::number(total_result);

    ui->textBrowser->setPlainText(result);

}
