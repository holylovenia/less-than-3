/* File: listrek.c */
/* ADT list linier dengan representasi pointer */
/* Implementasi list linier secara rekursif dengan binary tree sebagai infonya */


#include <stdlib.h>
#include "../List_Rekursif/listrek.h"
#include <stdio.h>



/* *** Manajemen Memori *** */


address AlokasiLR (BinTree X)
{
	// KAMUS
	address P;

		// ALGORITMA
		P = (address) malloc (sizeof (ElmtListLR));
		if (P != NilLR)
		{
			Info(P) = X;
			Next(P) = NilLR;
			return (P);
		}
		else
		{
			return (NilLR);
		}
}
/* Mengirimkan address hasil AlokasiLR sebuah elemen */
/* Jika AlokasiLR berhasil, maka address tidak NilLR, dan misalnya menghasilkan P,
  maka Info(P) = X, Next(P) = NilLR */
/* Jika AlokasiLR gagal, mengirimkan NilLR */

void DealokasiLRLR (address P)
{
	free(P);
}
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan DealokasiLRLR/pengembalian address P */



/* *** Primitif-primitif yang harus direalisasikan *** */


/* Pemeriksaan Kondisi ListLR */

int IsEmptyLR(ListLR L)
{
	if (L == NilLR)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/* Mengirimkan 1 jika L kosong dan 0 jika L tidak kosong */

int IsOneElmtLR(ListLR L)
{
	if ((L != NilLR) && (Next(L) == NilLR))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/* Mengirimkan 1 jika L berisi 1 elemen dan 0 jika > 1 elemen atau kosong */


/* *** Selektor *** */

BinTree FirstElmt (ListLR L)
{
	return (Info(L));
}
/* Mengirimkan elemen pertama sebuah ListLR L yang tidak kosong */

ListLR TailLR(ListLR L)
{
	// KAMUS
	ListLR Ekor;

		// ALGORITMA
		if (IsOneElmtLR(L))
		{
			Ekor = NilLR;
		}
		else
		{
			Ekor = Next(L);
		}
		return (Ekor);
}
/* Mengirimkan ListLR L tanpa elemen pertamanya, mungkin menjadi ListLR kosong */


/* *** Konstruktor *** */
ListLR Konso(BinTree e, ListLR L)
{
	// KAMUS
	address P;
	ListLR Hasil;

		// ALGORITMA
		P = AlokasiLR(e);
		if (P != NilLR)
		{
			Next(P) = L;
			Hasil = P;
		}
		else
		{
			Hasil = L;
		}
		return (Hasil);
}
/* Mengirimkan ListLR L dengan tambahan e sebagai elemen pertamanya.
e diAlokasiLR terlebih dahulu. Jika AlokasiLR gagal, mengirimkan L. */

ListLR KonsB(ListLR L, BinTree e)
{
		// KAMUS
	address P;

		// ALGORITMA
		if (IsEmptyLR(L) == 1)
		{
			P = AlokasiLR(e);
			if (P != NilLR)
			{
				return (P);
			}
			else
			{
				return (NilLR);
			}
		}
		else
		{
			Next(L) = (KonsB(TailLR(L), e));
			return (L);
		}
}
/* Mengirimkan ListLR L dengan tambahan e sebagai elemen pertamanya */
/* e harus diAlokasiLR terlebih dahulu */
/* Jika AlokasiLR e gagal, mengirimkan L */


/* *** Operasi Lain *** */

void PrintListLR (ListLR L)
{
	// KAMUS


		// ALGORITMA
		if (IsEmptyLR(L) == 1)
		{
		}
		else
		{
			printf("%d) %s\n", ID(Akar(FirstElmt(L))), NamaBT(Akar(FirstElmt(L))));
			PrintListLR(TailLR(L));
		}
}
/* I.S. L terdefinisi. */
/* F.S. Setiap elemen ListLR dicetak. */

int NbElmtListLR (ListLR L)
{
	// KAMUS
	int count;

		// ALGORITMA
		count = 0;
		if (IsEmptyLR(L) == 1)
		{
		}
		else
		{
			count = 1 + NbElmtListLR(TailLR(L));
		}
		return (count);

}
/* Mengirimkan banyaknya elemen ListLR L, Nol jika L kosong */

boolean SearchLR (ListLR L, BinTree X)
{
	// KAMUS


		// ALGORITMA
		if (IsEmptyLR(L) == 1)
		{
			return (false);
		}
		else
		{
			if (NamaBT(Akar(FirstElmt(L))) == NamaBT(Akar(X)))
			{
				return (true);
			}
			else
			{
				return (SearchLR(TailLR(L), X));
			}
		}
}
/* Mengirim true jika X adalah anggota ListLR, false jika tidak */
