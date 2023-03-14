#include "mainwindow.h"
#include <QApplication>
#include "inneroutputnode.h"

MainWindow* point_w = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    point_w = &w;
    w.show();

    return a.exec();
}
