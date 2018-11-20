#include "util.h"

namespace Acryl {

extern void readFileToBuffer(const std::string& path, std::string& buffer){
    std::ifstream f(path);
    buffer.insert(buffer.begin(), (std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

}