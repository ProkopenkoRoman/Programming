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
void input();
void check();
void process();
void output();

	int i, j, k, s, f=0;
	char *ptr[20];
	char first_ch, delim;
	//char str[261] = "CA:\\home\\qwert\\999\\openmpi\\165\\lib\OpenMPI\\mca_btl_tcp.so"; // windows
	//char str[261] = "/home/qwert/9/openmpi/165/lib/OpenMPI/mca_btl_tcp.so"; // linux
	char str[261];

int main() {
	setlocale(LC_ALL, "Russian");
	
	input(); 
	check();
	process();
	suntok(str, delim, ptr, i);
	output();
    return 0;
}

void input() {
	int i;
	char ch[500];
	
	printf("Введите строку, соответствующую абсолютному пути:\n"); // vvedite stroku, sootvetstvuyushuyu absolutnomu puti	
		scanf("%s", &ch);
	if(slen(ch) > 261) {
	 	printf("Превышение допустимой длины пути...");
	 	exit(1);
	}
	else {
		for (i = 0; i < slen(ch); i++)
         	str[i] = ch[i]; 
		printf("Входная строка: %s\n\n", str); // vhodnaya stroka
	} 
	printf("Входная строка: %s\n\n", str); // vhodnaya stroka
}

void check() {
	sspn(str); // proverka na nedopustimie simvoli
	printf("\n");
}

void process() {
	////////////////////////////////////// OPREDELENIE OS //////////////////////////////////////
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
		printf("Ошибочный путь...\n"); // oshibo4niy put'
		exit(1);
	}
	
	printf("Разделитель: %c\n", delim); // razdelitel'
      	
	i = stok(str, delim, ptr);
	printf("Количество каталогов с учетом конечного файла: %d\n", i); // koli4estvo katalogov s u4etom kone4nogo fayla
	
	printf("Конечный файл: %s\n", ptr[i-1]); // kone4niy fayl
	
	s = slen(ptr[i-1]);
	printf("Длина конечного файла: %d\n\n", s); // dlina kone4nogo fayla
	
	for(k = 0; k < i; k++) {
		if (atoi(ptr[k])) {
			j = atoi(ptr[k])+1;
			printf("Числовой каталог, который нужно увеличить на 1: <%d каталог> = %d\n", k+1, j); // 4islovoy katalog, kotoriy nuzhno uveli4it' na 1
			if (((j - 1) % 1000 == 999 || (j - 1) % 1000 == 99 || (j - 1) % 1000 == 9) && ((j - 1) % 100 == 99 || (j - 1) % 100 == 9) && ((j - 1) % 10 == 9)) {
				printf("Нужно свдинуть строку на 1 вправо, начиная с %d каталога\n", k+1); // nuzhno sdvinut' stroku na 1 vpravo, na4inaya s kataloga
				sdvig(str, k + 1, i, delim, ptr);
			}
			change(ptr[k], j);
		}
	}
}

void output() {
	printf("\nОбновленная строка: %s", str); // obnovlennaya stroka
}

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
		if (s[i] ==  '*' || s[i] ==  '&' || s[i] ==  '?' || s[i] ==  '|' || s[i] ==  '"' || s[i] ==  '<' || s[i] ==  '>' || s[i] ==  ';') {
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
