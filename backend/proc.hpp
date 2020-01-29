#ifndef DIMA_PROCESSES
#define DIMA_PROCESSES

#include <dirent.h>
#include <string.h>
#include <cstdint>
#include <string>
#include <vector>
//#include "utils.hpp"

namespace proc {
    // В /proc/ лежат папки - все процессы, которые запущены, или были запущены
    constexpr char PROC_DIRECTORY[] = "/proc/";

    struct Process {
        //dirent dir;
        uint32_t pid;
        std::string path;
        std::string name;
        std::string cmdline;
        std::string stdin;
        std::string stdout;
        std::string stderr;

        int loadFd();
        void sedDir(dirent* dir);
        std::string relativeRead(std::string path);
        std::string relativeReadLink(std::string path);
    };
    std::vector<Process> getAllProccess();
}
#endif
