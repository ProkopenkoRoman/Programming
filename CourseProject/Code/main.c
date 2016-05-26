#include "lz77.h"

int main (int argc, char ** argv)
{
	FILE *fin, *fout;	//
	int M, N;			// размеры задаваемого словаря и буфера
	char finname[30], foutname[30]; 
	char ch, op = 0; 
	M = 512; N = 128;	// по умолчанию 

	if (argc > 3)	//если заданы параметры в комм.строке
	{
		// проверить операцию
		if (strcmp(argv[1], "-c") == 0) op = '1';
		else if (strcmp(argv[1], "-d") == 0) op = '2';
		else 
		{
			printf("Command error!\n");
			return 1 ;
		}
		
		// взять имена файлов
		strcpy(&finname , argv[2] );
		printf("Source File : %s\n", finname );
		strcpy(&foutname , argv[3] );
		printf("Result File : %s\n", foutname );
	}
	// иначе задаем через меню
	else
	{
		printf("Input operation!\n1 - Encode\n2 - Decode\n");
		scanf("%c",&op);
		if (op == '1') // выбор операции кодирования
		{
			printf("Input encode filename!\n");		
			scanf("%s",&finname);
			printf("Input result filename!\n");		
			scanf("%s",&foutname);
		}
		else if ( op == '2' ) //декодирования
		{
			printf("Input decode filename!\n");		
			scanf("%s",&finname);
			printf("Input result filename!\n");		
			scanf("%s",&foutname);		
		}
		else
		{
			printf("Command error!\n");
			return 2;	
		}	
	}	
	// при воборе кодирования
	if (op == '1')
	{
		printf("Size Dictionary : %d\n", M);
		printf("Size Buffer : %d\n", N);	
		// приглашение изменить размеры словаря и буфера
		printf("Change Size? (Y) \n", M);
		fflush(stdin);
		scanf("%c", &ch);
		
		if (ch == 'Y' || ch == 'y')
		{
			printf("Input Size Dictionary !\n");
			scanf("%d", &M);
			printf("Input Size Buffer !\n");
			scanf("%d", &N);	
		}
	}
	
	//открытие исходного файла
	fin = fopen(&finname, "rb");
	if (fin == NULL) 
	{
		printf("Error: open read file!");
		return 3;
	}
	// открытие файла для записи результат
	fout = fopen(&foutname, "wb");
	if (fout == NULL) 
	{
		printf("Error: open write file!");
		fclose(fin);
		return 3;
	}

	if (op == '1') {	// вызов ф-ции кодирования
		Encode(fin, fout, M, N);
	}
	else {	//декодирования
		Decode(fin, fout);
	}
	
	// закрыть файлы
	fclose(fin);
	fclose(fout);
	
	printf("Done!\n");
	system("pause");
	return 0;
}
