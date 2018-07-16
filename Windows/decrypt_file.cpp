#include <string>
#include <fstream>
#include "BigDec.hpp"
#include "RSA.hpp"
#include "file_tools.hpp"
#include "decrypt_file.hpp"

static const int	DECODE_BUFF_SIZE	=	512;
extern std::string	TMP_FILE_NAME;
extern bool			FILE_END;

static BigDec* readFile(std::string &fileName, size_t &retLength);
static bool writeFile(std::string &text, std::string &fileName);

bool decryptFile(RSA &key, std::string &fileName)
{
	std::string message;
	size_t returnLength;
	BigDec *numbers;
	
	while(FILE_END == false)
	{
		numbers=readFile(fileName, returnLength);
		message=key.decrypt(numbers, returnLength);
		delete[] numbers;
		
		if(writeFile(message, TMP_FILE_NAME) == false)
			return false;
	}
	
	return copyFile(fileName, TMP_FILE_NAME);
}

static BigDec* readFile(std::string &fileName, size_t &returnLength)
{
	static size_t state=0;
	static size_t fSize=fileSize(fileName);
	static std::ifstream file(fileName, std::ios::binary);
	
	int i=0;
	char readedChar;
	bool readingNumbers=true;
	std::string auxString;
	BigDec *numbers;
	
	numbers=new BigDec[DECODE_BUFF_SIZE];

	while(state < fSize)
	{
		file.read((char*)&readedChar,1);
		state++;
		
			if(state >= fSize)
			{	
				convertString(auxString, true);
				
				BigDec tmp(auxString);
				numbers[i]=tmp;
				
				returnLength=i+1;
				FILE_END=true;
				file.close();
				
				break;
			}
			else if(readedChar == ' ')
			{
				if(readingNumbers == true)
					readingNumbers=false;
				
				convertString(auxString, true);
				
				BigDec tmp(auxString);
				numbers[i]=tmp;
				
				if(i+1 == DECODE_BUFF_SIZE)
				{
					returnLength=DECODE_BUFF_SIZE;
					break;
				}
				continue;
				
			}
			else if(readingNumbers == false)
			{
				readingNumbers=true;
				auxString.clear();
				i++;
			}
		
		auxString+=readedChar;
		
	}
	
	return numbers;
}

static bool writeFile(std::string &text, std::string &fileName)
{
	static size_t state=0;
	static std::fstream file(fileName, std::ios::out|std::ios::in|std::ios::app|std::ios::binary);
	
	file.write(text.c_str(), text.size());
	
	if(FILE_END == true)
		file.close();
	
	return true;
}
