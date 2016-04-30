#ifndef STRING
#define STRING

void sspn(char *s);
int slen(char *s);
int stok(char *str, char delim, char *ptr[]);	
int schr(char *str, char delim);
int sequal(char *s, char *s2);
void scopy(char *s, char *s2);
void suntok(char *str, char delim, char *ptr[], int cnt);
int isCase(char ch);

#endif
