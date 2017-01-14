// Deskripsi: Definisi fungsi dan prosedur umum

#ifndef GENERAL_H
#define GENERAL_H

#include "../Boolean/boolean.h"
//#include "character.h"

void CopyNama(char* str1, char* str2);
/*I.S. str1 dan str2 terdefinisi
  F.S. str2 merupakan string copy dari str1*/

int CompareString(const char *str1, const char *str2);
/*	Fungsi membandingkan str1 dengan str2 secara leksikografis (sesuai kamus).
	Fungsi mengembalikan 0 jika kedua string sama
	Fungsi mengembalikan -1 jika str1 lebih kecil dari str2 (jika di kamus, str1 di atas str2)
	Fungsi mengembalikan 1 jika str1 lebih besar dari str2 (jika di kamus, str1 di bawah str2) 	*/

void CopyString(char* src, char* dest);
/* 	Prosedur menyalin string src ke string dest
 *	I.S. src terdefinisi, dest sembarang
 *	F.S. dest berisi salinan src */

int LengthString(char* src);
/* Fungsi mengembalikan panjang string masukan */

char* ConcatString(char *str1, char *str2);
/* Fungsi mengembalikan string yang merupakan str1 ditempel dengan str2 */
#endif
