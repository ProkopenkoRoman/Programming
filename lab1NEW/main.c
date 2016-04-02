#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "string.h"
#include "proc.h"

int main() {
	setlocale(LC_ALL, "Russian");
	
	input(str); 
	check(str);
	process(str);
	output(str);
	
    return 0;
}
