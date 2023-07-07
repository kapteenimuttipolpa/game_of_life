#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mygraphicsview.h"
#include "grid.h"
#include "patterns.h"
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QApplication>
#include <QVBoxLayout>
#include <chrono>
#include <thread>
#include <QThread>
#include <QTimer>
#include <QGridLayout>
#include <QComboBox>
#include <QDebug>
#include <QSlider>
#include <QLabel>
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    grid_view = new MyGraphicsView(this); // Creates a new graphics view (The empty box where scene goes)
    scene = new QGraphicsScene(this);
    grid_view->setCacheMode(QGraphicsView::CacheBackground); // random optimization, not sure if it made it faster
    grid_view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate); //^^
    grid_view->setRenderHint(QPainter::Antialiasing, true); // ^^
    print_grid(grid, grid_view, scene);

    // Creates a button that updates current gen to next gen
    nextButton = new QPushButton("Next Generation", this);
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

    // Create a start button that starts a timer (loop)
    startButton = new QPushButton("Start", this);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::on_startButton_clicked);

    // Create a stop button that stops the loop
    stopButton = new QPushButton("Stop", this);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::on_stopButton_clicked);

    // Create a clear button that resets the game to starting position
    clearButton = new QPushButton("Clear", this);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::on_clearButton_clicked);

    speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setMinimum(10);
    speedSlider->setMaximum(1000);
    speedSlider->setValue(200);
    connect(speedSlider, &QSlider::sliderReleased, this, &MainWindow::on_speedSlider_sliderMoved);

    // Create the vertical layout, add the grid_view and the button
    //QVBoxLayout* mainLayout = new QVBoxLayout;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QComboBox *comboBox = new QComboBox;
    QGridLayout* buttonLayout = new QGridLayout;
    comboBox->addItem(tr("blinker"));
    comboBox->addItem(tr("block"));
    comboBox->addItem(tr("glider"));
    comboBox->addItem(tr("gosper_glider_gun"));
    comboBox->addItem(tr("c_heptomino"));
    comboBox->addItem(tr("biloaf"));
    comboBox->addItem(tr("octagon_II"));
    comboBox->addItem(tr("copperhead"));
    comboBox->addItem(tr("diamond_4_8_12"));
    comboBox->addItem(tr("full"));

    mainLayout->addWidget(grid_view);
    buttonLayout->addWidget(nextButton,1,0);
    buttonLayout->addWidget(startButton,0,0);
    buttonLayout->addWidget(stopButton,0,1);
    buttonLayout->addWidget(clearButton,1,1);
    buttonLayout->addWidget(comboBox, 2, 0);
    buttonLayout->addWidget(speedSlider, 2,1);
    connect(comboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::set_current_pattern);

    counter = 0;
    counter_label = new QLabel(this);
    counter_label->setText("Counter: 0");
    statusBar()->addWidget(counter_label);

    // Create a central widget to hold the layout
    QWidget* centralWidget = new QWidget(this);
    mainLayout->addLayout(buttonLayout);

    //centralWidget->setLayout(buttonLayout);
    centralWidget->setLayout(mainLayout);
    // Set the central widget
    setCentralWidget(centralWidget);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, &MainWindow::on_pushButton_clicked);



}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    next_generation(grid, active_grid);
    update_grid(grid, active_grid);
    scene->clear();
    print_grid(grid, grid_view, scene);
    counter++;
    counter_label->setText("Evolution " + QString::number(counter));
}

void MainWindow::on_startButton_clicked(){

    timer->start(speed);
}
void MainWindow::on_stopButton_clicked(){
    timer->stop();
}
void MainWindow::on_clearButton_clicked(){
    timer->stop();
    active_grid.clear();
    scene->clear();
    counter = 0;
    counter_label->setText("Evolution: 0");
    grid = init_grid(active_grid, lsize, rsize, current_pattern);
    print_grid(grid, grid_view, scene);
}
void MainWindow::perform_grid_update(){
    bool is_changed = next_generation(grid, active_grid);
    if(!is_changed){
        timer->stop();
    }
    else update_grid(grid, active_grid);
    scene->clear();
    print_grid(grid, grid_view, scene);
}
void MainWindow::set_current_pattern(int index){
    timer->stop();
    active_grid.clear();
    scene->clear();
    current_pattern = all_patterns[index];
    grid = init_grid(active_grid, lsize, rsize, current_pattern);
    print_grid(grid, grid_view, scene);
    counter = 0;
    counter_label->setText("Counter: 0");
}

void MainWindow::on_speedSlider_sliderMoved()
{
    speed = speedSlider->value();
    timer->setInterval(speed);
}
void MainWindow::set_grid_height(int height){
    lsize = height;
    scene->clear();
    grid = init_grid(active_grid, lsize, rsize, current_pattern);
    print_grid(grid, grid_view, scene);

}
void MainWindow::set_grid_width(int width){
    rsize = width;
    scene->clear();
    grid = init_grid(active_grid, lsize, rsize, current_pattern);
    print_grid(grid, grid_view, scene);

}
int MainWindow::get_lsize(){
    return lsize;
}
int MainWindow::get_rsize(){
    return rsize;
}
void MainWindow::set_curr_pat(Pattern rand){
    current_pattern = rand;
}
