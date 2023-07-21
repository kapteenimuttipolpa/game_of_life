#ifndef DIALOG_H
#define DIALOG_H
#include "mainwindow.h"
#include "patterns.h"
#include <QDialog>
#include <QMouseEvent>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(MainWindow* mainWindow, QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_buttonBox_accepted();


    void on_widthSlider_sliderReleased();

    void on_heightSlider_sliderReleased();

    void on_comboBox_activated(int index);

    void on_RandpushButton_clicked();

    void print_preview(Pattern& selected_pattern);

private:
    Ui::Dialog *ui;
    MainWindow* main_window;
    QGraphicsScene* scene;
    MyGraphicsView* previewView;
    Pattern selected_pattern;
};

#endif // DIALOG_H
