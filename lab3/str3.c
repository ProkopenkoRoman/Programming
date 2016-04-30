#include <stdio.h>
#include <stdlib.h>
#include "string.h"
//#include "proc.h"
#include "analiz.h"

int main()
{
	//char str[261] ;
	//char *ptr[20];
	
	char s[1024] = {0};
	open_file(s);
	printf("str = %s\n", s);
	analiz(s);
	//input(str);
	//check(str);
	//process(str, ptr);
	
	return 0;
}
