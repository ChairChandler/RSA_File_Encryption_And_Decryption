#include <ctime>
#include <string>
#include <fstream>
#include "BigDec.hpp"
#include "RSA.hpp"
#include "file_tools.hpp"
#include "encrypt_file.hpp"

typedef char*	Buffer;
typedef char 	Byte;

static std::string	TMP_FILE_NAME		=	"tmp.txt";
static const int	ENCODE_BUFF_SIZE	=	256;
static bool			FILE_END			=	false;
static Byte			SPACE_CHAR_LENGTH	=	1;

static Buffer	readFile(std::string &fileName);
static bool		writeFile(BigDec *numbers, size_t length, std::string &fileName);

bool encryptFile(RSA &key, std::string &fileName)
{
	BigDec *numbers;
	Buffer stream;
	std::string message;
	
	
	while(FILE_END == false)
	{
		stream=readFile(fileName);
		message=stream;
		delete[] stream;
		
		numbers=key.encrypt(message);
		if(writeFile(numbers,message.size(),TMP_FILE_NAME)==false)
		{
			delete[] numbers;
			return false;
		}
		delete[] numbers;
	}
	
	return copyFile(fileName, TMP_FILE_NAME);
}

static Buffer readFile(std::string &fileName)
{
	static size_t state=0;
	static size_t fSize=fileSize(fileName);
	static std::ifstream file(fileName, std::ios::binary);
	Buffer stream=new char[ENCODE_BUFF_SIZE+1];
	
	file.read(stream, ENCODE_BUFF_SIZE);
	state+=ENCODE_BUFF_SIZE;
	
	if(state >= fSize)
	{
		FILE_END=true;
		file.close();
		
		size_t length;
		length=state-fSize+1;
		stream[length]='\0';
	}
	
	stream[ENCODE_BUFF_SIZE]='\0';
	
	return stream;
}

static bool writeFile(BigDec *numbers, size_t length, std::string &fileName)
{
	static size_t state=0;
	static std::fstream file(fileName, std::ios::in|std::ios::out|std::ios::app|std::ios::binary);
	std::string stream;
	
	for(int i=0; i < length; i++)
	{
		stream=numbers[i];
		convertString(stream, false);
		
		file.write(stream.c_str(), stream.size());
		file.write(" ", SPACE_CHAR_LENGTH);
		state+=stream.size()+SPACE_CHAR_LENGTH;
		stream.clear();
	}
	
	if(FILE_END == true)
		file.close();
	
	return true;
}
