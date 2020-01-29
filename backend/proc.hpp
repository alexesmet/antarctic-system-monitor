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
#include <string>

namespace proc {
    // В /proc/ лежат папки - все процессы, которые запущены, или были запущены
    constexpr char PROC_DIRECTORY[] = "/proc/";

    struct Process {
        uint32_t pid;
        std::string path;
        std::string name;
        std::string cmdline;
        std::string stdin;
        std::string stdout;
        std::string stderr;
    private:
        int loadFd();
        void sedDir(dirent* dir);
        std::string relativeRead(std::string path);
        std::string relativeReadLink(std::string path);
    };
}
#endif
