#include "mainwindow.hpp"

#include <vector>

using std::vector;
using std::to_string;
using proc::Process;

static auto header_list = QStringList({"PID" ,"name"});

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    ui->setupUi(this);

    ui->table_widget->setColumnCount(header_list.size());
    ui->table_widget->setHorizontalHeaderLabels(header_list);
    ui->table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_widget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_widget->horizontalHeader()->setStretchLastSection(true);
    ui->table_widget->setColumnWidth(0, 70);
    ui->table_widget->verticalHeader()->setVisible(false);

    connect(ui->update_button, &QPushButton::clicked, [this]() {
        ui->update_button->setDisabled(true);
        ui->statusbar->showMessage("Updating is not yet implemented.");
    });
}

void MainWindow::update(const vector<Process>& proc_list) {

    ui->table_widget->setRowCount(proc_list.size());

    for(size_t i=0; i < proc_list.size(); i++) {
        auto cell_pid  = new QTableWidgetItem(QString::fromStdString(to_string(proc_list[i].pid)));
        auto cell_name = new QTableWidgetItem(QString::fromStdString(proc_list[i].name));

        cell_pid->setTextAlignment(2);

        ui->table_widget->setItem(i, 0, cell_pid);
        ui->table_widget->setItem(i, 1, cell_name);
    }
    ui->table_widget->resizeColumnToContents(header_list.size()-1);
    ui->table_widget->resizeRowsToContents();

    ui->statusbar->showMessage("Table was updated.");
}
