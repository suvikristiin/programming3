#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "deckmanager.hh"
#include <QListWidgetItem>
#include "cardwidget.hh"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadFileButton_clicked();

    void on_addDeckPushButton_clicked();

    void on_removeDeckPushButton_clicked();

    void on_removeCardPushButton_clicked();

    void on_closePushButton_clicked();
    void onAddCard(const Fields& definitions);
    void onUpdateCard(const Fields& definitions);
    void clearCardWidgetArea();

private:
    Ui::MainWindow *ui;
    shared_ptr<DeckManager> manager_;
    shared_ptr<Deck> deck_;
    shared_ptr<Fields> fields_;
    void refreshDeckList();
    void onDeckClicked(QListWidgetItem* item);
    void onCardClicked(QListWidgetItem* item);
    void refreshCardList();
    void showCardWidget(CardWidget* widget);
};

#endif // MAINWINDOW_HH
