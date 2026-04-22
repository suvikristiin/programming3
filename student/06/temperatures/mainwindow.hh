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

    void on_spinBoxDegrees_valueChanged(int arg1);

    void on_pushButtonConvert_clicked();

    void on_lineEditScale_editingFinished();

private:
    Ui::MainWindow *ui;
    QString scale_;
    int input_degrees_;
};
#endif // MAINWINDOW_HH
