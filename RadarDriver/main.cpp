#include <QCoreApplication>

#include "radardriver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RadarDriver driver(10, 5);
    driver.start();

    return a.exec();
}
