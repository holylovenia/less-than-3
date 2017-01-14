/* MODUL TABEL INTEGER */
/* Berisi definisi dan semua primitif pemrosesan tabel integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi I : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori tabel statik */
#include "../Array/array.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>


   /* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmptyTab (TabInt * T)
{
	Neff(*T) = 0;
}
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */


/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */

int NbElmtTab (TabInt T)
{
	return (Neff(T));
}
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */


/* *** Selektor INDEKS *** */

IdxType GetFirstIdxTab (TabInt T)
{
	return(IdxMin);
}
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */

IdxType GetLastIdxTab (TabInt T)
{
	return(IdxMin + NbElmtTab(T) - 1);
}
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */


/* ********** TEST KOSONG ********** */
/* *** Test tabel kosong *** */

boolean IsEmptyTab (TabInt T)
{
	return(NbElmtTab(T) == 0);
}
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */


/* ********** FUNGSI TAMBAHAN ********** */

void ShuffleTab (TabInt * T)
{
	// KAMUS
	int i, j;
	int temp;

		// ALGORITMA
		// Use a different seed value so that we don't get same
		// result each time we run this program
		srand (time(NULL));

		// Start from the last element and swap one by one. We don't
		// need to run for the first element that's why i > 0
		for (i = NbElmtTab(*T) - 1; i > 0; i--)
		{
			// Pick a random index from 0 to i
			j = (rand() % i) + 1;

			// Swap arr[i] with the element at random index
			temp = ElmtTab(*T, i);
			ElmtTab(*T, i) = ElmtTab(*T, j);
			ElmtTab(*T, j) = temp;
		}
}
/* MENGACAK INDEKS ARRAY OF INTEGER
I.S: T adalah array terdefinisi.
F.S: Indeks T sudah diacak.
*/
