#include <unistd.h>
#include <dirent.h>
#include <sys/types.h> // for opendir(), readdir(), closedir()
#include <sys/stat.h> // for stat()
#include <iostream>
#include <cstring>
#include <fstream>
#include <optional>
#include <algorithm>

using std::optional;
using std::string;
using std::ifstream;

static inline bool is_number(const char* c) {
    for (; *c; ++c) {
        if (!std::isdigit(*c)) {
            return false;
        }
    }
    return true;
}

constexpr auto PROC_DIRECTORY = "/proc/";

optional<string> get_all_processes() {
    struct dirent * dirEntity = nullptr;
    DIR* dir_proc = nullptr;

    dir_proc = opendir(PROC_DIRECTORY) ;
    if (!dir_proc) {
        std::cerr << "Couldn't open the "<< PROC_DIRECTORY << "directory: " << std::strerror(errno);
        return {};
    }

    string temp_str;
    while ((dirEntity = readdir(dir_proc))) {
        if (dirEntity->d_type == DT_DIR) {
            if (is_number(dirEntity->d_name)) {
                string path = std::string(PROC_DIRECTORY) + dirEntity->d_name + "/cmdline";
                std::cout << path;
                ifstream cmdLineFile{path};
                string cmdLine;
                if (cmdLineFile) {
                    std::getline(cmdLineFile, cmdLine);
                }
                if (cmdLine.length() > 0) {
                    temp_str += "pid: ";
                    temp_str += dirEntity->d_name;
                    temp_str += " ";
                    temp_str += cmdLine.c_str();
                    temp_str += '\n';
                }
            }
        }
    }
    closedir(dir_proc);
    return temp_str;
}
