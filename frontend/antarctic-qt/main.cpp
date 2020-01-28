#include <QApplication>
#include "mainwindow.hpp"
#include "../../backend/antarcticore-linux/allpids.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    proc::Storage storage;
    allPids::get(storage);
    w.show();
    return a.exec();
}
