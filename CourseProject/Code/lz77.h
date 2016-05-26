#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

//структура кода
struct Code {
	int num;	//индекс в словаре
	int len;	//длина найденной подстроки
	char c;		//символ стоящий за подстрокой из буфера
};

// прототипы вызываемых ф-ций кодирования/декодирования
void Encode(FILE* , FILE* , int , int);
void Decode(FILE* , FILE*);
