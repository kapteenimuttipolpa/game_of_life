#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include "grid.h"
#include <QGraphicsView>
#include "mygraphicsview.h"
#include <vector>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void set_grid_height(int height);
    void set_grid_width(int width);
    void set_current_pattern(int index);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_startButton_clicked();
    void perform_grid_update();
    void on_stopButton_clicked();
    void on_clearButton_clicked();
   // void set_current_pattern(int index);

    void on_speedSlider_sliderMoved();


private:
    Ui::MainWindow *ui;
    MyGraphicsView* grid_view;
    QGraphicsScene* scene;
    QPushButton* nextButton;
    QPushButton* startButton;
    QPushButton* stopButton;
    QPushButton* clearButton;
    QTimer* timer;
    Pattern current_pattern = blinker;
    QComboBox* user_pattern_choise;
    QComboBox* comboBox;
    Grid grid;
    Subgrid active_grid;
    QSlider* speedSlider;
    int speed = 500;
    int lsize = 50;
    int rsize = 50;

};
#endif // MAINWINDOW_H
