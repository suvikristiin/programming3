#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QSlider>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    const int RGB_VALUE_MAX = 255;
    QSpinBox* spinBoxRed_;
    QSpinBox* spinBoxGreen_;
    QSpinBox* spinBoxBlue_;
    QSlider* horizontalSliderRed;
    QSlider* horizontalSliderGreen;
    QSlider* horizontalSliderBlue;
    QLabel* colorLabel_;
    void onColorChanged();

};
#endif // MAINWINDOW_H
