#include <QApplication>
#include "mainwindow.hpp"
#include "../../backend/proc.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    std::vector<proc::Process> storage = proc::getAllProccess();
    w.update(storage);
    w.show();
    return a.exec();
}
