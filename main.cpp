#include <unistd.h>
#include <dirent.h>
#include <sys/types.h> // for opendir(), readdir(), closedir()
#include <sys/stat.h> // for stat()

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>

#include <QApplication>
#include <QTextEdit>

#include "mainwindow.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.getAllTasks();

    w.show();
    return a.exec();
}
