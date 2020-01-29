#ifndef DIMA_PROCESSES
#define DIMA_PROCESSES

#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <vector>
#include <utility>
#include <string.h>
#include <cstdint>

namespace proc {
    struct Process {
        uint32_t pid;
        std::string path;
        std::string name;
        std::string cmdline;
        std::string stdin;
        std::string stdout;
        std::string stderr;

        int loadFd() {
            dirent * dir = nullptr;
            DIR * dir_proc = nullptr;

            std::string fd = path + "/fd/";

            dir_proc = opendir( fd.c_str());
            if (dir_proc == nullptr) {
                perror( ("Couldn't open the " + fd + " directory").c_str());
                return -2;
            }
            while ((dir = readdir(dir_proc)) != nullptr) {
                if (dir->d_name[1] == 0) {
                    switch (dir->d_name[0]) {
                    case '0':
                        stdin = relativeReadLink(fd + dir->d_name);
                        continue;
                    case '1':
                        stdout = relativeReadLink(fd + dir->d_name);
                        continue;
                    case '2':
                        stderr = relativeReadLink(fd + dir->d_name);
                        continue;
                    default:
                        break;
                    }
                }
                //TODO:
                //folder fd keep sockets, pipes and something else
                //value from relativeReadLink need to interpret correctly
            }
            closedir(dir_proc);

            return 0;
        }
        void sedDir(dirent * dir) {
            this->dir.d_ino = dir->d_ino;
            this->dir.d_off = dir->d_off;
            strcpy(this->dir.d_name, dir->d_name);
            this->dir.d_type = dir->d_type;
            this->dir.d_reclen = dir->d_reclen;
        }

        Process() = delete;
        std::string relativeRead(std::string path) {
            std::ifstream pathFile(this->path + path);
            std::string out;
            pathFile >> out;
            return out;
        }
        std::string relativeReadLink(std::string path) {
            std::string final_path = this->path + path;

            struct stat sb;
            if (lstat(final_path.c_str(), &sb) == -1) return std::string("");

            ssize_t bufsize;
            if (sb.st_size == 0) bufsize = PATH_MAX;
            else bufsize = sb.st_size + 1;

            char buf[1024];
            ssize_t nbytes = readlink(final_path.c_str(), buf, bufsize);
            if (nbytes == -1) return std::string("");
            buf[nbytes] = 0;

            printf("'%s' points to '%.*s'\n", final_path.c_str(), (int) nbytes, buf);

            return std::string(buf);
        }
    };

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
    vector<Process> getProcList() {
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
                if ( (task.pid = (task.dir.d_name) ) != 0 ) {
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
#endif
