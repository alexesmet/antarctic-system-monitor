#include "mainwindow.hpp"

#include <vector>

using std::vector;
using std::to_string;
using proc::Process;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    ui->setupUi(this);
}

void MainWindow::update(const vector<Process>& proc_list) {
    ui->textEdit->clear();
    for (const auto& proc: proc_list) {
        ui->textEdit->append(QString::fromStdString(to_string(proc.pid) + " | " + proc.name));
    }
}
