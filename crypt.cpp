#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <windows.h>


typedef unsigned int	uint;
typedef unsigned char	uchar;

using namespace std;
void showHelp()
{
	setlocale(LC_ALL, "Russian");
	cout << "$ crypt [options] <key> <source> [<dest>]\n\n";
	cout << "options:\n";
	cout << "\t-a, --alphabet=<alphabet>  alphabet — alphabet for the algorithm (the default\n";
	cout << "\t                                      contains the letters of the Latin alphabet and numbers: AaBbCc..Zz0..9)\n"; 
	cout << "\t-t, --type=<type>                     type maybe 'encode' or 'decode', the default — encode\n";
	cout << "\t-h, --help                            prints this help\n\n";
	cout << "key:\n";
	cout << "\tkey for encryption / decryption\n\n";
	cout << "source:\n";
	cout << "\tsource file to encrypt / decrypt\n\n";
	cout << "dest:\n";
	cout << "\tthe file will be written a new, encrypted text. If not specified, it overwrites source\n\n";
}
	
string getAlphabet(string strAlp)
{
	strAlp.erase(0,11);
	strAlp.erase(strAlp.length());
	return strAlp;
}

int main(int argc, char* argv[])
{
	int key, keyIndex, index, code;
	char symbol, codsymbol;
	string alphabet="AaBbCcDdEeFfGgHhIiKkLlMmNnOoPpQqRrSsTtVvXxYyZz0123456789";
	string tmp;
	FILE * source;
	FILE * dest;

	if(argc == 2)
		if((!(strcmp(argv[1],"-h"))) or (!(strcmp(argv[1],"--help"))))
		{
			showHelp();
			return 0;
		}
		else
		{
			cout << "Error!" << endl;
			return -1;
		}
	if(argc > 2)
	{
		for(int i=1; i<argc; i++)
		{
			if((!(strcmp(argv[i],"-a"))))
			{
				i++;
				alphabet = argv[i];
			}
			else 
			if(strstr(argv[i],"-alphabet="))
			{	
				alphabet = getAlphabet(argv[i]);
			}
			else
			if(strstr(argv[i],"-t"))
			{
				if(strstr(argv[i],"--type="))
				{	
					tmp = string(argv[i]).erase(0,7);
				}
				else
				{
					i++; 
					tmp = string(argv[i]);
				}
				if(!(tmp == "encode" or tmp =="decode"))
				{
					cout << "Invalid argument" <<endl;
					return -1;
				}
			}
			else if(key = atoi(argv[i]))
			{
				if (key < 1)
				{
					cout << "Arguments are wrong " << endl;
					return -1;				  
				}
				keyIndex = i;
				break;
			}
			else
			{
				cout << "Arguments are wrong " << endl;
				return -1;
			}
		}
	}	
	if (keyIndex == (argc-2))//Если ключ - предпоследний аргумент
	{
		if (!(source = fopen(argv[keyIndex+1],"r+")))
		{
			printf("%s\n", "Bad file. Does it exist?");
			return -1;
		}

		dest = fopen("output.txt","w");
	}
	else if (keyIndex == (argc-3))//Если ключ - предпредпоследний аргумент
	{
		if (!(source = fopen(argv[keyIndex+1],"r")))
		{
			printf("%s\n", "Bad file. Does it exist?");
			return -1;
		}
		if (!(dest = fopen(argv[keyIndex+2],"w")))
		{
			printf("%s\n", "Bad file. Does it exist?");
			return -1;
		}
	}
	else
	{
		cout << "Parameters are set incorrectly!" << endl;
	}
	// если расшифровка, то меняем ключ на противоположный
	if(tmp=="decode") key *= -1;
	while((symbol=fgetc(source)) != EOF)
	{
			if((index = alphabet.find(symbol)) +1)//еcть ли символ  в алфавите
		{
	 code = symbol; //получаем код симввола из таблицы ascii
	 if (code==32) // если встретился пробел не шифруем его
	 {
		fputc(symbol,dest);
	 }
		else
		{
		if((code >=48)and(code <=57))// если встречаються цифры
		{
		code=code-48;
		codsymbol=(char)((code+key) % 10 +48);
		fputc(codsymbol,dest);
		}
		else
		if((code >=65)and(code <=90))// если заглавные буквы
		{
		code=code-65;
		codsymbol=(char)((code+key) % 26 + 65);
		fputc(codsymbol,dest);
		}
		else 
		if((code >=97)and(code <=122))// строчные буквы
		{
		code=code-97;
		codsymbol=(char)((code+key) % 26 +97);
		fputc(codsymbol,dest);
		}
		}
	}
	else
	{
	fputc(symbol,dest);
	}
	}
	fclose(source);
	fclose(dest);
	return 0;
}