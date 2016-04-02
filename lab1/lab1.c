#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "string.h"
#include "proc.h"

int main() {
	setlocale(LC_ALL, "Russian");
	
	input(); 
	check();
	process();
	suntok(str, delim, ptr, i);
	output();
    return 0;
}
