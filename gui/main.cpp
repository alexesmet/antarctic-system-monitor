#include <unistd.h>
#include <dirent.h>
#include <sys/types.h> // for opendir(), readdir(), closedir()
#include <sys/stat.h> // for stat()

#include <cstdlib>
#include <cstdio>

#include <QApplication>
#include <QTextEdit>
#include "../core/allpids.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    allPids::get(proc::storage);
    w._testGetProccesess(proc::storage);
    w.show();
    return a.exec();
}
