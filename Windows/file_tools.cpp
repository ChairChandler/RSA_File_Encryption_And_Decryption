#include <stdio.h>
#include <fstream>
#include <string>
#include <ctime>
#include "RSA.hpp"
#include "file_tools.hpp"

static char INFO_FILE_NAME[] = "info.txt";

bool copyFile(std::string &fileName, std::string &tmpName)
{
	std::ifstream tmp(tmpName.c_str(), std::ios::binary);
	std::ofstream file(fileName.c_str(), std::ios::trunc|std::ios::binary);
	
	file<<tmp.rdbuf();
	
	file.close();
	tmp.close();
	
	return !remove(tmpName.c_str());
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

void saveInformation(RSA &cipherFile, std::string &fileName)
{
	std::ofstream file;
	time_t now;
	
	now=time(0);
	
	file.open(INFO_FILE_NAME, std::ios::app);
	if(file.is_open() == false)
		std::cerr<<std::endl<<"[WARNING] Couldn't save RSA data into file: "<<INFO_FILE_NAME<<" ! "<<std::endl;
	
	file<<std::endl<<std::endl<<"Public ( "	<<cipherFile.Public.e	<<" , "		<<cipherFile.Public.n	<<" )";
	file<<std::endl<<"Private ( "		<<cipherFile.Private.d	<<" , "		<<cipherFile.Private.n	<<" )";
	file<<std::endl<<"Ciphered file: "	<<fileName				<<"\tDate: "<<ctime(&now);
	file.close();
}
