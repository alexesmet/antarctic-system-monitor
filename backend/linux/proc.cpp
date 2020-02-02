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
        std::string temp;
        dir_proc = opendir( fd.c_str());
        if (dir_proc == nullptr) {
            std::cerr << "Couldn't open the " + fd + " directory" << std::endl;
            return -2;
        }

        fd = "/fd/";

        const std::string socket = "socket";
        const std::string anon_inode = "anon_inode";
        const std::string pipe = "pipe";

        sockets.clear();
        pipes.clear();
        other.clear();
        inodes.clear();

        while ((dir = readdir(dir_proc)) != nullptr) {
            if (dir->d_type == DT_LNK) {

                temp = relativeReadLink(fd + dir->d_name);
                std::cout << temp << std::endl;
                if      (strcmp(dir->d_name, "0") == 0) stdin  = temp;
                else if (strcmp(dir->d_name, "1") == 0) stdout = temp;
                else if (strcmp(dir->d_name, "2") == 0) stderr = temp;

                if      (temp.find(socket)     == 0) //нужен нормальный toNum
                    sockets.push_back(utils::toNum(utils::getFdValue(temp, socket).c_str()));
                else if (temp.find(anon_inode) == 0)
                    inodes. push_back(             utils::getFdValue(temp, anon_inode));
                else if (temp.find(pipe)       == 0) //нужен нормальный toNum
                    pipes.  push_back(utils::toNum(utils::getFdValue(temp, pipe).c_str()));
                else {
                    other.  push_back(temp);
                    std::cout << "other = " << temp << std::endl;
                }
            }
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
        if (lstat(final_path.c_str(), &sb) == -1) {
            std::cerr << "lstat for " << final_path << " is -1" << std::endl;
            return {};
        }

        ssize_t bufsize;
        if (sb.st_size == 0) bufsize = PATH_MAX;
        else bufsize = sb.st_size + 1;

        char buf[1024];
        ssize_t nbytes = readlink(final_path.c_str(), buf, bufsize);
        if (nbytes == -1){
            std::cerr << "nbytes for " << final_path << " is -1" << std::endl;
            return {};
        }
        buf[nbytes] = 0;

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
                //auto pid = static_cast<uint32_t>(strtol(dir->d_name, nullptr, 10));
                //if (errno != ERANGE) {
                //Закоменчено, потому что проверку errno != ERANGE проходят
                //абсолютно все папки из /proc/
                int pid = utils::toNum(dir->d_name);
                if (pid != 0) {
                    task.pid = pid;
                    task.path = std::string(PROC_DIRECTORY) + dir->d_name;
                    task.cmdline = task.relativeRead("/cmdline");
                    task.name = task.relativeReadLink("/exe");
                    out.push_back(task);
                    //errno = 0;
                }
            }
        }
        closedir(dir_proc);
        return out;
    }
}
