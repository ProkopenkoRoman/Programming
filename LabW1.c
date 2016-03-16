#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void sspn(char *s);
int slen(char *s);
int stok(char *s, char delim, char *ptr[]);	
int schr(char *s, char delim);
int sequal(char *s1, char *s2);
void scopy(char *s1, char *s2);
void suntok(char *s, char delim, char *ptr[], int cnt);

int main() {
	int i, j, k, r, s1, index, delta, n;
	//char ch[260]; // vremenniy massiv dlya dannih
	char delim; // razdelitel'
	char *ptr[10];
	char tmp;
	
	char somedir[] = "~/";
	char username[] = "John";
	char dir[] = "ooo/";
	char paths[260] = "~/games/packman.cpp+~alex/d*cs+~/study/Prog/lab4.c+/us*r/bin/gcc+~/lab/pr*ject1";
	char *suf = paths;
	delta = slen(somedir)-slen(dir);
	s1 = slen(paths);
	
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
    printf("Vvedite pu0ti cherez razdeliteli:\n");
      scanf("%s", &ch);
       char *paths = (int *)malloc(slen(ch)*sizeof(int)); // vhodnaya stroka s putyami
        for (i=0; i<slen(ch); i++)
         paths[i]=ch[i]; */

	//r = slen(dir) - slen(somedir);
	//printf("Sdvig na %d\n", r);
      	
	i = stok(paths, delim, ptr);
	for(j = 0;  j < i; j++) {
		sspn(ptr[j]);
	}
	
	for(j = 0;  j < i; j++) {
		k = sequal(ptr[j], somedir);
		if(k == 1){
			index = ptr[j] - suf;
			
			if (delta < 0) {
				for (n = s1 - delta; n > index + delta ; n--) {
					paths[n - delta] = paths[n];
				}
				for (n = j; n < i - 1; n++) {
			
				ptr[n + 1] = ptr[n + 1] - delta;
				}
			}
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
int stok(char *s, char delim, char *ptr[]) {
	char *suf = s;
	ptr[0] = s; 
	int i, j = 1; 
	while( ( i = schr(suf, delim) ) >= 0 ){
		suf[i] = '\0';
		suf = suf + i + 1;
		ptr[j] = suf;
		j++;
	}
	return j;
}

// poisk simvola v stroke
int schr(char *s, char delim) {
	int i, idx = -1;
	for(i = 0; (s[i] != '\0') && (s[i] != delim); i++);
		if(s[i] == delim)
			idx = i;
	return idx;
}

// proverka stroki na nedopustimie simvoli
void sspn(char *s) {
	int i;
	for(i = 0;  s[i] != '\0'; i++){
		if (s[i] ==  '*' ){
			
			fprintf(stderr, "invalid character  %d \n", i);
			printf("%s\n",s);
			//exit(EXIT_FAILURE);
		}
	}
}

// sravnenie strok
int sequal(char *s1, char *s2) {
	int i, out = 1;
	for(i = 0; out && (s1[i] != '\0' && s2[i] != '\0'); i++){
		if (s1[i] != s2[i]){
			out = 0;
			return out;
		}
	}
	//out = 1;
	return out;
}

// kopirovanie stroki
void scopy(char *s1, char *s2) {
	int i;
	for(i = 0; (s1[i] != '\0' && s2[i] != '\0'); i++)
		s2[i] = s1[i];
	
}

// sobiranie stroki
void suntok(char *s, char delim, char *ptr[], int cnt) {
	int i;
	for(i = 1; i < cnt; i++){
		*(ptr[i] - 1) = delim;
	}
}
