#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "../../backend/proc.hpp"
#include "ui_mainwindow.h"
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
        //~MainWindow();
        void update(const std::vector<proc::Process> & proc_list);
    private:
        std::unique_ptr<Ui::MainWindow> ui {new Ui::MainWindow};
};
#endif //MAINWINDOW_HPP
