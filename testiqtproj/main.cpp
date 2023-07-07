#include "mainwindow.h"
#include "dialog.h"
#include <QApplication>
#include <QThread>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* mainWindow = new MainWindow();
    Dialog d(mainWindow);
    d.show();
    return a.exec();
}
