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
#include <QTimer>
#include <QGridLayout>
#include <QComboBox>
#include <QDebug>
#include <QSlider>
#include <QLabel>
#include <QElapsedTimer>
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

    print_grid(active_grid, grid_view, scene);

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

    // Create a speed slider so user can change the generation speed
    speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setMinimum(10);
    speedSlider->setMaximum(1000);
    speedSlider->setValue(200);
    connect(speedSlider, &QSlider::sliderReleased, this, &MainWindow::on_speedSlider_sliderMoved);

    // Create some layouts where we can store buttons and graphicview etc
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QComboBox *comboBox = new QComboBox;
    QGridLayout* buttonLayout = new QGridLayout;
    // Add stuff to the comboBox (Dropdown menu)
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
    // Selecting item from comboBox triggers this and sets the selected item as current pattern
    connect(comboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::set_current_pattern);
    // Counter to keep track of the generation count
    counter = 0;
    counter_label = new QLabel(this);
    counter_label->setText("Counter: 0");
    statusBar()->addWidget(counter_label);

    elapsed_label = new QLabel(this);
    elapsed_label->setText("Time elapsed: ");
    statusBar()->addWidget(elapsed_label);

    // Create a central widget to hold the layout
    QWidget* centralWidget = new QWidget(this);
    mainLayout->addLayout(buttonLayout);

    centralWidget->setLayout(mainLayout);
    // Set the central widget
    setCentralWidget(centralWidget);
    // Create a timer and connect it to on_pushButton_clicked
    // button gets clicked every time the timer ticks
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, &MainWindow::on_pushButton_clicked);
    q_timer = new QElapsedTimer;
}

MainWindow::~MainWindow()
{
    delete ui;
}



/**
 * @brief MainWindow::on_pushButton_clicked
 * updates next gen
 * updates grid
 * clears current scene (to avoid stacking scenes)
 * prints grid
 * updates counter
 */
void MainWindow::on_pushButton_clicked()
{
    next_generation(grid, active_grid);
    update_grid(grid, active_grid);
    scene->clear();
    print_grid(active_grid, grid_view, scene);
    counter++;
    counter_label->setText("Evolution " + QString::number(counter));
    if(counter == 20000){
        on_clearButton_clicked();
    }
}
/**
 * @brief MainWindow::on_startButton_clicked
 * starts the timer with speed given in speed slider
 */
void MainWindow::on_startButton_clicked(){

    timer->start(speed);
    q_timer->start();
}
/**
 * @brief MainWindow::on_stopButton_clicked
 * stops the timer
 */
void MainWindow::on_stopButton_clicked(){
    timer->stop();
}
/**
 * @brief MainWindow::on_clearButton_clicked
 * resets the state to original state
 */
void MainWindow::on_clearButton_clicked(){
    timer->stop();
    active_grid.clear();
    scene->clear();
    counter = 0;
    counter_label->setText("Evolution: 0");
    qint64 elapsed_time = q_timer->nsecsElapsed();
    double seconds = elapsed_time / 1000000000.0;
    elapsed_label->setText("Elapsed seconds: " + QString::number(seconds));
    grid = init_grid(active_grid, lsize, rsize, current_pattern);
    print_grid(active_grid, grid_view, scene);
}
/**
 * @brief MainWindow::set_current_pattern
 * @param index = index from all_patterns
 * sets current pattern from user selection
 */
void MainWindow::set_current_pattern(int index){
    timer->stop();
    active_grid.clear();
    scene->clear();
    current_pattern = all_patterns[index];
    grid = init_grid(active_grid, lsize, rsize, current_pattern);
    print_grid(active_grid, grid_view, scene);
    counter = 0;
    counter_label->setText("Counter: 0");
}
/**
 * @brief MainWindow::on_speedSlider_sliderMoved
 * updates the speed
 */
void MainWindow::on_speedSlider_sliderMoved()
{
    speed = speedSlider->value();
    timer->setInterval(speed);
}
/**
 * @brief MainWindow::set_grid_height
 * @param height = user selected height from dialog
 */
void MainWindow::set_grid_height(int height){
    lsize = height;
}
/**
 * @brief MainWindow::set_grid_width
 * @param width = user selected width from dialog
 */
void MainWindow::set_grid_width(int width){
    rsize = width;
}
/**
 * @brief MainWindow::set_curr_pat
 * sets the pattern as random pattern
 * @param rand
 */
void MainWindow::set_curr_pat(Pattern rand){
    current_pattern = rand;
}
/**
 * @brief MainWindow::set_current_pattern_dialog
 * sets the current pattern in dialog for preview
 *
 * @param index
 */
void MainWindow::set_current_pattern_dialog(int index){
    current_pattern = all_patterns[index];
}
