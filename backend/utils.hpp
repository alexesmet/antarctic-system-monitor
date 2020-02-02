#include <string>
#include <iostream>
#include <string.h>

namespace utils {
    int toNum(const char * name);
    std::string getFdValue(const std::string & fd, const std::string & check);
    //str::string::substr иногда просает exception по непонятной мне причине
    //Поэтому сделал свой substr, нужно будет потом сделать через нормальный substr
    char * copyRange(char * out, const char * in, size_t from = 0, long long to = -1);
}
