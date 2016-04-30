#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "analiz.h"

int sspn_time(char *s)
{
	int i;
	
	/*if (slen(s) > 260){
		printf("lengs string > 260  \n");
		//printf("%s\n",s);
		exit(EXIT_FAILURE);
	}*/
	
	for(i = 0;  s[i] != '\0'; i++){
		if ((s[i] != '*') || (s[i] != '-') || (s[i] != '/') || (atoi(s[i]) > 9) || (atoi(s[i]) < 0)){
			return 1;
			printf(" return 1 \n");
		}
	}
	printf(" return 0 \n");
return 0;
}

//пропуск пробелов
char *skip_spaces(char *suf) {
	int t, i,j;
	for(i = 0; suf[i] != '\0'; i++ ){
		
		t = schr(suf, '\t');
		
		if (t >= 0) {
			suf[t] = 0x20;
			t = -1;
		}
	}
	for(i = 0; suf[i] != '\0'; i++ ){
		for(j = 0; suf[i] == 0x20 && suf[i+1] == 0x20; j++){
			suf[i + j] = 0x7F; 
		}
	}
return suf;
}

//открывает файл и записывает первую строку файла 
//в массив
void open_file(char *str) {
	FILE *f;
	f = fopen("passwd", "a+");
	char tmp[1024];
	fread(tmp, 1024, 1, f);
	int i; 
	for(i = 0; tmp[i] != '\n'; i++){
		str[i] = tmp[i];
	}	
	skip_spaces(str);

	fclose(f);  
}

void analiz(char *str) {
	
	int i, j;
	char *ptr[7], tmp;
	i = stok(str, ':', ptr);
	
	printf(" i = %d\n", i);
	pwdrecs struk;
	
	
	int id[7];
	for(j = 0; j <= 7; j++){
		id[i] = -1;
		}
		
		FILE *cron, *end;
	cron = fopen("crontab", "a+");
	//проверка на количество полей в строке
	if(i != 7) {
		end = fopen("end", "a+");
		//fread(tmp, 1024, 1, cron);
		fprintf(end," %s", "pidr");
		fclose(end);  
	} 
/*	else {//проверка каждого поля и заполнение структуры
		
		for(i = 0; i <= 5; i++){
			for (j = 0; ptr[j] != '\0'; j++){
					if(sspn_time(ptr[j]) == 1){
						id[i] = 7;
					}
						else id[i] = i;
				}
			}	
		
		}
	for(j = 0; j <= 7; j++){
		printf("id = %d\n", id[i]);
		}
	*/
	fclose(cron);  
}
