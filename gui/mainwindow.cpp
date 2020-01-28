#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::_testGetProccesess(proc::Storage & storage) {
    for(size_t i = 0; i < storage.procceses.size(); i++) {
        auto& rec = storage.procceses[i];
        ui->textEdit->append(
            QString::fromStdString(rec.name + " | " + rec.dir.d_name + " | " + rec.path));
    }
}
