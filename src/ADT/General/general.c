// Deskripsi: Implementasi fungsi dan prosedur umum lain-lain

#include "../Character/character.h"
#include "../Boolean/boolean.h"
#include "../General/general.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void CopyNama(char* str1, char* str2)
/*I.S. str1 dan str2 terdefinisi
  F.S. str2 merupakan string copy dari str1*/
{
	int i = 0;
	while (str1[i] != '\0')
    {
        str2[i] = str1[i];
		i++;
    }
	str2[i] = '\0';
}

int CompareString(const char *str1, const char *str2)
/*	Fungsi membandingkan str1 dengan str2 secara leksikografis (sesuai kamus).
	Fungsi mengembalikan 0 jika kedua string sama
	Fungsi mengembalikan -1 jika str1 lebih kecil dari str2 (jika di kamus, str1 di atas str2)
	Fungsi mengembalikan 1 jika str1 lebih besar dari str2 (jika di kamus, str1 di bawah str2) 	*/
{	// KAMUS
	int i = 0;

	// ALGORITMA
	while ((str1[i] == str2[i]) && (str1[i] != '\0')) {
		i++;
	}
	if (str1[i] < str2[i]) {
		return -1;
	} else if (str1[i] > str2[i]) {
		return 1;
	} else {
		return 0;
	}
}

void CopyString(char* src, char* dest)
/* 	Prosedur menyalin string src ke string dest
 *	I.S. src terdefinisi, dest sembarang
 *	F.S. dest berisi salinan src */
{
	dest = (char*) malloc (LengthString(src)*sizeof(char));
	if (dest != NULL) {
		size_t i;
		for (i = 0; src[i] != '\0'; i++)
			dest[i] = src[i];
		dest[i] = '\0';
	}
}

int LengthString(char* src)
/* Fungsi mengembalikan panjang string masukan */
{	// KAMUS
	int n = 0;

	// ALGORITMA
    while (src[n] != '\0')
        n++;
    return n;
}

char* ConcatString(char *str1, char *str2)
/* Fungsi mengembalikan string yang merupakan str1 ditempel dengan str2 */
{
	char* str3 = (char*) malloc ((LengthString(str1)+LengthString(str2))*sizeof(char));
	if (str3 != NULL) {
		size_t i,j;
		for (i = 0; str1[i] != '\0'; i++)
			str3[i] = str1[i];
		for (j = 0; str2[j] != '\0'; j++)
			str3[i+j] = str2[j];
		str3[i+j] = '\0';
	}
	return str3;
}
