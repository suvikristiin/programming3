#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <iostream>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager_ = make_shared<DeckManager>();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadFileButton_clicked()
{
    QString filename = ui->fileNameEdit->text();
    manager_->read_file(filename.toStdString());

    refreshDeckList();
}



