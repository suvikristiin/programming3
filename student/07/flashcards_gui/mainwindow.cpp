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

void MainWindow::refreshDeckList()
{
    vector<string> deck_names = manager_->get_deck_names();

    for(auto deck_name : deck_names)
    {
        ui->decksListWidget->addItem(QString::fromStdString(deck_name));
    }
}



