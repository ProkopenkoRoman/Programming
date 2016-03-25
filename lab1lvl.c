#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//void increm(char *s, int k);
void sspn(char *s);
int slen(char *s);
int stok(char *s, char delim, char *ptr[]);	
int schr(char *s, char delim);
int sequal(char *s1, char *s2);
void scopy(char *s1, char *s2);
void suntok(char *s, char delim, char *ptr[], int cnt);

int main() {
	setlocale(LC_ALL, "Russian");
	
	int i, j, k, s, f=0;
	char *ptr[20];
	char first_ch, delim;
	char str[260] = "/home/qwert/9/openmpi/165/lib/OpenMPI/mca_btl_tcp.so";
	//char *suf = str;

	//printf("Ââåäèòå ñòðîêó, ñîîòâåòñòâóþùàóþ àáñîëþòíîìó ïóòè:\n");
	//scanf("%s\n", &str);
	
	printf("Âõîäíàÿ ñòðîêà: %s\n\n", str);
	
	first_ch = str[0];
	if (first_ch == '/') {
		printf("OS: Linux\n");
		delim = '/';
		f=1;
	}
	if ((first_ch == 'C') || (first_ch == 'D') || (first_ch == 'A')) {
		printf("OS: Windows\n");
		delim = '\\';
		f=1;
	}
	if (f == 0)
		printf("Error...\n");	
	
	printf("Ðàçäåëèòåëü: %c\n", delim);
      	
	i = stok(str, delim, ptr);
	printf("Êîëè÷åñòâî êàòàëîãîâ ñ ó÷åòîì êîíå÷íîãî ôàéëà: %d\n", i);
	
	printf("Êîíå÷íûé ôàéë: %s\n", ptr[i-1]);
	
	s = slen(ptr[i-1]);
	printf("Äëèíà êîíå÷íîãî ôàéëà: %d\n", s);
	
	for(k = 0; k < i; k++) {
		if (atoi(ptr[k])) {
			j = atoi(ptr[k])+1;
			printf("×èñëîâîé êàòàëîã óâåëè÷åííûé íà 1: <%d êàòàëîã> = %d\n", k, j);
			//increm(ptr[k], j);
		}
	}
	
	suntok(str, delim, ptr, i);
	printf("Îáíîâëåííàÿ ñòðîêà: %s\n", str);
	
 /*	for(j = 0;  j < i; j++)
		sspn(ptr[j]);
 */
    return 0;
}

// zamena stroki
/*void increm(char *s, int k) {
    int i;
    for (i = 0; s[i] != '\0'; i++)
    itoa(k, s);
}*/

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
