/* File : stackt.c */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */

#include "../Stack/stackt.h"

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */

void CreateEmptyStack (Stack *S)
{
	Top(*S) = NilS;
}
/* I.S. sembarang{} */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxElS */
/* jadi indeksnya antara 1.. MaxElS+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP berNilSai NilS */


/* ************ Predikat Untuk test keadaan KOLEKSI ************ */

boolean IsEmptyStack (Stack S)
{
	return (Top(S) == NilS);
}
/* Mengirim true jika Stack kosong: lihat definisi di atas */


/* ************ Menambahkan sebuah elemen ke Stack ************ */

void PushStack (Stack * S, infotypeS X)
{
	Top(*S)++;
	InfoTop(*S) = X;
}
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */


/* ************ Menghapus sebuah elemen Stack ************ */

void PopStack (Stack * S, infotypeS* X)
{
	*X = InfoTop(*S);
	Top(*S)--;
}
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah NilSai elemen TOP yang lama, TOP berkurang 1 */
