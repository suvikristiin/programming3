#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "deckmanager.hh"

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

private:
    Ui::MainWindow *ui;
    shared_ptr<DeckManager> manager_;
    void refreshDeckList();
};

#endif // MAINWINDOW_HH
