#include "mainwindow.hh"
#include <QSpinBox>
#include <QGridLayout>
#include <QSlider>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    QGridLayout* gLayout = new QGridLayout(central);

    horizontalSliderRed = new QSlider(Qt::Horizontal);
    horizontalSliderGreen = new QSlider(Qt::Horizontal);
    horizontalSliderBlue = new QSlider(Qt::Horizontal);
    spinBoxRed_ = new QSpinBox();
    colorLabel_ = new QLabel();

    spinBoxRed_->setObjectName("spinBoxRed");
    horizontalSliderRed->setObjectName("horizontalSliderRed");
    gLayout->addWidget(horizontalSliderRed,0,1);
    gLayout->addWidget(spinBoxRed_,0,2);

    spinBoxGreen_ = new QSpinBox();
    spinBoxGreen_->setObjectName("spinBoxGreen");
    horizontalSliderGreen->setObjectName("horizontalSliderGreen");
    gLayout->addWidget(horizontalSliderGreen,1,1);
    gLayout->addWidget(spinBoxGreen_,1,2);

    spinBoxBlue_ = new QSpinBox();
    spinBoxBlue_->setObjectName("spinBoxBlue");
    horizontalSliderBlue->setObjectName("horizontalSliderBlue");
    gLayout->addWidget(horizontalSliderBlue,2,1);
    gLayout->addWidget(spinBoxBlue_,2,2);
    gLayout->addWidget(colorLabel_, 3,1);

    horizontalSliderRed->setMinimum(0);
    horizontalSliderRed->setMaximum(RGB_VALUE_MAX);

    horizontalSliderGreen->setMinimum(0);
    horizontalSliderGreen->setMaximum(RGB_VALUE_MAX);

    horizontalSliderBlue->setMinimum(0);
    horizontalSliderBlue->setMaximum(RGB_VALUE_MAX);

    spinBoxRed_->setMinimum(0);
    spinBoxRed_->setMaximum(RGB_VALUE_MAX);

    spinBoxGreen_->setMinimum(0);
    spinBoxGreen_->setMaximum(RGB_VALUE_MAX);

    spinBoxBlue_->setMinimum(0);
    spinBoxBlue_->setMaximum(RGB_VALUE_MAX);




    connect(horizontalSliderRed, &QSlider::valueChanged,
            spinBoxRed_, &QSpinBox::setValue);
    connect(spinBoxRed_, &QSpinBox::valueChanged,
            horizontalSliderRed, &QSlider::setValue);

    connect(horizontalSliderGreen, &QSlider::valueChanged,
            spinBoxGreen_, &QSpinBox::setValue);
    connect(spinBoxGreen_, &QSpinBox::valueChanged,
            horizontalSliderGreen, &QSlider::setValue);

    connect(horizontalSliderBlue, &QSlider::valueChanged,
            spinBoxBlue_, &QSpinBox::setValue);
    connect(spinBoxBlue_, &QSpinBox::valueChanged,
            horizontalSliderBlue, &QSlider::setValue);

    connect(horizontalSliderRed, &QSlider::valueChanged, this, &MainWindow::onColorChanged);
    connect(horizontalSliderGreen, &QSlider::valueChanged, this, &MainWindow::onColorChanged);
    connect(horizontalSliderBlue, &QSlider::valueChanged, this, &MainWindow::onColorChanged);


    onColorChanged();
}

MainWindow::~MainWindow() {}

void MainWindow::onColorChanged()
{
    QColor color(
        horizontalSliderRed->value(),
        horizontalSliderGreen->value(),
        horizontalSliderBlue->value()
        );

    QPixmap pixmap(64,64);
    pixmap.fill(color);
    colorLabel_->setPixmap(pixmap);

}


