#include "main.hpp"
using namespace std;

int main()
{	
	menu();
	return 0;
}

static void menu()
{
	char sign;
	bool repeat;
	
		do
		{
			cout<<"1.Encode file"		<<endl;
			cout<<"2.Decode file"		<<endl;
			cout<<"3.End the programme"	<<endl	<<endl	<<"    Answer: ___\b\b";
			
			repeat=true;
			
			cin>>sign;
			cin.ignore();
			sleep(1);
			
			
			system("cls");
			
			switch(sign)
			{
				case '1': { encrypt(); sleep(3);		} break;
				case '2': { decrypt(); sleep(3);		} break;
				case '3': { repeat=false; 				} break;
			}
			
			system("cls");
			
		}while(repeat == true);
		
}

static void encrypt()
{
	size_t length;
	cout	<<"RSA key length: ";
	cin		>>length;


	RSA cipherFile;
	cipherFile.generateKeys(length);
	cout	<<endl	<<"Public ( "	<<cipherFile.Public.e	<<" , "	<<cipherFile.Public.n	<<" ) ";
	cout	<<endl	<<"Private ( "	<<cipherFile.Private.d	<<" , "	<<cipherFile.Private.n	<<" )";
	cin.ignore();
	
	
	string fileName;
	cout	<<endl	<<endl	<<endl	<<"Enter the filename to be ciphered: ";
	getline(cin, fileName);
	
	
	if(encryptFile(cipherFile, fileName) == true)
		cout	<<endl	<<"File encrypted succesfully!";
	else
		cout	<<endl	<<"Couldn't encrypted file!";
	
	
	saveInformation(cipherFile, fileName);
}

static void decrypt()
{
	RSA cipherFile;
	
	
	cout	<<"\n\tpublic(e,n)\n\tprivate(d,n)";
	cout	<<endl	<<endl	<<"Enter e: ";
	cin		>>cipherFile.Public.e;
	cin.ignore();
	
	
	cout	<<endl	<<endl	<<"Enter n: ";
	cin		>>cipherFile.Public.n;
	cin.ignore();
	
	
	cout	<<endl	<<endl	<<"Enter d: ";
	cin		>>cipherFile.Private.d;
	cipherFile.Private.n	=	cipherFile.Public.n;
	cin.ignore();
	
	
	string fileName;
	cout	<<endl	<<endl	<<endl	<<"Enter the filename to be deciphered: ";
	getline(cin, fileName);
	
	
	if(decryptFile(cipherFile, fileName) == true)
		cout	<<endl	<<"File decrypted succesfully!";
	else
		cout	<<endl	<<"Couldn't decrypted file!";
}
