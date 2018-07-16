#ifndef ENCRYPT_FILE_HPP
#define ENCRYPT_FILE_HPP

#include <string>
#include "RSA.hpp"

bool encryptFile(RSA &key, std::string &fileName);

#endif
