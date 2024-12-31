#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include "animal.h"
#include "map.h"
#include "qdebug.h"
#include "qlogging.h"



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
    void updateMap();
    void onFoodSliderChange(int value);
    void onPopulationChange(int value);
    void onStart();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *event) override;
    int ROW_SIZE = 500;
    int COL_SIZE = 500;
    int INITIAL_POP = 20;
    int INITIAL_FOOD = 1000;
    int FRAME_UPDATE_MS = 500; // 1000ms = 1s
    Map Grid;
};

#endif // MAINWINDOW_H
