#include <QApplication>

#include "FaceTest.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    FaceTest w;
    w.show();
    return a.exec();
}
