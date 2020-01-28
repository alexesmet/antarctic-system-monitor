#pragma once

#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <vector>
#include <utility>

#include "processes.h"

namespace allPids {

    pid_t toNum(const char * name) {
        pid_t pid = 0;
        while (*name != 0) {
            if (*name < '0' || *name > '9') return 0;
            else pid = pid * 10 + *name - 48;
            name++;
        }
        return pid;
    }

    //В /proc/ лежат папки - все процессы, которые запущены, или были запущены
    #define PROC_DIRECTORY "/proc/"

    /*
    Суть:
       В папке /proc/ лежат папки процессов
       Поэтому считываем все папки из /proc/
       Проверяем их на имя типа "10203"
       Получаем файл cmdline из папки
       Чекаем на то, чтобы cmdline был

       После выполнения улсловий, процесс
    */
    int get(proc::Storage & storage) {
        dirent * dir = nullptr;
        proc::Process task;
        DIR * dir_proc = nullptr;

        dir_proc = opendir(PROC_DIRECTORY);
        if (dir_proc == nullptr) {
            perror("Couldn't open the " PROC_DIRECTORY " directory") ;
            return (pid_t) -2 ;
        }
        while ((dir = readdir(dir_proc)) != nullptr) {
            task.sedDir(dir);
            if (task.dir.d_type == DT_DIR) {
                if ( (task.pid = toNum(task.dir.d_name) ) != 0 ) {
                    task.path = std::string(PROC_DIRECTORY) + task.dir.d_name;
                    task.cmdlime = task.relativeRead("/cmdline");
                    //if (task.cmdlime.length() > 0) {
                        //task.name = task.relativeRead("/comm");
                        task.name = task.relativeReadLink("/exe");
                        std::cout << "\nd_name: "  << task.dir.d_name
                                  << "\npid: "     << task.pid
                                  << "\nname: "    << task.name
                                  << "\npath: "    << task.path
                                  << "\ncmdline: " << task.cmdlime << '\n';
                        storage.procceses.push_back(task);
                    //}
                }
            }
        }
        closedir(dir_proc);
        return 0;
    }

    #undef PROC_DIRECTORY
}
