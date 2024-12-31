#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect sliders to slots
    ui->food_slider->setValue(INITIAL_FOOD);
    ui->pop_slider->setValue(INITIAL_POP);
    ui->food_label->setText(QString::number(INITIAL_FOOD));
    ui->pop_label->setText(QString::number(INITIAL_POP));

    connect(ui->food_slider, &QSlider::valueChanged, this, &MainWindow::onFoodSliderChange);
    connect(ui->pop_slider, &QSlider::valueChanged, this, &MainWindow::onPopulationChange);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStart);
}

void MainWindow::onFoodSliderChange(int value) {
    this->INITIAL_FOOD = value;
    ui->food_label->setText(QString::number(INITIAL_FOOD));
}

void MainWindow::onPopulationChange(int value) {
    this->INITIAL_POP = value;
    ui->pop_label->setText(QString::number(INITIAL_POP));
}

void MainWindow::onStart() {

    ui->startButton->setVisible(false);
    ui->food_slider->setVisible(false);
    ui->pop_slider->setVisible(false);
    ui->food_label->setVisible(false);
    ui->pop_label->setVisible(false);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);

    resize(this->ROW_SIZE, this->COL_SIZE); //set size of window
    this->Grid = Map(this->COL_SIZE, this->ROW_SIZE, this->INITIAL_FOOD, this->INITIAL_POP, 20);
    this->Grid.populateMap();
    // this->setStyleSheet("background-color: lightgrey;"); //interferes with drawing
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateMap);
    timer->start(FRAME_UPDATE_MS); // Repeat updates at the specified interval
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateMap() {
    this->Grid.animalMouvement();
    update();
}


void MainWindow::paintEvent(QPaintEvent *event)  {

    //std::cout<<"Happening!"<<std::endl;
    QMainWindow::paintEvent(event); // Call the base class paintEvent.

    if (!this->Grid.isInitialized()) {
        // QPainter painter(this);
        // painter.setRenderHint(QPainter::Antialiasing);

        // // Display a placeholder message
        // painter.setPen(Qt::black);
        // painter.drawText(rect(), Qt::AlignCenter, "Press Start to initialize the simulation.");
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Enable anti-aliasing.

    // Set brush and pen styles.
    painter.setPen(Qt::NoPen);
    int green_counter = 0;
    int red_counter = 0;
    for (int row = 0; row < ROW_SIZE; ++row) {
        for (int col = 0; col < COL_SIZE; ++col) {
            if (this->Grid.getGridCellValue(row, col) == 1) {  // Check for food value (1)
                painter.setBrush(Qt::green);
                painter.drawRect(col, row, 3, 3); // Draw a green rectangle
                green_counter += 1;
                //std::cout<<col<< " "<<row<<std::endl;
            }
            else if (this->Grid.getGridCellValue(row, col) == 2) {  // Check for animal value (2)
                //std::cout<<col<< " "<<row<<std::endl;
                painter.setBrush(Qt::red);
                painter.drawRect(col, row, 3, 3); // Draw a red rectangle
                red_counter += 1;
            }
        }
    }

    //std::cout<<green_counter<<std::endl;
    std::cout<<red_counter<<std::endl;
}

