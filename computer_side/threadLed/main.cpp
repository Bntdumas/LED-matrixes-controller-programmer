#include <QApplication>
#include "ledCube.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ledCube *_ledCube = new ledCube();
    _ledCube->show();
    return a.exec();
}
