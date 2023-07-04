#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "grid.h"
#include "QGraphicsView"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void nextGenerationClicked(Grid& grid);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsView* grid_view;
    QGraphicsScene* scene;
    QPushButton* nextButton;
    Grid grid;
};
#endif // MAINWINDOW_H
