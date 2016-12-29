// ForDZ1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
// Размер обрабатываемого блока в функции сдвига любой до 4 байт
unsigned sdvigright(unsigned a, int n, int L) // Сдвиг вправо на L бит, n - размер блока в битах
{
	// a- исходное значение
	unsigned maska = 0; // Маска для получения правых L битов (младшие L разрядов должны быть 1)
	for (int i = 0; i<L; i++)
	{
		maska <<= 1; // Сдвиг влево на 1 бит
		maska += 1; // Младший бит в 1
	}
	unsigned b = a & maska; // Сохранил младщие L бит в b
	b <<= (n - L); // Сдвигаем младшие биты в начало блока
	a >>= L; // Сдвиг вправо на L бит
	return a | b; // Получаем результат
}

unsigned sdvigleft(unsigned a, int n, int L) // Сдвиг влево на L бит, n - размер блока в битах
{
	// a- исходное значение
	unsigned maska = 0; // Маска для получения левых L битов (старшие L разрядов должны быть 1)
	for (int i = 0; i<L; i++)
	{
		maska <<= 1; // Сдвиг влево на 1 бит
		maska += 1; // Младший бит в 1
	}
	maska <<= (n - L); // Младшие биты сдвигаем в старшую часть блока

	unsigned b = a & maska; // Сохранил старшие L бит в b
	b >>= (n - L); // Сдвигаем старшие биты в младшую часть
	a <<= L; // Сдвиг влево на L бит
	return a | b; // Получаем результат
}

// Одна функция шифрует и дешифрует (работает с блоками по 1 байту)
void shifrDeshifr(char *in, char *out, int n, int key, int reg)
{
	// При шифровании сдвигаем на 2 бита влево 
	/* in - входной массив
	   out - выходной массив
	   n - размерности массивов
	   key - секретный ключ
	   reg - режим работы функции 1 - режим шифрования 2 - режим расшифрования
	   */
	srand(key); // Инициализация генератора секретным ключом для получения гаммы
	// Работаем с блоками по 2 байта
	unsigned char a, b, gamma; // Входное и выходное значения  (все размером 1 байт)
	int l; // Размер блока в байтах
	for (int i = 0; i < n; i ++)
	{ 
		
		memcpy(&a, in + i, 1); // Копируем 1 байт из входного массива
		if (reg == 2) // Режим дешифрования
			a = sdvigright(a, 8, 2); // Сдвигаем на 2 бита вправо
		gamma = rand();
		b = gamma ^ a;
		if (reg == 1) b = sdvigleft(b, 8, 2); // Сдвигаем на 2 бита влево при шифровании
		memcpy(out+i, &b, 1); // Копируем 1 байта в выходной массив
	
	}


}


int _tmain(int argc, _TCHAR* argv[])
{
	char StrIn[64]; // Входная строка
	char StrShifr[64]; // Зашифрованный массив
	char StrOut[64]; // Расшиврованная строка
	printf("Str="); fflush(stdin);
	gets(StrIn);
	int len = strlen(StrIn); // Длина строки
	int key1, key2;
	printf("key1="); scanf("%d", &key1);
	// Шифруем
	shifrDeshifr(StrIn, StrShifr, len, key1, 1);
	// Печаем зашифрованный массив по символьно и коды (т.к. данные двоичные)
	printf("Posle shifr:");
	for (int i = 0; i < len; i++)
		printf("\nChar=%c Code=%d", StrShifr[i], StrShifr[i]);
	printf("\nkey2="); scanf("%d", &key2);
	// Расшифруем
	shifrDeshifr(StrShifr, StrOut, len, key2, 2);
	StrOut[len] = 0; // Строка заканчивается 0
	// Печать строки после расшифровки
	printf("\nPosle deshfr:\n%s\n", StrOut);
	system("pause");

	return 0;
}

