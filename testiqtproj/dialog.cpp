#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

Dialog::Dialog(MainWindow* mainWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    main_window(mainWindow)
{
    ui->setupUi(this);
    auto palette = ui->heightLcdNumber->palette();
    palette.setColor(palette.WindowText, Qt::black);
    palette.setColor(palette.Window, Qt::black);
    ui->heightLcdNumber->setPalette(palette);
    ui->widthLcdNumber->setPalette(palette);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    close();
    main_window->show();

}



void Dialog::on_widthSlider_sliderReleased()
{
    if(main_window){
        int width = ui->widthSlider->value();
        main_window->set_grid_width(width);
    }
}


void Dialog::on_heightSlider_sliderReleased()
{
    if(main_window){
        int height = ui->heightSlider->value();
        main_window->set_grid_height(height);
    }
}


void Dialog::on_comboBox_activated(int index)
{
    main_window->set_current_pattern(index);
}

