#ifndef DIMA_PROCESSES
#define DIMA_PROCESSES

#include <dirent.h>
#include <string.h>
#include <cstdint>
#include <string>
#include <vector>
#include <sys/times.h>
#include <sys/resource.h>

#include "utils.hpp"

namespace proc {
    // В /proc/ лежат папки - все процессы, которые запущены, или были запущены
    constexpr char PROC_DIRECTORY[] = "/proc/";

    struct Process {
        //dirent dir;
        uint32_t pid;
        std::string path;
        std::string name;
        std::string cmdline;

        tms    cpu_time;
        rusage res_usage;
        /*
        struct rusage {
            struct timeval ru_utime; // user CPU time used
            struct timeval ru_stime; // system CPU time used
            long   ru_maxrss;        // maximum resident set size
            long   ru_ixrss;         // integral shared memory size
            long   ru_idrss;         // integral unshared data size
            long   ru_isrss;         // integral unshared stack size
            long   ru_minflt;        // page reclaims (soft page faults)
            long   ru_majflt;        // page faults (hard page faults)
            long   ru_nswap;         // swaps
            long   ru_inblock;       // block input operations
            long   ru_oublock;       // block output operations
            long   ru_msgsnd;        // IPC messages sent
            long   ru_msgrcv;        // IPC messages received
            long   ru_nsignals;      // signals received
            long   ru_nvcsw;         // voluntary context switches
            long   ru_nivcsw;        // involuntary context switches
        };
        */


        std::string stdin;
        std::string stdout;
        std::string stderr;

        std::vector<size_t> sockets;
        std::vector<size_t> pipes;
        std::vector<std::string> other;
        std::vector<std::string> inodes;


        int loadFd();
        void sedDir(dirent* dir);
        std::string relativeRead(std::string path);
        std::string relativeReadLink(std::string path);
    };
    std::vector<Process> getAllProccess();
}
#endif
