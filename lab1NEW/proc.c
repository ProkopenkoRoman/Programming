#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "proc.h"
#include <conio.h>

void input(char *s) {
	int i = 0;
	char ch[262];
	printf("Введите строку, соответствующую абсолютному пути:\n"); // vvedite stroku, sootvetstvuyushuyu absolutnomu puti	
//		scanf("%s", &ch);

/////// posimvol'no s4itivaem stroku(pomoglo ispravit' oshibku, kogda stroka posle probela ne s4itivalas' ///////
	do {
		scanf("%c",&ch[i]); 
		i++;
	} while(ch[i-1] != '\n');
	s[i-1] = '\0'; 
	
	if(slen(ch) > 261) {
	 	printf("Превышение допустимой длины пути..."); // previshenie dopustimoy dlini puti
	 	exit(1);
	}
	else {
		for (i = 0; i < slen(ch); i++)
         	s[i] = ch[i]; 
		printf("Входная строка: %s\n\n", s); // vhodnaya stroka
	} 
}

void check(char *s) {
	sspn(s); // proverka na nedopustimie simvoli
	printf("\n");
}

void process(char *s) {
	int i, s1, f = 0, k, j;
	
	////////////////////////////////////// OPREDELENIE OS //////////////////////////////////////
	first_ch = s[0];
	if (first_ch == '/' && schr(s, '\\') < 0 && schr(s, ':') < 0) {
		printf("OS: Linux\n");
		delim = '/';
		f=1;
	}
	if ((isLowCase(first_ch) == 1 || isHighCase(first_ch) == 1) && schr(s, '/') < 0 && schr(s, ':') > 0 && schr(s, ':') < 3 && schr(s, '\\') > schr(s, ':') && schr(s, '\\') == schr(s, ':') + 1) {
		printf("OS: Windows\n");
		delim = '\\';
		f=1;
	}
	if (f == 0) {
		printf("Ошибочный путь...\n"); // oshibo4niy put'
		exit(1);
	}
	
	printf("Разделитель: %c\n", delim); // razdelitel'
      	
	i = stok(s, delim, ptr);
	printf("Количество каталогов: %d\n", i - 2); // koli4estvo katalogov
	
	printf("Конечный файл: %s\n", ptr[i-1]); // kone4niy fayl
	
	s1 = slen(ptr[i-1]);
	printf("Длина конечного файла: %d\n\n", s1); // dlina kone4nogo fayla
						
	for (k = 0; k < i; k++) {
		if (isCase(ptr[k]) == 0) {
		if (atoi(ptr[k])) {
			j = atoi(ptr[k])+1;
			printf("Числовой каталог, который нужно увеличить на 1: <%d каталог> = %d\n", k, j); // 4islovoy katalog, kotoriy nuzhno uveli4it' na 1
			if (((j - 1) % 1000 == 999 || (j - 1) % 1000 == 99 || (j - 1) % 1000 == 9) && ((j - 1) % 100 == 99 || (j - 1) % 100 == 9) && ((j - 1) % 10 == 9)) {
				printf("Нужно свдинуть строку на 1 вправо, начиная с %d каталога\n", k); // nuzhno sdvinut' stroku na 1 vpravo, na4inaya s kataloga
				sdvig(s, k + 1, i, delim, ptr);
			}
		change(ptr[k], j);
		}
		}
	}
	suntok(s, delim, ptr, i);	
}

void output(char *s) {
	printf("\nОбновленная строка: %s", s); // obnovlennaya stroka
}
