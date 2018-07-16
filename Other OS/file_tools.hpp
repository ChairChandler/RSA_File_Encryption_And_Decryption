#ifndef FILE_TOOLS_HPP
#define FILE_TOOLS_HPP
#include <string>
#include "RSA.hpp"

static char	offset	=	15;

long long 	fileSize(std::string &fileName);
bool 		copyFile(std::string &fileName, std::string &tmpName);
void 		saveInformation(RSA &cipherFile, std::string &fileName);

inline void convertString(std::string &text, bool toAscii)
{
	if(toAscii == true)
	{
		for(int j=0; j < text.size(); j++)
			text[j]=text[j]+offset;
	}
	else
	{
		for(int j=0; j < text.size(); j++)
			text[j]=text[j]-offset;
	}
}

#endif
