#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grid.h"
#include "patterns.h"
#include "grid.h"
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QApplication>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        grid_view = new QGraphicsView(this);
        scene = new QGraphicsScene(this);
        grid = init_grid(10, 10, glider);
        print_grid(grid, grid_view, scene);

        // Create the button and connect its clicked signal to your slot function
        nextButton = new QPushButton("Next Generation", this);
        connect(nextButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

        // Create the vertical layout, add the grid_view and the button
        QVBoxLayout* mainLayout = new QVBoxLayout;
        mainLayout->addWidget(grid_view);
        mainLayout->addWidget(nextButton);

        // Create a central widget to hold the layout
        QWidget* centralWidget = new QWidget(this);
        centralWidget->setLayout(mainLayout);

        // Set the central widget
        setCentralWidget(centralWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    next_generation(grid);
    update_grid(grid);
    print_grid(grid, grid_view, scene);
}

