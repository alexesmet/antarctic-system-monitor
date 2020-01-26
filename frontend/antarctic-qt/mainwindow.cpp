#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "../../backend/antarcticore-linux/test.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, ui{new Ui::MainWindow} {
    ui->setupUi(this);
    ui->textEdit->append("Test");
    ui->textEdit->append(QString::fromStdString(get_all_processes().value_or("Failed")));
}

MainWindow::~MainWindow() {
    delete ui;
}
