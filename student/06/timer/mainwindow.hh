#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // Add your slots here.

    void on_startButton_clicked();


    void on_stopButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* timer_;
    // Add other necessary members here.
    void update_timer();
    int minutes_;
    int seconds_;
};

#endif // MAINWINDOW_HH
