#include <stdio.h>
#include <stdlib.h>
#include "string.h"

int isCase(char ch) {
	//int i;
	//for (i = 0; ch != '\0'; i++)
		if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
			return 1;
	return 0;
}

int slen(char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

int stok(char *str, char delim, char *ptr[]) {
	char *suf = str;
	ptr[0] = str; // 
	int i, j = 1; // 
	
	while((i = schr(suf, delim)) >= 0) {
		suf[i] = '\0';
		suf = suf + i + 1;
		ptr[j] = suf;
		j++;
	}
	return j;
}

void suntok(char *str, char delim, char *ptr[], int cnt) {
	int i;
	for(i = 1; i < cnt; i++){
		*(ptr[i] - 1) = delim;
	}
}

int schr(char *str, char delim) {
	int i, idx = -1;
	for(i = 0; (str[i] != '\0') && (str[i] != delim); i++);
		if(str[i] == delim)
			idx = i;
	return idx;
}

int sequal(char *s, char *s2) {
	int i, out = 1;
	for (i = 0; out && (s[i] != '\0' && s2[i] != '\0'); i++) {
		if (s[i] != s2[i]) {
			out = 0;
			return out;
		}
	}
	//out = 1;
	return out;
}

void sspn(char *s) {
	int i;
	
	if (slen(s) > 260) {
		printf("lengs string > 260  \n");
		//printf("%s\n",s);
		exit(EXIT_FAILURE);
	}
	for(i = 0;  s[i] != '\0'; i++){
		if ((s[i] == '*') || (s[i] == '?') || (s[i] == '"') || (s[i] == '>') || (s[i] == '<') || (s[i] == '|') ) {
			fprintf(stderr, "invalid character number %d \n", i+1);
			//printf("%s\n",s);
			exit(EXIT_FAILURE);
		}
	}
}
