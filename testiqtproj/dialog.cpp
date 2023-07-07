#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "customgraphicsview.h"
#include "utils.h"
#include "patterns.h"
#include <QtWidgets>
#include <QMouseEvent>
#include <QAbstractItemView>
Dialog::Dialog(MainWindow* mainWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    main_window(mainWindow)
{
    //sets the color of of lcd number widget
    ui->setupUi(this);
    auto palette = ui->heightLcdNumber->palette();
    palette.setColor(palette.WindowText, Qt::black);
    palette.setColor(palette.Window, Qt::black);
    ui->heightLcdNumber->setPalette(palette);
    ui->widthLcdNumber->setPalette(palette);

    //scene for pattern preview
    QGraphicsScene* scene = new QGraphicsScene;
    ui->previewView->setScene(scene);


}
Dialog::~Dialog(){
    delete ui;
}
/**
 * @brief Dialog::on_buttonBox_accepted
 * When accept button is pressed, inits grid
 * and opens main window
 */
void Dialog::on_buttonBox_accepted()
{
    close();
    main_window->on_clearButton_clicked();
    main_window->show();
}
/**
 * @brief Dialog::on_widthSlider_sliderReleased
 * updates grids width
 */
void Dialog::on_widthSlider_sliderReleased()
{
    if(main_window){
        int width = ui->widthSlider->value();
        main_window->set_grid_width(width);
    }
}
/**
 * @brief Dialog::on_heightSlider_sliderReleased
 * updates grids height on slider release
 */
void Dialog::on_heightSlider_sliderReleased()
{
    if(main_window){
        int height = ui->heightSlider->value();
        main_window->set_grid_height(height);
    }
}
/**
 * @brief Dialog::on_comboBox_activated
 * selects pattern and preview it on the screen
 * @param index
 */
void Dialog::on_comboBox_activated(int index)
{
    selected_pattern = all_patterns[index];
    print_preview(selected_pattern);
    main_window->set_current_pattern_dialog(index);
}

/**
 * @brief Dialog::on_RandpushButton_clicked
 * generates random pattern
 * and prints it to preview
 */
void Dialog::on_RandpushButton_clicked()
{
    Pattern rand_p = Utils::random_pattern();
    main_window->set_curr_pat(rand_p);
    print_preview(rand_p);
}
/**
 * @brief Dialog::print_preview
 * prints preview
 * @param selected_pattern
 */
void Dialog::print_preview(Pattern& selected_pattern){
    QGraphicsScene* scene = new QGraphicsScene;
    ui->previewView->setScene(scene);
    scene->setForegroundBrush(Qt::NoBrush);
    for(Coord c : selected_pattern.coords){
        scene->addRect(c.col * (cell_size + spacing),
                       c.row * (cell_size + spacing),
                       cell_size,
                       cell_size,
                       QPen(Qt::NoPen),
                       QBrush(Qt::black));
    }

    ui->previewView->setScene(scene);

}

