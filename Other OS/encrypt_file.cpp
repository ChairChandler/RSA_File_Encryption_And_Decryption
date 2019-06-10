#include "encrypt_file.h"
#include <ctime>
#include <fstream>
#include <windows.h>
#include "BigDec.h"
#include "file_tools.h"

namespace FILE_encrypt_file_NS
{
    const std::string TMP_FILE_NAME = std::to_string(GetCurrentProcessId());

    static const int ENCODE_BUFF_SIZE = 256;
    static const Byte SPACE_CHAR_LENGTH = 1;
    static bool isFileEnded = false;

    static Buffer readFile(std::string &fileName);
    static bool writeFile(BigDec_NS::BigDec *numbers, size_t length, std::string &fileName);


    bool encryptFile(RSA_NS::RSA &key, std::string &fileName)
    {
        BigDec_NS::BigDec *numbers;
        std::string message;
        Buffer stream;

        isFileEnded=false;

        while(isFileEnded == false)
        {
            stream=readFile(fileName);

            message=stream;
            delete[] stream;

            numbers=key.encrypt(message);

            if(writeFile(numbers, message.size(), const_cast<std::string&>(TMP_FILE_NAME)) == false)
            {
                delete[] numbers;
                return false;
            }

            delete[] numbers;
        }

        return FILE_file_tools_NS::copyFile(fileName, const_cast<std::string&>(TMP_FILE_NAME));
    }

    static Buffer readFile(std::string &fileName)
    {
        static size_t state = 0;
        static long long fSize = FILE_file_tools_NS::fileSize(fileName);
        static std::ifstream file(fileName, std::ios::binary);

        Buffer stream=new char[ENCODE_BUFF_SIZE+1];


        file.read(stream, ENCODE_BUFF_SIZE);
        state += ENCODE_BUFF_SIZE;

        if(state >= fSize)
        {
            isFileEnded=true;
            file.close();


            long long length;
            length=ENCODE_BUFF_SIZE-(state-fSize);
            stream[length]='\0';
        }

        stream[ENCODE_BUFF_SIZE]='\0';

        return stream;
    }

    static bool writeFile(BigDec_NS::BigDec *numbers, size_t length, std::string &fileName)
    {
        static std::fstream file(fileName, std::ios::in|std::ios::out|std::ios::app|std::ios::binary);

        if(file.is_open() == false)
        {
            file.open(fileName, std::ios::in|std::ios::out|std::ios::app|std::ios::binary);
        }

        std::string stream;

        for(size_t i=0; i < length; i++)
        {
            stream=numbers[i];
            FILE_file_tools_NS::convertString(stream, false);


            file.write(stream.c_str(), static_cast<std::streamsize>(stream.size()));
            file.write(" ", SPACE_CHAR_LENGTH);


            stream.clear();
        }

        if(isFileEnded == true)
        {
            file.close();
        }

        return true;
    }
}
