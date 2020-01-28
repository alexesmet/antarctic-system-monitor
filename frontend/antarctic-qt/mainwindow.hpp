#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "../../backend/antarcticore-linux/processes.h"
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
        void update(proc::Storage& storage);
    private:
        std::unique_ptr<Ui::MainWindow> ui;
};
#endif //MAINWINDOW_HPP
