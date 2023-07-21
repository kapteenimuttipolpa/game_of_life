#include "mainwindow.h"
#include "dialog.h"
#include <QApplication>
#include <QThread>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* dialog_window = new MainWindow();
    Dialog d(dialog_window);
    d.show();
    return a.exec();
}
