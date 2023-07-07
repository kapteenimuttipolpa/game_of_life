#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include "grid.h"
#include <QGraphicsView>
#include "mygraphicsview.h"
#include <vector>
#include <QLabel>
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
    void set_curr_pat(Pattern rand);
    void on_clearButton_clicked();
    void set_current_pattern_dialog(int index);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_startButton_clicked();
    void on_stopButton_clicked();
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
    Pattern current_pattern = full;
    QComboBox* user_pattern_choise;
    QComboBox* comboBox;
    Grid grid;
    CoordVect active_grid;
    QSlider* speedSlider;
    QLabel* counter_label;
    int counter;
    int speed = 500;
    int lsize = 50;
    int rsize = 50;

};
#endif // MAINWINDOW_H
