#include "../proc.hpp"

#include <cstdlib>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

using std::vector;
using std::string;
using std::strtol;

namespace proc {
    int Process::loadFd() {
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

    /*void Process::sedDir(dirent * dir) {
        this->dir.d_ino = dir->d_ino;
        this->dir.d_off = dir->d_off;
        strcpy(this->dir.d_name, dir->d_name);
        this->dir.d_type = dir->d_type;
        this->dir.d_reclen = dir->d_reclen;
    }*/

    std::string Process::relativeRead(std::string path) {
        std::ifstream pathFile{this->path + path};
        std::string out;
        pathFile >> out;
        return out;
    }

    std::string Process::relativeReadLink(std::string path) {
        std::string final_path = this->path + path;

        struct stat sb;
        if (lstat(final_path.c_str(), &sb) == -1) return {};

        ssize_t bufsize;
        if (sb.st_size == 0) bufsize = PATH_MAX;
        else bufsize = sb.st_size + 1;

        char buf[1024];
        ssize_t nbytes = readlink(final_path.c_str(), buf, bufsize);
        if (nbytes == -1) return {};
        buf[nbytes] = 0;

        printf("'%s' points to '%.*s'\n", final_path.c_str(), (int) nbytes, buf);

        return std::string{buf};
    }
    /*
    Суть:
       В папке /proc/ лежат папки процессов
       Поэтому считываем все папки из /proc/
       Проверяем их на имя типа "10203"
       Получаем файл cmdline из папки
       Чекаем на то, чтобы cmdline был

       После выполнения улсловий, процесс
    */
    std::vector<Process> getAllProccess() {
        dirent * dir = nullptr;
        Process task;
        DIR * dir_proc = nullptr;

        std::vector<Process> out;

        dir_proc = opendir(PROC_DIRECTORY);
        if (dir_proc == nullptr) {
            std::cerr << "Couldn't open the " << PROC_DIRECTORY << " directory";
            return out;
        }
        while ((dir = readdir(dir_proc)) != nullptr) {
            if (dir->d_type == DT_DIR) {
                auto pid = static_cast<uint32_t>(strtol(dir->d_name, nullptr, 10));
                if (errno != ERANGE) {
                    task.pid = pid;
                    task.path = std::string(PROC_DIRECTORY) + dir->d_name;
                    task.cmdline = task.relativeRead("/cmdline");
                    task.name = task.relativeReadLink("/exe");
                    std::cout << "\npid: "  << task.pid
                              << "\nname: "    << task.name
                              << "\npath: "    << task.path
                              << "\ncmdline: " << task.cmdline << '\n';
                    out.push_back(task);
                    errno = 0;
                }
            }
        }
        closedir(dir_proc);
        return out;
    }
}
