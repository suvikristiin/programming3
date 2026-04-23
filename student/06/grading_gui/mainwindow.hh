#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonCalculate_clicked();

    void on_spinBoxN_valueChanged(int arg1);

    void on_spinBoxP1_valueChanged(int arg1);

    void on_spinBoxP2_valueChanged(int arg1);

    void on_spinBoxB_valueChanged(int arg1);

    void on_spinBoxE_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    int n;
    int p1;
    int p2;
    int b;
    int e;
};
#endif // MAINWINDOW_HH
