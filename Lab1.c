#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void sspn(char *s);
int slen(char *s);
int stok(char *str, char delim, char *ptr[]);
int schr(char *str, char delim);
int sequal(char *s, char *s2);
void scopy(char *s, char *s2);
void suntok(char *str, char delim, char *ptr[], int cnt);

int main() {
	int i, j, k;
	//char ch[260]; // vremenniy massiv dlya dannih
	char delim; // razdelitel'
	char *ptr[10];
	
	char somedir[] = "~/";
	char username[] = "John";
	char dir[] = "o/";
	char paths[] = "~/games/packman.cpp+~al*x/docs+~/study/Prog/lab4.c+/us*r/bin/gcc";
	
    printf("Vvedite razdlitel':\n");
      scanf("%c",&delim); // razdelitel'
 /*   printf("Vvedite imya polzovatelya:\n");
      scanf("%s", &ch);
       char *username = (int *)malloc(slen(ch)*sizeof(int)); // imya polzovatelya
        for (i=0; i<slen(ch); i++)
         username[i]=ch[i];
    printf("Vvedite imya domashney direktorii:\n");
      scanf("%s", &ch);
       char *dir = (int *)malloc(slen(ch)*sizeof(int)); // imya domashnego kataloga
        for (i=0; i<slen(ch); i++)
         dir[i]=ch[i];
    printf("Vvedite puti cherez razdeliteli:\n");
      scanf("%s", &ch);
       char *paths = (int *)malloc(slen(ch)*sizeof(int)); // vhodnaya stroka s putyami
        for (i=0; i<slen(ch); i++)
         paths[i]=ch[i]; */
    
	i = stok(paths, delim, ptr);
	for(j = 0;  j < i; j++) {
		sspn(ptr[j]);
	}
	
	for(j = 0;  j < i; j++) {
		k = sequal(ptr[j], somedir);
		if(k == 1){
			scopy(dir, ptr[j]);
		}
	}
	
	suntok(paths, delim, ptr, i);
	printf("New paths: %s\n", paths);
	
    return 0;
}

// dlina stroki
int slen(char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

// razbienie stroki na podstroki
int stok(char *str, char delim, char *ptr[]) {
	char *suf = str;
	ptr[0] = str;
	int i, j = 1;
	while ( (i = schr(suf, delim)) >= 0 ) {
		suf[i] = '\0';
		suf = suf + i + 1;
		ptr[j] = suf;
		j++;
	}
	return j;
}

// poisk simvola v stroke
int schr(char *str, char delim) {
	int i, idx = -1;
	for (i = 0; (str[i] != '\0') && (str[i] != delim); i++)
		if(str[i] == delim)
			idx = i;
	return idx;
}

// proverka stroki na nedopustimie simvoli
void sspn(char *s) {
	int i;
	for(i = 0; s[i] != '\0'; i++) {
		if (s[i] == '*') {
			fprintf(stderr, "invalid character  %d \n", i);
			printf("%s\n",s);
			//exit(EXIT_FAILURE);
		}
	}
}

// sravnenie strok
int sequal(char *s, char *s2)
{
	int i, out = 1;
	for(i = 0; out && (s[i] != '\0' && s2[i] != '\0'); i++){
		if (s[i] != s2[i]){
			out = 0;
			return out;
		}
	}
	return out; // out = 1
}

// kopirovanie stroki
void scopy(char *s, char *s2) {
	int i;
	for(i = 0; (s[i] != '\0' && s2[i] != '\0'); i++)
		s2[i] = s[i];
}

// sobiranie stroki
void suntok(char *str, char delim, char *ptr[], int cnt)
{
	int i;
	for(i = 1; i < cnt; i++){
		*(ptr[i] - 1) = delim;
	}
}