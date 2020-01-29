#include <QApplication>
#include "mainwindow.hpp"
#include "../../backend/linux/allpids.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    allPids::get(storage);
    w.update(storage);
    w.show();
    return a.exec();
}
