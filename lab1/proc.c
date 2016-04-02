#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "proc.h"

void input() {
	int i;
	char ch[500];
	
	printf("Введите строку, соответствующую абсолютному пути:\n"); // vvedite stroku, sootvetstvuyushuyu absolutnomu puti	
		scanf("%s", &ch);
	if(slen(ch) > 261) {
	 	printf("Превышение допустимой длины пути...");
	 	exit(1);
	}
	else {
		for (i = 0; i < slen(ch); i++)
         	str[i] = ch[i]; 
		printf("Входная строка: %s\n\n", str); // vhodnaya stroka
	} 
}

void check() {
	sspn(str); // proverka na nedopustimie simvoli
	printf("\n");
}

void process() {
	////////////////////////////////////// OPREDELENIE OS //////////////////////////////////////
	first_ch = str[0];
	if (first_ch == '/') {
		printf("OS: Linux\n");
		delim = '/';
		f=1;
	}
	if (isLowCase(first_ch) == 1 || isHighCase(first_ch) == 1) {
		printf("OS: Windows\n");
		delim = '\\';
		f=1;
	}
	if (f == 0) {
		printf("Ошибочный путь...\n"); // oshibo4niy put'
		exit(1);
	}
	
	printf("Разделитель: %c\n", delim); // razdelitel'
      	
	i = stok(str, delim, ptr);
	printf("Количество каталогов: %d\n", i - 2); // koli4estvo katalogov s u4etom kone4nogo fayla
	
	printf("Конечный файл: %s\n", ptr[i-1]); // kone4niy fayl
	
	s = slen(ptr[i-1]);
	printf("Длина конечного файла: %d\n\n", s); // dlina kone4nogo fayla
						
	for (k = 0; k < i; k++) {
		if (isCase(ptr[k]) == 0) {
		if (atoi(ptr[k])) {
			j = atoi(ptr[k])+1;
			printf("Числовой каталог, который нужно увеличить на 1: <%d каталог> = %d\n", k+1, j); // 4islovoy katalog, kotoriy nuzhno uveli4it' na 1
			if (((j - 1) % 1000 == 999 || (j - 1) % 1000 == 99 || (j - 1) % 1000 == 9) && ((j - 1) % 100 == 99 || (j - 1) % 100 == 9) && ((j - 1) % 10 == 9)) {
				printf("Нужно свдинуть строку на 1 вправо, начиная с %d каталога\n", k+1); // nuzhno sdvinut' stroku na 1 vpravo, na4inaya s kataloga
				sdvig(str, k + 1, i, delim, ptr);
			}
		change(ptr[k], j);
		}
		}
	}	
}

void output() {
	printf("\nОбновленная строка: %s", str); // obnovlennaya stroka
}
