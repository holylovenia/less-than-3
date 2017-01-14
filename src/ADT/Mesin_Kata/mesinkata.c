/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#include "../Mesin_Kata/mesinkata.h"
#include <stdio.h>
#include <stdlib.h>

boolean EndKata;
Kata CKata;

void IgnoreBlank() {
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */

   while ( (CC == BLANK) && (CC!=MARK) ) {
    ADV();
   }
}
void IgnoreBlankNewLine()
/* Mengabaikan satu atau beberapa BLANK atau NEWLINE
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC ≠ NEWLINE atau CC = MARK */
{	/* Algoritma */
	while (((CC == BLANK) || (CC == NEWLINE) || (CC == CARRIAGERETURN)) && (CC != MARK)) {
		ADV();
	} /* CC != BLANK or CC = MARK */
}
void STARTKATA(char* import) {
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
  START(import);
  IgnoreBlankNewLine();
  if (CC == MARK) {
    EndKata = true;
  } else {
    EndKata = false;
    SalinKata();
  }
}
void ADVKATA() {
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */
  IgnoreBlankNewLine();
  if ( CC == MARK ) {
    EndKata = true;
  } else {
    SalinKata();
    IgnoreBlankNewLine();
  }
}
void SalinKata() {
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
	int i = 0;
	if (CC != 34) {
		while ( (CC != MARK) && (CC != BLANK) &&(i<NMax)) {
			i++;
			CKata.TabKata[i] = CC;
			ADV();
		}
	} else {
		ADV();
		while ((CC != 34) && (i < NMax)) {
			i++;
			CKata.TabKata[i] = CC;
			ADV();
		}
		ADV();
	}
	CKata.Length = i;
}
void SalinKataUI() {
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
  int i = 0;
  while ( (CC != '\n') && (CC != BLANK) &&(i<NMax)) {
    i++;
    CKata.TabKata[i] = CC;
    ADVUI();
  }
  CKata.Length = i;
}

boolean IsKataSama(Kata C1, Kata C2) {
  boolean sama = true;
  int i;
  if (C1.Length != C2.Length) {
    return false;
  } else {
    i = 1;
    while (i<= C1.Length && sama) {
      if (C1.TabKata[i] != C2.TabKata[i]) {
        sama = false;
      } else {
        i++;
      }
    }
    if (sama) {
      return true;
    } else {
      return false;
    }
  }
}

void CopyKataToString (Kata kata, char* str) {
	// KAMUS
	size_t i;

	// ALGORITMA
	for (i = 0; i < kata.Length; i++)
		str[i] = kata.TabKata[i+1];
	str[i] = '\0';
}

int KataToInt (Kata kata) {
	// KAMUS
	char cstr[20];

	// KAMUS
	CopyKataToString(kata,cstr);
	return atoi(cstr);
}
