#include "mainwindow.hpp"

//#include "../../backend/antarcticore-linux/test.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}, ui{new Ui::MainWindow} {
    ui->setupUi(this);
//    ui->textEdit->append("Test");
//    ui->textEdit->append(QString::fromStdString(get_all_processes().value_or("Failed")));
}

void MainWindow::update(proc::Storage& storage) {
    ui->textEdit->clear();
    for (auto process : storage.procceses) {
        ui->textEdit->append(QString::fromStdString(process.name+" | "+process.dir.d_name));
    }
}
