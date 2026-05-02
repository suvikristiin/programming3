#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "deckmanager.hh"
#include <QListWidgetItem>

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

private:
    Ui::MainWindow *ui;
    shared_ptr<DeckManager> manager_;
    shared_ptr<Deck> deck_;
    void refreshDeckList();
    void onDeckClicked(QListWidgetItem* item);
    void onCardClicked(QListWidgetItem* item);
    void refreshCardList();
};

#endif // MAINWINDOW_HH
