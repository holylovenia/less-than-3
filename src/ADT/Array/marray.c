//Cara Compile : gcc -o test darray.c array.c
#include <stdio.h>
#include "../Array/array.h"

int main ()
{
	// KAMUS
	TabInt T;
	int i, N;

		// ALGORITMA
		MakeEmptyTab(&T);

		if (IsEmptyTab(T))
		{
			printf("Array T kosong\n");
		}


		N = 10;

		printf("Isi array T:\n");
		for (i = 1; i <= N; i++)
		{
			ElmtTab(T, i) = i;
			Neff(T)++;
			printf("%d ", ElmtTab(T, i));
		}
		printf("\n\n");

		if (!IsEmptyTab(T))
		{
			printf("Array T ada isinya: %d buah\n", NbElmtTab(T));
		}

		printf("Print isi array T:\n");
		for (i = GetFirstIdxTab(T); i <= GetLastIdxTab(T); i++)
		{
			printf("%d ", ElmtTab(T, i));
		}
		printf("\n\n");

		ShuffleTab(&T);

		printf("Print isi array T setelah diacak:\n");
		for (i = GetFirstIdxTab(T); i <= GetLastIdxTab(T); i++)
		{
			printf("%d ", ElmtTab(T, i));
		}
		printf("\n\n");

	return 0;
}
