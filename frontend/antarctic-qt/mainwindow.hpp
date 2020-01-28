#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "../../backend/antarcticore-linux/allpids.h"
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT
    public:
        MainWindow(QWidget* parent = nullptr);
        void update(proc::Storage & storage) {
            ui->textEdit->clear();
            for (auto process : storage.procceses) {
                ui->textEdit->append(QString::fromStdString(process.name+" | "+process.dir.d_name));
            }

        };
    private:
        std::unique_ptr<Ui::MainWindow> ui;
};
#endif //MAINWINDOW_HPP
