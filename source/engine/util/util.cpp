#include "util.h"

namespace Acryl {

/**
 * @brief Reads a file completely and puts its context in a supplied buffer
 * @param buffer Buffer for the file-contents
 */
extern void readFileToBuffer(const std::string& path, std::string& buffer){
    std::ifstream f(path);
    buffer.insert(buffer.begin(), (std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

}