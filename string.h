#ifndef STRING   
#define STRING   
 
 	int i, j, k, s, f;
	char *ptr[20];
	char first_ch, delim;
	char str[261];
	
void sdvig(char *s, int j, int i, char delim, char *ptr[]);
int isLowCase(char ch);
int isHighCase(char ch);
void change(char *s, int k);
void sspn(char *s);
int slen(char *s);
int stok(char *s, char delim, char *ptr[]);	
int schr(char *s, char delim);
int sequal(char *s1, char *s2);
void scopy(char *s1, char *s2);
void suntok(char *s, char delim, char *ptr[], int cnt);
void input();
void check();
void process();
void output();
 
#endif 

