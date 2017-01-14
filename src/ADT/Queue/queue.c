/* File : queue.c */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */

#include "../Queue/queue.h"
#include <stdlib.h>


/* ********* Prototype ********* */

boolean IsEmptyQ  (Queue Q)
{
	return ((Head(Q) == NilQ) && (Tail(Q) == NilQ));
}
/* Mengirim true jika Q kosong: lihat definisi di atas */

int NBElmtQ  (Queue Q)
{
	// KAMUS


			// ALGORITMA
			if ((Head(Q) == NilQ) && (Tail(Q) == NilQ))
			{
				return (0);
			}
			else if (Head(Q) <= Tail (Q))
			{
				return (Tail(Q) - Head(Q) + 1);
			}
			else // if (Head(Q) > Tail(Q))
			{
				return (MaxElQ(Q) - (Head(Q) - Tail(Q)) + 1);
			}
}
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */


/* *** Kreator *** */

void CreateEmptyQ  (Queue * Q, int Max)
{
	// KAMUS


			// ALGORITMA

			(*Q).T = (infotype *) malloc ((Max + 1) * sizeof (infotype));

			if ((*Q).T != NULL)
			{
				MaxElQ(*Q) = Max;
				Head(*Q) = NilQ;
				Tail (*Q) = NilQ;
			}
			else	// alokasi gagal
			{
				MaxElQ(*Q) = NilQ;
			}
}
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxElQ=0 */
/* Proses : Melakukan alokasi,Membuat sebuah Q kosong */


/* *** Destruktor *** */

void DeAlokasiQ (Queue * Q)
{
	// KAMUS


			// ALGORITMA
			MaxElQ(*Q) = NilQ;
			free((*Q).T);
}
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxElQ(Q) diset 0 */


/* *** Primitif Add/Delete *** */

void AddQ  (Queue * Q, infotype X)
{
	// KAMUS


		// ALGORITMA
		if (IsEmptyQ(*Q))
		{
			Head(*Q) = 1;
			Tail(*Q) = 1;
		}
		else
		{
			Tail(*Q) = (Tail(*Q) % MaxElQ(*Q) + 1);
		}
		InfoTail(*Q) = X;
}
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */

void DelQ (Queue * Q, infotype * X)
{
	// KAMUS


		// ALGORITMA
		*X = InfoHead(*Q);
		if (Head(*Q) == Tail(*Q))
		{
			Head(*Q) = NilQ;
			Tail(*Q) = NilQ;
		}
		else
		{
			Head(*Q) = ((Head(*Q) % MaxElQ(*Q)) + 1);
		}

}
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = NilQai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; Q mungkin kosong */
