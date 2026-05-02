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

        QListWidgetItem* item = new QListWidgetItem(definition_text);
        item->setData(Qt::UserRole, card->get_id());
        ui->cardsListWidget->addItem(item);

    }
}

void MainWindow::onCardClicked(QListWidgetItem* item) {
    Q_UNUSED(item);
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
    QListWidgetItem* item = ui->decksListWidget->currentItem();

    if (item == nullptr)
    {
        ui->infoLabel->setText("Valitse poistettava pakka!");
        return;
    }

    QString deck_name_q = ui->decksListWidget->currentItem()->text();
    string deck_name = deck_name_q.toStdString();

    if (!manager_->remove_deck(deck_name)) {
        return;
    }

    refreshDeckList();
    ui->cardFieldstextBrowser->clear();
    ui->cardsListWidget->clear();

    ui->infoLabel->setText("Pakka " + deck_name_q + " poistettu!");
}


void MainWindow::on_removeCardPushButton_clicked()
{
    QListWidgetItem* item = ui->cardsListWidget->currentItem();

    if (item == nullptr)
    {
        ui->infoLabel->setText("Valitse kortti!");
        return;
    }

    unsigned int card_id =
        item->data(Qt::UserRole).toUInt();

    QString deck_name_q = ui->decksListWidget->currentItem()->text();
    string deck_name = deck_name_q.toStdString();


    manager_->remove_card(deck_name, card_id);

    refreshCardList();
    ui->infoLabel->setText("Kortti numero" + QString::number(card_id) + " poistettu!");
}

