#include <stdio.h>
#include <stdlib.h>
#include "string.h"

// sdvig stroki i ukazateley
void sdvig(char *s, int j, int i, char delim, char *ptr[]) {
	char *suf = s;
	int idx = ptr[j] - suf;
	int m;
	
	// sdvig stroki
	for (m = 261; m > idx-1; m--) 
		s[m + 1] = s[m];
	
	// sdvig ukazateley
	for (m = j; m < i; m++) 
		ptr[m] = ptr[m] + 1;
}

// zamena kataloga <n> na <n+1>
void change(char *s, int k) {
char* c;
    c = (char *)malloc(10 * sizeof(char)); 
    int i, v = 0; // koli4estvo cifr v 4isle n
    // razbiaem na otdel'nie simvoli 4islo n
    while (k > 9) {
        c[v++] = (k % 10) + '0';
        k = k / 10;
    }
    c[v++] = k + '0';
    c[v] = '\0';
    char t;
    // invertiruem massiv simvolov
    for (i = 0; i < v / 2; i++) {
        t = c[i];
        c[i] = c[v - 1 - i];
        c[v - 1 - i] = t;
    }
    v = 0;
    for (v=0; c[v] != '\0'; v++)
        s[v] = c[v];
    free(c);
}

// prinadlezhnost' k latinskim bukvam nizhnego registra
int isLowCase(char ch) {
if( ch >= 'a' && ch <= 'z')
return 1;
return 0;
}

// prinadlezhnost' k latinskim bukvam verhnego registra
int isHighCase(char ch) {
if( ch >= 'A' && ch <= 'Z')
return 1;
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
	for(i = 0;  s[i] != '\0'; i++)
		if (s[i] == '*' || s[i] == '&' || s[i] == '?' || s[i] == '|' || s[i] == '"' || s[i] == '<' || s[i] == '>' || s[i] == ';' || s[i] == ',') {
			fprintf(stderr, "Недопустимый символ <%c> на позиции <%d>;", s[i], i); // nedopustimiy simvol na pozicii
			printf("\n");
		}
}

// sravnenie strok
int sequal(char *s1, char *s2) {
	int i, out = 1;
	for(i = 0; out && (s1[i] != '\0' && s2[i] != '\0'); i++)
		if (s1[i] != s2[i]){
			out = 0;
			return out;
		}
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
	for(i = 1; i < cnt; i++)
		*(ptr[i] - 1) = delim;
}
