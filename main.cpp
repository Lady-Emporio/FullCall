#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Settings::S();
    MainWindow w;
    w.show();

    return a.exec();
}
