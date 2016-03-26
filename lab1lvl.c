#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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

int main() {
	setlocale(LC_ALL, "Russian");
	
	int i, j, k, s, f=0;
	char *ptr[20];
	char first_ch, delim;
	//char str[261] = "CA:\\home\\qwert\\8\\openmpi\\165\\lib\OpenMPI\\mca_btl_tcp.so"; // windows
	char str[261] = "/home/qwert/9/openmpi/165/lib/OpenMPI/mca_btl_tcp.so"; // linux
	//char *suf = str;

	//printf("Ââåäèòå ñòðîêó, ñîîòâåòñòâóþùàóþ àáñîëþòíîìó ïóòè:\n");
	//scanf("%s\n", &str);
	
	printf("Âõîäíàÿ ñòðîêà: %s\n\n", str);
	sspn(str); // ïðîâåðêà íà íåäîïóñòèìûå ñèìâîëû
	printf("\n");
	
	////////////////////////////////////// ÎÏÐÅÄÅËÅÍÈÅ OS //////////////////////////////////////
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
		printf("Îøèáî÷íûé ïóòü...\n");
		return 1;
	}
	
	printf("Ðàçäåëèòåëü: %c\n", delim);
      	
	i = stok(str, delim, ptr);
	printf("Êîëè÷åñòâî êàòàëîãîâ ñ ó÷åòîì êîíå÷íîãî ôàéëà: %d\n", i);
	
	printf("Êîíå÷íûé ôàéë: %s\n", ptr[i-1]);
	
	s = slen(ptr[i-1]);
	printf("Äëèíà êîíå÷íîãî ôàéëà: %d\n\n", s);
	
	for(k = 0; k < i; k++) {
		if (atoi(ptr[k])) {
			j = atoi(ptr[k])+1;
			printf("×èñëîâîé êàòàëîã, êîòîðûé íóæíî óâåëè÷èòü íà 1: <%d êàòàëîã> = %d\n", k+1, j);
			if (((j - 1) % 1000 == 999 || (j - 1) % 1000 == 99 || (j - 1) % 1000 == 9) && ((j - 1) % 100 == 99 || (j - 1) % 100 == 9) && ((j - 1) % 10 == 9)) {
				printf("Íóæíî ñâäèíóòü ñòðîêó íà 1 âïðàâî, íà÷èíàÿ ñ %d êàòàëîãà\n", k+1);
				//sdvig(str, k + 1, i, delim, ptr);
			}
			change(ptr[k], j);
		}
	}
	
	suntok(str, delim, ptr, i);
	printf("\nÎáíîâëåííàÿ ñòðîêà: %s\n", str);
	
    return 0;
}


// ñäâèã ñòðîêè
void sdvig(char *s, int j, int i, char delim, char *ptr[]) {
	int m, count = 0;
	for (m = slen(s); count < i - j; m--) {
		if (s[m] == delim)
			count++;
		s[m + 1] = s[m];	
	}
	
	for (m = i - j; m < i; m++) {
		ptr[m] = ptr[m] + 1;
	}
}


// çàìåíà ñòðîêè
void change(char *s, int k) {
char* c;
    c = (char *)malloc(10 * sizeof(char)); 
    int i, v = 0; //êîëè÷åñòâî öèôð â ÷èñëå n
    //ðàçáèâàåì íà îòäåëüíûå ñèìâîëû ÷èñëî n
    while (k > 9)
    {
        c[v++] = (k % 10) + '0';
        k = k / 10;
    }
    c[v++] = k + '0';
    c[v] = '\0';
    char t;
    //èíâåðòèðóåì ìàññèâ ñèìâîëîâ
    for (i = 0; i < v / 2; i++)
    {
        t = c[i];
        c[i] = c[v - 1 - i];
        c[v - 1 - i] = t;
    }
    v = 0;
    for (v=0; c[v] != '\0'; v++)
        s[v] = c[v];
    free(c);
}


// ïðèíàäëåæíîñòü ê ëàòèíñêèì áóêâàì íèæíåãî ðåãèñòðà
int isLowCase(char ch) {
if( ch >= 'a' && ch <= 'z')
return 1;
return 0;
}


// ïðèíàäëåæíîñòü ê ëàòèíñêèì áóêâàì âåðõíåãî ðåãèñòðà
int isHighCase(char ch) {
if( ch >= 'A' && ch <= 'Z')
return 1;
return 0;
}


// äëèíà ñòðîêè
int slen(char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}


// ðàçáèåíèå ñòðîêè íà ïîäñòðîêè
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


// ïîèñê ñèìâîëà â ñòðîêå
int schr(char *s, char delim) {
	int i, idx = -1;
	for(i = 0; (s[i] != '\0') && (s[i] != delim); i++);
		if(s[i] == delim)
			idx = i;
	return idx;
}


// ïðîâåðêà ñòðîêè íà íåäîïóñòèìûå ñèìâîëû
void sspn(char *s) {
	int i;
	for(i = 0;  s[i] != '\0'; i++){
		if (s[i] ==  '*' || s[i] ==  '&' || s[i] ==  '?' || s[i] ==  '|' || s[i] ==  '"' || s[i] ==  '<' || s[i] ==  '>' || s[i] ==  ';')
			fprintf(stderr, "Íåäîïóñòèìûé ñèìâîë <%c> íà ïîçèöèè <%d>;\n", s[i], i);
	}
}


// ñðàâíåíèå ñòðîê
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


// êîïèðîâàíèå ñòðîêè
void scopy(char *s1, char *s2) {
	int i;
	for(i = 0; (s1[i] != '\0' && s2[i] != '\0'); i++)
		s2[i] = s1[i];
	
}


// ñîáèðàíèå ñòðîêè
void suntok(char *s, char delim, char *ptr[], int cnt) {
	int i;
	for(i = 1; i < cnt; i++){
		*(ptr[i] - 1) = delim;
	}
}
