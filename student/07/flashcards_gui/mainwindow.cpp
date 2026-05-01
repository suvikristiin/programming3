#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager_ = make_shared<DeckManager>();
    connect(ui->decksListWidget,
            &QListWidget::itemClicked,
            this,
            &MainWindow::onDeckClicked);

    connect(ui->cardsListWidget,
            &QListWidget::itemClicked,
            this,
            &MainWindow::onCardClicked);
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
    ui->decksListWidget->clear();
    vector<string> deck_names = manager_->get_deck_names();

    for(auto deck_name : deck_names)
    {
        ui->decksListWidget->addItem(QString::fromStdString(deck_name));

    }

}

void MainWindow::onDeckClicked(QListWidgetItem* item)
{
    deck_ = manager_->get_deck(item->text().toStdString());
    refreshCardList();

}

void MainWindow::refreshCardList() {

    ui->cardsListWidget->clear();

    for(auto card : deck_->get_cards())
    {
        Fields fields = card->get_fields();

        Fields return_definitions;

        card->get_definitions(fields, return_definitions);

        QString definition_text = "";

        for (size_t i = 0; i < fields.size(); ++i)
        {
            definition_text += QString::fromStdString(fields[i] + ": " + return_definitions[i] + " | ");
        }

        ui->cardsListWidget->addItem(definition_text);

    }
}

void MainWindow::onCardClicked(QListWidgetItem* item) {
    deck_ = manager_->get_deck(item->text().toStdString());
}




