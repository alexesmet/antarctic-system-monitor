#pragma once

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


namespace proc {

    struct procces {
        dirent dir;
        std::string path;
        std::string name;
        std::string cmdlime;
        int pid = 0;
        /*
        dirent is:
            __ino_t d_ino;
            __off_t d_off;
            unsigned short int d_reclen;
            unsigned char d_type;
            char d_name[256];
        */
        void sedDir(dirent * dir) {
            this->dir.d_ino = dir->d_ino;
            this->dir.d_off = dir->d_off;
            strcpy(this->dir.d_name, dir->d_name);
            this->dir.d_type = dir->d_type;
            this->dir.d_reclen = dir->d_reclen;
        }
        procces(const procces & proc) {
            dir = proc.dir;
            path = proc.path;
            name = proc.name;
            pid = proc.pid;
            cmdlime = proc.cmdlime;
        }
        procces() {}
        std::string relativeRead(std::string path) {
            std::ifstream pathFile(this->path + path);
            std::string out;
            if (pathFile) {
                std::getline(pathFile, out);
            }
            return out;
        }
    };

    static
    struct Storage {
        std::vector<procces> procceses;
    }
    storage;

}
