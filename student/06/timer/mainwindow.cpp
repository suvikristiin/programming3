#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    minutes_ = 0;
    seconds_ = 0;
    ui->setupUi(this);
    ui->lcdNumberMin->setStyleSheet("background-color:green;");

    ui->lcdNumberSec->setStyleSheet("background-color:blue;");
    ui->lcdNumberMin->display(minutes_);
    ui->lcdNumberSec->display(seconds_);
    // luodaan ajastin
    timer_ = new QTimer(this);

    // yhdistetään ajastin slot-funktioon
    connect(timer_, &QTimer::timeout, this, &MainWindow::update_timer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    if (!timer_->isActive()) {
        timer_->start(1000);
    }


}

void MainWindow::update_timer() {

    // Vähennä sekunti
    if (seconds_ == 59) {
        minutes_++;
        seconds_ = 0;
    } else {
        seconds_++;
    }

    ui->lcdNumberMin->display(minutes_);
    ui->lcdNumberSec->display(seconds_);
}



void MainWindow::on_stopButton_clicked()
{
    if (timer_->isActive()) {
        timer_->stop();
    }


}


void MainWindow::on_resetButton_clicked()
{
    minutes_ = 0;
    seconds_ = 0;

    ui->lcdNumberMin->display(minutes_);
    ui->lcdNumberSec->display(seconds_);
}

