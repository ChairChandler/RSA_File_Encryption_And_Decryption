#include "decrypt_file.h"
#include <fstream>
#include "BigDec.h"
#include "file_tools.h"
#include "encrypt_file.h"

namespace FILE_decrypt_file_NS
{
    static const int DECODE_BUFF_SIZE = 256;

    static bool isFileEnded = false;

    static BigDec_NS::BigDec* readFile(std::string &fileName, size_t &retLength);
    static bool writeFile(std::string &text, std::string &fileName);


    bool decryptFile(RSA_NS::RSA &key, std::string &fileName)
    {
        std::string message;
        size_t returnLength;
        BigDec_NS::BigDec *numbers;

        isFileEnded=false;

        while(isFileEnded == false)
        {
            numbers=readFile(fileName, returnLength);
            message=key.decrypt(numbers, returnLength);


            delete[] numbers;


            if(writeFile(message, const_cast<std::string&>(FILE_encrypt_file_NS::TMP_FILE_NAME)) == false)
            {
                return false;
            }
        }

        return FILE_file_tools_NS::copyFile(fileName, const_cast<std::string&>(FILE_encrypt_file_NS::TMP_FILE_NAME));
    }

    static BigDec_NS::BigDec* readFile(std::string &fileName, size_t &returnLength)
    {
        static size_t state = 0;
        static long long fSize = FILE_file_tools_NS::fileSize(fileName);
        static std::ifstream file(fileName, std::ios::binary);

        if(file.is_open() == false)
        {
            file.open(fileName, std::ios::binary);
            state = 0;
        }

        BigDec_NS::BigDec *numbers;
        std::string auxString;
        size_t counter = 0;
        char readedChar;


        numbers=new BigDec_NS::BigDec[DECODE_BUFF_SIZE];


        while(state < fSize)
        {
            file.read(static_cast<char*>(&readedChar), 1);
            state++;


            if(state >= fSize)
            {
                FILE_file_tools_NS::convertString(auxString, true);

                numbers[counter]=BigDec_NS::BigDec(auxString);

                returnLength=counter+1;
                isFileEnded=true;
                file.close();

                break;
            }
            else if(readedChar == ' ')
            {
                FILE_file_tools_NS::convertString(auxString, true);

                numbers[counter]=BigDec_NS::BigDec(auxString);
                auxString.clear();


                if((counter+1) == DECODE_BUFF_SIZE)
                {
                    returnLength=DECODE_BUFF_SIZE;
                    break;
                }
                else
                {
                    counter++;
                }
            }
            else
            {
                auxString += readedChar;
            }
        }

        return numbers;
    }

    static bool writeFile(std::string &text, std::string &fileName)
    {
        static std::fstream file(fileName, std::ios::out|std::ios::in|std::ios::app|std::ios::binary);

        if(file.is_open() == false)
        {
            file.open(fileName, std::ios::out|std::ios::in|std::ios::app|std::ios::binary);
        }

        file.write(text.c_str(), static_cast<std::streamsize>(text.size()));

        if(isFileEnded == true)
        {
            file.close();
        }

        return true;
    }
}
