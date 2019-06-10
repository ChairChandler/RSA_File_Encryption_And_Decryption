#ifndef DECRYPT_FILE
#define DECRYPT_FILE
#include <string>
#include "RSA.h"

namespace FILE_decrypt_file_NS
{
    bool decryptFile(RSA_NS::RSA &key, std::string &fileName);
}

#endif
