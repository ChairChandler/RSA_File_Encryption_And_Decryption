#ifndef DECRYPT_FILE
#define DECRYPT_FILE

#include <string>
#include "RSA.hpp"

bool decryptFile(RSA &key, std::string &fileName);

#endif
