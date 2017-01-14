/* File: bintree.c */
/* ADT Pohon Biner */
/* Implementasi dengan menggunakan pointer */
/* Penamaan type infotypeBT, type addrNode, dan beberapa fungsi disesuaikan */

#include <stdlib.h>
#include "../Binary_Tree/bintree.h"
#include <stdio.h>


/* *** Konstruktor *** */

void CreateEmptyTree(BinTree *P)
{
	*P = NilBT;
}
/* Menghasilkan Tree kosong dimana P = NilBT */

BinTree Tree (infotypeBT Akar, BinTree L, BinTree R)
{
	// KAMUS
	BinTree BT;

		// ALGORITMA
		BT = AlokNode(Akar);
		if (BT != NilBT)
		{
			Left(BT) = L;
			Right(BT) = R;
		}
		return (BT);
}
/* Menghasilkan sebuah pohon biner dari A, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (NilBT) jika alokasi gagal */


/* Manajemen Memory */

addrNode AlokNode (infotypeBT X)
{
	// KAMUS
	addrNode P;

		// ALGORITMA
		P = (addrNode) malloc (sizeof (Node));
		if (P != NilBT)
		{
			Akar(P) = X;
			Left(P) = NilBT;
			Right(P) = NilBT;
		}
		return (P);

}
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak NilBT, dan misalnya menghasilkan P,
  maka Akar(P) = X, Left(P) = NilBT, Right(P)=NilBT */
/* Jika alokasi gagal, mengirimkan NilBT */

void DealokNode (addrNode P)
{
	free(P);
}
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */


/* *** Predikat-Predikat Penting *** */

boolean IsTreeEmpty (BinTree P)
{
	return (P == NilBT);
}
/* Mengirimkan true jika P adalah pohon biner kosong */

boolean IsTreeOneElmt (BinTree P)
{
	return ((P != NilBT) && (Left(P) == NilBT) && (Right(P) == NilBT));
}
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */


/* *** Traversal *** */

void PrintTreeL (BinTree P, int h, int CLevel)
{
	// KAMUS
	int i;

		// ALGORITMA
		if (IsTreeEmpty(P))
		{
		}
		else
		{
			for (i = 1; i <= h*(CLevel-1); i++)
			{
				printf(" ");
			}
			printf("%s", NamaBT(Akar(P)));
			if (Unlocked(Akar(P)))
			{
				printf(" unlocked\n");
			}
			else
			{
				printf(" still locked\n");
			}
			for (i = 1; i <= h*(CLevel-1); i++)
			{
				printf(" ");
			}
			printf("%s\n\n", Deskripsi(Akar(P)));
			if (Left(P) != NilBT)
			{
				PrintTreeL(Left(P), h, CLevel+1);
			}
			if (Right(P) != NilBT)
			{
				PrintTreeL(Right(P), h, CLevel+1);
			}
		}
}

void PrintTree (BinTree P, int h)
{
	PrintTreeL(P, h, 1);
}
/* I.S. P terdefinisi, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
/* Contoh, jika h = 2:
1) Pohon preorder: (A()()) akan ditulis sbb:
A
2) Pohon preorder: (A(B()())(C()())) akan ditulis sbb:
A
  B
  C
3) Pohon preorder: (A(B(D()())())(C()(E()()))) akan ditulis sbb:
A
  B
    D
  C
    E
*/


/* *** Searching *** */

boolean SearchTree (BinTree P, infotypeBT X)
{
	// KAMUS


		// ALGORITMA
		if (IsTreeEmpty(P))
		{
			return (false);
		}
		else
		{
			if (NamaBT(Akar(P)) == NamaBT(X))
			{
				return (true);
			}
			else
			{
				return ((SearchTree(Left(P), X)) || (SearchTree(Right(P), X)));
			}
		}
}
/* Mengirimkan true jika ada node dari P yang bernilai X */


/* *** Fungsi-Fungsi Lain *** */

int NbElmt (BinTree P)
{
	// KAMUS


		// ALGORITMA
		if (IsTreeEmpty(P))
		{
			return (0);
		}
		else
		{
			return (1 + NbElmt(Left(P)) + NbElmt(Right(P)));
		}
}
/* Mengirimkan banyaknya elemen (node) pohon biner P */

int Level (BinTree P, infotypeBT X)
{
	// KAMUS


		// ALGORITMA
		if (SearchTree(P, X))
		{
			if (IsTreeOneElmt(P))
			{
				return 1;
			}
			else
			{
				return (1 + Level(Left(P), X) + Level(Right(P), X));
			}
		}
		else
		{
			return 0;
		}
}
/* Mengirimkan level dari node X yang merupakan salah satu simpul dari pohon biner P.
   Akar(P) level-nya adalah 1. Pohon P tidak kosong dan elemen-elemennya unik. */
