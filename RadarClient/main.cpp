#include "mainwindow.h"
#include "radarobject.h"

#include <QApplication>

int main(int argc, char *argv[])
{           
    QApplication a(argc, argv);

    qRegisterMetaType<RadarObject>();

    MainWindow w;
    w.show();
    return a.exec();
}
