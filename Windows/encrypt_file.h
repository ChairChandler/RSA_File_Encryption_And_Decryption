#ifndef ENCRYPT_FILE_HPP
#define ENCRYPT_FILE_HPP
#include <string>
#include "RSA.h"

namespace FILE_encrypt_file_NS
{
    typedef char* Buffer;
    typedef char Byte;

    bool encryptFile(RSA_NS::RSA &key, std::string &fileName);

    extern const std::string TMP_FILE_NAME;
}

#endif
