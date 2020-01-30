#include <QApplication>
#include "mainwindow.hpp"
#include "../../backend/proc.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    std::vector<proc::Process> storage = proc::getAllProccess();
    for (size_t i = 0; i < storage.size(); i++) {
        std::cout << storage[i].pid << std::endl;
        storage[i].loadFd();
    }
    w.update(storage);
    w.show();
    return a.exec();
}
