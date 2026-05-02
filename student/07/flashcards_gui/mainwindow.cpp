#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "utils.hh"

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
    QString fields_text;

    shared_ptr<Fields> fields = deck_->get_fields();
    for (const string& field : *fields) {
        fields_text += QString::fromStdString(field + " | ");
    }

    ui->cardFieldstextBrowser->setText(fields_text);

    for(auto card : deck_->get_cards())
    {
        Fields return_definitions;

        card->get_definitions(*fields, return_definitions);

        QString definition_text = "";

        for (size_t i = 0; i < return_definitions.size(); ++i)
        {
            definition_text += QString::fromStdString(return_definitions[i] + " | ");
        }

        ui->cardsListWidget->addItem(definition_text);

    }
}

void MainWindow::onCardClicked(QListWidgetItem* item) {
    deck_ = manager_->get_deck(item->text().toStdString());
}





void MainWindow::on_addDeckPushButton_clicked()
{
    QString new_deck_name = ui->deckNameLineEdit->text();
    QString input_fields = ui->deckFieldsLineEdit->text();

    Fields deck_fields = split(input_fields.toStdString(), ' ');

    if (manager_->deck_exists(new_deck_name.toStdString()) && deck_fields.empty()) {
        return;
    }

    manager_->add_deck(new_deck_name.toStdString(), deck_fields);
    refreshDeckList();
}


void MainWindow::on_removeDeckPushButton_clicked()
{
    QString remove_deck_name = ui->removeDeckLineEdit->text();

    if (!manager_->remove_deck(remove_deck_name.toStdString())) {
        return;
    }

    manager_->remove_deck(remove_deck_name.toStdString());
    refreshDeckList();
    ui->cardFieldstextBrowser->clear();
    ui->cardsListWidget->clear();
}

