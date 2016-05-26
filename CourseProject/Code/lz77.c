#include "lz77.h"

// установить служебную информацию в выходной массив при кодировании
void SetInfo(int* array, int M, int N) {
	array[0] = M; array[1] = N;
}
// взять сл. информацию из входного массива при декодировании
void GetInfo(int* array, int* M, int* N) {
	*M = array[0]; *N = array[1];
}

// установка массива бит в выходной массив при кодировании
// array - выходной массив
// offset- смещение в битах от начала
// value - устанавливаемое значение
// len	 - и его длина в битах
int SetBits(int *array, int offset, unsigned int value, int value_len) {

	int i, d ;
	i = offset / 32;	//индекс для массива из int
	d = offset % 32;	//находящийся остаток в битах
	// обнулить все биты числа выходящие за длину битовой последовательности 
	value &=  (int) pow(2.0, (float)value_len) - 1;		
	// добавить в выходной массив
	// сдвинув влево на остаток в битах находящийся уже в массиве
	array[i] += value << d; 
	// если вставили меньше чем длина битовой последовательности
	if (32 - d < value_len) {
		// дописываем последовательность в сл. ячейку массива
		array[i+1] += value >> (32 - d);
	}
	// изменить смещение на длину вставленной последовательности бит
	return offset + value_len;
}
// считать массив бит из входного массива при декодировании
// array - входной массив
// offset- смещение в битах от начала
// value - аддрес переменной для взятия битовой последовательности  
// len	 - и его длина в битах
int GetBits(int *array, int offset, unsigned int* value, int value_len)  {

	int i, d;
	i = offset / 32;
	d = offset % 32;	
	*value = 0;
	// взять из массива значение сдвинутое на осаток смещения
	*value = array[i] >> d;	
	// если взяли меньше чем длина в битах
	if (32 - d < value_len)
	{
		// оставить только те биты которые уже взяли
		// остальные сбросить в 0
		*value &= (int) pow(2.0, (float)(32-d)) - 1;
		// взять оставшуюся часть 
		*value += array[i+1] << (32 - d );
	}
	// обнулить все биты кроме тех что взяли
	*value &= (int) pow(2.0, (float)value_len) - 1;
	// изменить смещение на взятое число бит
	return offset + value_len;
}

// взять размеры файла
int GetFileSize(FILE * f)
{
	int size;
	fseek(f, 0, SEEK_END);	// сместится в конец  
	size = ftell(f);		// взять смещение в байтах от начала
	fseek(f, 0, SEEK_SET);  // вернутся в начало файла
	return size;			// вернуть размер в байтах
}

// поиск наибольшей подстроки буфера в словаре
struct Code Find(char* dict, char *buff , int M, int N) {
	int i, num, tmp;
	char *pstr;			
	struct Code code;	// возвращаемая структура кода
	
	pstr = malloc(N+1);	// выделить память под максимальную подстроку равную длине буфера - 1
	for (i = 0; i < N + 1; i++) {
		pstr[i] = 0;	// обнулить 
	}
	
	tmp = 0;	// временный(предыдущий) адрес найденной подстроки в словаре
	
	// исследовать на всю длину буфера - 1
	// последний символ должен быть записан за подстрокой
	// в случае если найдется подстрока максимальной длины
	// потому N - 1
	for(i = 0; i < N - 1 ; i++) 
	{
		// взять символ из буфера во временную подстроку
		// увеличая ее в длине и проводя поиск
		pstr[i] = buff[i];
		// найти его расположение в словаре
		num = strstr(dict, pstr);
		// если подстрока найдена за пределами словаря в самом буфере
		if (num >= buff) 
		{
			// и нет предыдущего адреса подстроки
			// то символ встречается впервые
			// запишем её код
			if (tmp ==  0) {
				// последний символ за подстрокой
				code.c = pstr[i];
				// длина и смещение в словаре в 0
				code.len = 0; 
				code.num = 0;
				// освободить память
				free(pstr);
				// вернуть код
				return code;
			}		
			// иначе если была найдена подстрока до того как пришли в буфер
			else {
				// взять текущую итерацию за длину
				code.len = i;
				// вычислить смещение в словаре
				code.num = M - (num - tmp); 
				// если вышли за пределы длины файла	
				if (pstr[i] == -1) {
					// взять предыдущий символ
					code.c = pstr[i-1];
					// отнять длину на 1
					code.len--;
				}
				// иначе взять текущий символ
				else code.c = pstr[i];	
				// освободить подстроку
				free(pstr);			
				// вернуть код
				return code;
			}		
		}
		// пока идет цикл
		// сохраняем 
		else tmp = num;
	}
	
	// если цикл завершен
	// то вся подстрока длиной буфера - 1 символ найдена в словаре  
	if (tmp == num && i == N - 1) {
		// запишем длину
		code.len = N - 1;
		// последний символ в буфере
		code.c = buff[code.len];
		// смещение в словаре от начала
		code.num = M - ((int)buff - num); 
	}
	// освобождаем память
	free(pstr);
	// возвращаем код
	return code;
}
	
// ф-ция кодирования файла
void Encode(FILE *fin, FILE *fout, int M, int N) {
	char *input;	// входной и выходной массивы
	char *output;
	int  offset, Mlen, Nlen;
	
	struct Code code;
	int i, k, num, fsize,fosize ;

	fsize = GetFileSize(fin);	// размер файла
	output = malloc(fsize * 4); // выделим память под выходной массив 
	for(i = 0; i < fsize * 4; i++) {
		output[i] = 0;			// обнулить
	}	
	SetInfo(output, M, N);		// установить служебную информацию
	offset = 64;				// смещение в битах от начала на 64 бита больше
		
	// входной массив
	input = malloc(fsize + M + 1);
	input[fsize + M] = -1;
	for(i = 0; i < M; i++) {
		input[i] = -1; // инициализируем в -1
	}		
	// считать файл сместившись в массиве на длину словаря
	fread(&input[M], 1, fsize, fin);

	// вычислить длину словаря и массива в битах
	Mlen = (log((float)M) / log((float)2) + 0.999999);
	Nlen = (log((float)N) / log((float)2) + 0.999999);
		
	//процесс кодирования
	code.len = 0;
	for(i = 0; i < fsize; i += code.len + 1) {
		// поиск записываемого кода
		code = Find(&input[i], &input[i + M], M, N);
		// установка битового массива в выходной массив
		offset = SetBits(output, offset, code.num, Mlen);
		offset = SetBits(output, offset, code.len, Nlen);
		offset = SetBits(output, offset, (int)code.c, 8);
	}		
	
	// найти длину выходного файла в байтах
	fosize = offset / 8;
	// если есть остаток, увеличим на 1 
	if (offset % 8) 
		fosize++;
	
	// записать выходной файл
	if (fwrite(output, 1, fosize, fout))
	{
		// освободить память
		free(input);
		free(output);
	}
	// расчитать коэфф. сжатия
	printf("Compression ratio = %f\n",(float)fsize / (float)fosize); 
}

// ф-ция декодирования
void Decode(FILE *fin, FILE *fout) {
	char *input;
	char *output;
	int offset, Mlen, Nlen, M, N;
	
	struct Code code;
	int i, j, k, num, fsize;

	fsize = GetFileSize(fin);	// размер входного файла
	input = malloc(fsize + 1);	// выделить память под массив
	// проинициализировать в 0
	for(i = 0; i < fsize + 1; i++) {
		input[i] = 0;
	}
	// считать файл 
	fread(input, 1, fsize, fin);
	M = 0; 
	N = 0;
	// взять служебную информацию о размерах словаря и буфера 
	GetInfo(input, &M, &N);
	offset = 64;	// смещение в битах от начала на 64 бита больше
					
	// выделить память под выходной массив
	output = malloc(fsize * 4);
	for(i = 0; i < fsize * 4; i++) {
		output[i] = -1; // инициализация в -1
	}			

	// расчет длины словаря и буфера в битах
	Mlen = (log((float)M) / log((float)2) + 0.999999);
	Nlen = (log((float)N) / log((float)2) + 0.999999);
		
		
	//процесс декодирования
	i = 0;
	while ((fsize - offset / 8) * 8  >=  Mlen + Nlen + 8) {	
		// взять значения из входного массива
		offset = GetBits(input, offset, &code.num, Mlen);
		offset = GetBits(input, offset, &code.len, Nlen);
		offset = GetBits(input, offset, (int)&code.c, 8);
		
		// если подстроки нет в словаре
		if (code.num == 0 && code.len == 0)
			// запишем в буфер как есть
			output[i + M] = code.c;
		else 
		{
			// перепишем всю подстроку в буфер
			for(k = 0; k < code.len; k++) {
				output[i + M + k] = output[i + code.num + k];
			}
			// дописать в конце подстроки символ
			output[i + M + code.len] = code.c;
		}				
		// сместить окно на длину подстроки
		i += code.len + 1;
	}	
	
	// записать выходной файл
	if (fwrite(&output[M], 1, i, fout))
	{
		// освободить память
		free(input);
		free(output);
	}
	// рассчитать коэфф. сжатия
	printf("Compression ratio = %f\n",(float)i / (float)fsize); 
}
