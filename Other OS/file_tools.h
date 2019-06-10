#ifndef FILE_TOOLS_HPP
#define FILE_TOOLS_HPP
#include <string>
#include "RSA.h"

namespace FILE_file_tools_NS
{
    long long fileSize(std::string &fileName);
    bool copyFile(std::string &fileName, std::string &tmpName);
    void saveInformation(RSA_NS::RSA &cipherFile);
    void convertString(std::string &text, bool toAscii);
}

#endif
