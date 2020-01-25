#include <unistd.h>
#include <dirent.h>
#include <sys/types.h> // for opendir(), readdir(), closedir()
#include <sys/stat.h> // for stat()

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}


int IsNumeric(const char* ccharptr_CharacterList) {
    for ( ; *ccharptr_CharacterList; ccharptr_CharacterList++)
        if (*ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9')
            return 0; // false
    return 1; // true
}

#define PROC_DIRECTORY "/proc/"

bool MainWindow::getAllTasks() {
    struct dirent * dirEntity = nullptr;
    DIR * dir_proc = nullptr ;

    dir_proc = opendir(PROC_DIRECTORY) ;
    if (dir_proc == nullptr) {
        perror("Couldn't open the " PROC_DIRECTORY " directory") ;
        return (pid_t) -2 ;
    }
    ui->textEdit->clear();
    QString temp;
    while ((dirEntity = readdir(dir_proc)) != 0) {
        if (dirEntity->d_type == DT_DIR) {
            if (IsNumeric(dirEntity->d_name)) {
                std::string path = std::string(PROC_DIRECTORY) + dirEntity->d_name + "/cmdline";

                std::ifstream cmdLineFile(path.c_str());
                std::string cmdLine;
                if (cmdLineFile) {

                    std::getline(cmdLineFile, cmdLine);

                }
                if (cmdLine.length() > 0) {
                    temp.clear();
                    temp += "pid: ";
                    temp += dirEntity->d_name;
                    temp += " ";
                    temp += cmdLine.c_str();
                    temp += '\n';
                    ui->textEdit->append(temp);
                }

            }
        }
    }
    closedir(dir_proc);
}
