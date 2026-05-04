#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "utils.hh"
#include "cardwidget.hh"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager_ = make_shared<DeckManager>();

    connect(ui->decksListWidget,
            &QListWidget::itemClicked,
            this,
            &MainWindow::on_deck_clicked);

    connect(ui->cardsListWidget,
            &QListWidget::itemClicked,
            this,
            &MainWindow::on_card_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadFileButton_clicked() {

    QString filename = ui->fileNameEdit->text();

    if(!manager_->read_file(filename.toStdString())) {
        ui->infoLabel->setText(QString::fromStdString("Error loading file data"));
        return;
    }

    refresh_deckList();
    ui->infoLabel->setText("Deck added from file!");
}

void MainWindow::refresh_deckList() {
    ui->decksListWidget->clear();
    vector<string> deck_names = manager_->get_deck_names();

    for(const auto& deck_name : deck_names) {
        ui->decksListWidget->addItem(QString::fromStdString(deck_name));
    }
}

void MainWindow::clear_cardWidget_area() {

    QLayout* layout = ui->cardWidget->layout();

    if (!layout) {
        return;
    }

    while (QLayoutItem* item = layout->takeAt(0)) {
        if (item->widget())
            item->widget()->deleteLater();
        delete item;
    }
}


void MainWindow::set_cardWidget(QWidget* cardWidget) {

    auto layout = ui->cardWidget->layout();

    if (!layout) {
        layout = new QVBoxLayout(ui->cardWidget);
    }

    while (auto item = layout->takeAt(0)) {
        if (item->widget())
            item->widget()->deleteLater();
        delete item;
    }

    layout->addWidget(cardWidget);
}

void MainWindow::on_deck_clicked(QListWidgetItem* item) {
    deck_ = manager_->get_deck(item->text().toStdString());
    refresh_cardList();
}

void MainWindow::refresh_cardList() {

    ui->cardsListWidget->clear();

    if (deck_ == nullptr) {
        clear_cardWidget_area();
        ui->infoLabel->setText("Select the deck to view");
        return;
    }

    fields_= deck_->get_fields();
    auto cards = deck_->get_cards();

    for(const auto& card : cards) {
        Fields return_definitions;
        card->get_definitions(*fields_, return_definitions);
        QString definition_text = "";

        for (const auto& definition : return_definitions) {
            definition_text += QString::fromStdString(definition + " | ");
        }

        QListWidgetItem* item = new QListWidgetItem(definition_text);
        item->setData(Qt::UserRole, card->get_id());
        ui->cardsListWidget->addItem(item);
    }

    CardWidget* widget = new CardWidget(
        nullptr,
        fields_,
        CardWidget::ADD,
        ui->cardWidget
        );

    connect(widget, &CardWidget::add_card_requested,
            this, &MainWindow::add_card);

    set_cardWidget(widget);
}

void MainWindow::on_card_clicked(QListWidgetItem* item) {

    unsigned int id = item->data(Qt::UserRole).toUInt();
    auto card = deck_->get_card(id);

    CardWidget* widget = new CardWidget(
        card,
        fields_,
        CardWidget::VIEW,
        ui->cardWidget
        );

    connect(widget, &CardWidget::card_updated,
            this, &MainWindow::update_card);
    set_cardWidget(widget);
}

void MainWindow::add_card(const Fields& definitions) {

    if (!deck_) {
        ui->infoLabel->setText("Select the deck to view");
        return;
    }

    bool ok = deck_->add_card(*fields_, definitions);

    if (!ok) {
        ui->infoLabel->setText("Failed to add card");
        return;
    }

    ui->infoLabel->setText("Card added successfully");
    refresh_cardList();
}

void MainWindow::update_card(const Fields& definitions) {

    QListWidgetItem* item = ui->cardsListWidget->currentItem();

    if (!item) {
        ui->infoLabel->setText("Select the deck to view");
        return;
    }

    auto card = deck_->get_card(item->data(Qt::UserRole).toUInt());

    if (!card) {
        ui->infoLabel->setText("Card not found");
        return;
    }

    if (!card->add_new_definitions(*fields_, definitions)) {
        ui->infoLabel->setText("Failed to update card");
        return;
    }

    ui->infoLabel->setText("Card updated successfully");
    refresh_cardList();
}

void MainWindow::on_addDeckPushButton_clicked() {

    QString new_deck_name = ui->deckNameLineEdit->text();
    QString input_fields = ui->deckFieldsLineEdit->text();

    if (new_deck_name.trimmed().isEmpty()) {
        ui->infoLabel->setText("Input the deck name!");
        return;
    }

    if (input_fields.trimmed().isEmpty()) {
        ui->infoLabel->setText("Input the deck fields!");
        return;
    }

    Fields deck_fields = split(input_fields.toStdString(), ' ');

    if (manager_->deck_exists(new_deck_name.toStdString())) {
        ui->infoLabel->setText("Error adding deck!");
        return;
    }

    manager_->add_deck(new_deck_name.toStdString(), deck_fields);
    refresh_deckList();
    ui->infoLabel->setText("Deck " + new_deck_name + " added!");
}


void MainWindow::on_removeDeckPushButton_clicked() {

    QListWidgetItem* item = ui->decksListWidget->currentItem();

    if (item == nullptr)
    {
        ui->infoLabel->setText("Select the deck to be removed from the list!");
        return;
    }

    string deck_name = item->text().toStdString();

    if (!manager_->remove_deck(deck_name)) {
        ui->infoLabel->setText("Error removing deck");
        return;
    }

    refresh_deckList();
    ui->cardsListWidget->clear();
    ui->infoLabel->setText("Deck " + QString::fromStdString(deck_name) + " removed!");
    clear_cardWidget_area();
}


void MainWindow::on_removeCardPushButton_clicked()
{
    QListWidgetItem* item = ui->cardsListWidget->currentItem();

    if (item == nullptr) {
        ui->infoLabel->setText("Select the card to be removed from the list!");
        return;
    }

    unsigned int card_id = item->data(Qt::UserRole).toUInt();
    string deck_name = ui->decksListWidget->currentItem()->text().toStdString();

    if (!manager_->remove_card(deck_name, card_id)) {
        return;
        ui->infoLabel->setText("Error removing card!");
    }

    refresh_cardList();
    ui->infoLabel->setText("Card number " + QString::number(card_id) + " removed!");
}


void MainWindow::on_closePushButton_clicked() {

    QApplication::quit();
}

