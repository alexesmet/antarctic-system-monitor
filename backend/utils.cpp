#include "utils.hpp"
int utils::toNum(const char * name) {
    int pid = 0;
    while (*name != 0) {
        if (*name < '0' || *name > '9') return 0;
        else pid = pid * 10 + *name - 48;
        name++;
    }
    return pid;
} 

using namespace std;

char * utils::copyRange(char * out, const char * in, size_t from, long long to) {
    if (to == -1) {
        return strcpy(out, in + from);
    }
    else {
        strncpy(out, in + from, to - from + 1);
        out[to - from + 1] = 0;
        return out;
    }
}

string utils::getFdValue(const string & fd, const string & check) {
    if (fd.find(check) == 0) {
        if (strchr(fd.c_str(), '[') != nullptr) {
            int pos_left =  fd.find('[') + 1;
            int pos_right = fd.find(']') - 1;
            char buf[32];
            string out = copyRange(buf, fd.c_str(), pos_left, pos_right);
            std::cout << check << " = " << out << std::endl;
            return out;
        }
        else {
            int pos_left = fd.find(':') + 1;
            char buf[32];
            string out = copyRange(buf, fd.c_str(), pos_left);
            std::cout << check << " = " << out << std::endl;
            return out;
        }
    }
    else {
        std::cerr << check << " error " << std::endl;
        std::cerr << fd << ".find(" << check << ") != 0" <<std::endl;
        return {};
    }
}
