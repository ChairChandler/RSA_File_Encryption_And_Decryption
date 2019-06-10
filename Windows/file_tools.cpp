#include "file_tools.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

namespace FILE_file_tools_NS
{

    static const int offset = 15;
    static const std::string INFO_FILE_NAME = "info.txt";


    bool copyFile(std::string &fileName, std::string &tmpName)
    {
        std::ifstream tmp(tmpName.c_str(), std::ios::binary);
        std::ofstream file(fileName.c_str(), std::ios::trunc|std::ios::binary);

        if(tmp.is_open() == false || file.is_open() == false)
        {
            return false;
        }
        else
        {
            file<<tmp.rdbuf();

            file.close();
            tmp.close();

            return !remove(tmpName.c_str());
        }
    }

    long long fileSize(std::string &fileName)
    {
        long long fSize;
        std::fstream file;

        file.open(fileName, std::ios::in|std::ios::out|std::ios::binary);

        fSize=file.tellg();
        file.seekg(0, std::ios::end);
        fSize=file.tellg()-fSize;

        file.close();

        return fSize;
    }

    void saveInformation(RSA_NS::RSA &cipherFile)
    {
        std::ofstream file;
        time_t now;

        now=time(NULL);

        file.open(INFO_FILE_NAME, std::ios::app);


        if(file.is_open() == false)
        {
            std::cerr<<std::endl<<"[WARNING] Couldn't save RSA data into file: "<<INFO_FILE_NAME<<" ! "<<std::endl;
        }



        RSA_NS::RSA::PublicKey pubKey;
        RSA_NS::RSA::PrivateKey privKey;

        pubKey=cipherFile.getPublicKey();
        privKey=cipherFile.getPrivateKey();



        file<<std::endl<<std::endl<<"Public ( "<<pubKey.e<<" , "<<pubKey.n<<" )";
        file<<std::endl<<"Private ( "<<privKey.d<<" , "<<privKey.n<<" )";
        file<<std::endl<<"\tDate: "<<ctime(&now);


        file.close();
    }

    void convertString(std::string &text, bool toAscii)
    {
        if(toAscii == true)
        {
            for(size_t j=0; j < text.size(); j++)
            {
                text[j]=text[j]+offset;
            }
        }
        else
        {
            for(size_t j=0; j < text.size(); j++)
            {
                text[j]=text[j]-offset;
            }
        }
    }
}
