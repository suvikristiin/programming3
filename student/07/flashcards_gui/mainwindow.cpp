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

    if(!manager_->read_file(filename.toStdString())) {
        ui->infoLabel->setText(QString::fromStdString("Error loading file data"));
        return;
    }

    refreshDeckList();
    ui->infoLabel->setText("Deck added from file!");
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

void MainWindow::showCardWidget(CardWidget* widget)
{
    QLayout* layout = ui->cardWidget->layout();

    if (!layout) {
        layout = new QVBoxLayout(ui->cardWidget);
        ui->cardWidget->setLayout(layout);
    }

    QLayoutItem* child;
    while ((child = layout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    layout->addWidget(widget);
}

void MainWindow::clearCardWidgetArea()
{
    QLayout* layout = ui->cardWidget->layout();
    if (!layout) return;

    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (item->widget())
            item->widget()->deleteLater();
        delete item;
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

    if (deck_ == nullptr)
    {
        clearCardWidgetArea();
        ui->infoLabel->setText("Select the deck to view");
        return;
    }

    fields_= deck_->get_fields();
    auto cards= deck_->get_cards();

    for(auto card : cards)
    {
        Fields return_definitions;

        card->get_definitions(*fields_, return_definitions);

        QString definition_text = "";

        for (size_t i = 0; i < return_definitions.size(); ++i)
        {
            definition_text += QString::fromStdString(return_definitions[i] + " | ");
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

    connect(widget, &CardWidget::addCardRequested,
            this, &MainWindow::onAddCard);

    showCardWidget(widget);
}



void MainWindow::onCardClicked(QListWidgetItem* item) {

    unsigned int id = item->data(Qt::UserRole).toUInt();

    auto card = deck_->get_card(id);

    CardWidget* widget = new CardWidget(
        card,
        fields_,
        CardWidget::VIEW,
        ui->cardWidget
        );

    connect(widget, &CardWidget::cardUpdated,
            this, &MainWindow::onUpdateCard);
    showCardWidget(widget);
}

void MainWindow::onAddCard(const Fields& definitions)
{
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
    refreshCardList();
}

void MainWindow::onUpdateCard(const Fields& definitions) {

    QListWidgetItem* item = ui->cardsListWidget->currentItem();

    if (!item) {
        ui->infoLabel->setText("Select the deck to view");
        return;
    }

    unsigned int id = item->data(Qt::UserRole).toUInt();
    auto card = deck_->get_card(id);

    if (!card) {
        ui->infoLabel->setText("Card not found");
        return;
    }

    bool ok = card->add_new_definitions(*fields_, definitions);

    if (!ok) {
        ui->infoLabel->setText("Failed to update card");
        return;
    }

    ui->infoLabel->setText("Card updated successfully");
    refreshCardList();
}

void MainWindow::on_addDeckPushButton_clicked()
{
    QString new_deck_name = ui->deckNameLineEdit->text();
    QString input_fields = ui->deckFieldsLineEdit->text();

    if (input_fields.trimmed().isEmpty())
    {
        ui->infoLabel->setText("Input the deck fields!");
        return;
    }

    Fields deck_fields = split(input_fields.toStdString(), ' ');

    if (manager_->deck_exists(new_deck_name.toStdString())) {
        ui->infoLabel->setText("Error adding deck!");
        return;
    }

    manager_->add_deck(new_deck_name.toStdString(), deck_fields);
    refreshDeckList();
    ui->infoLabel->setText("Deck " + new_deck_name + " added!");
}


void MainWindow::on_removeDeckPushButton_clicked()
{
    QListWidgetItem* item = ui->decksListWidget->currentItem();

    if (item == nullptr)
    {
        ui->infoLabel->setText("Select the deck to be removed from the list!");
        return;
    }

    QString deck_name_q = ui->decksListWidget->currentItem()->text();
    string deck_name = deck_name_q.toStdString();

    if (!manager_->remove_deck(deck_name)) {
        ui->infoLabel->setText("Error removing deck");
        return;
    }

    refreshDeckList();

    ui->cardsListWidget->clear();

    ui->infoLabel->setText("Deck " + deck_name_q + " removed!");

    clearCardWidgetArea();
}


void MainWindow::on_removeCardPushButton_clicked()
{
    QListWidgetItem* item = ui->cardsListWidget->currentItem();

    if (item == nullptr)
    {
        ui->infoLabel->setText("Select the card to be removed from the list!");
        return;
    }

    unsigned int card_id =
        item->data(Qt::UserRole).toUInt();

    QString deck_name_q = ui->decksListWidget->currentItem()->text();
    string deck_name = deck_name_q.toStdString();


    if (!manager_->remove_card(deck_name, card_id)) {
        return;
        ui->infoLabel->setText("Error removing card!");
    }

    refreshCardList();
    ui->infoLabel->setText("Card number " + QString::number(card_id) + " removed!");
}


void MainWindow::on_closePushButton_clicked()
{
    QApplication::quit();
}

