#include "face_check.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    face_check w;
    w.show();
    return a.exec();
}
