#ifndef ACRYL_UTIL_H
#define ACRYL_UTIL_H

#include <string>
#include <fstream>
#include <streambuf>

namespace Acryl {

extern void readFileToBuffer(const std::string& path, std::string& buffer);

}

#endif
