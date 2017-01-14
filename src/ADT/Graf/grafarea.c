#include "../Graf/grafarea.h"
#include <stdlib.h>
#include <stdio.h>


/* PROTOTYPE */
/****************** TEST ListArea KOSONG ******************/
boolean IsEmptyArea (ListArea L) {
/* Mengirim true jika ListArea kosong. Lihat definisi di atas. */
  return (FirstArea(L) == Nil);
}
/****************** PEMBUATAN ListArea KOSONG ******************/
void CreateEmptyArea (ListArea *L) {
/* I.S. L sembarang  */
/* F.S. Terbentuk ListArea kosong. Lihat definisi di atas. */
  FirstArea(*L) = Nil;
}
/****************** Manajemen Memori ******************/
addressarea AlokasiArea (infotypemap X) {
/* Mengirimkan addressarea hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressarea tidak nil. */
/* Misalnya: menghasilkan P, maka InfoMap(P)=X, Right(P)=Nil, Left(P)=Nil, Up(P)=Nil, Down(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
  addressarea P;
  int i;
  P = (addressarea) malloc (sizeof(ElmtListArea));
  if (P != Nil) {
    InfoMap(P) = X;
    for (i = 1; i<=MaxNeighbor; i++) {
      Neighbor(P)[i] = Nil;
    }
    Visited(P) = false;
  }
  return P;
}
void DealokasiArea (addressarea P) {
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressarea P */
  free(P);
}
/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void SetFirstArea (ListArea *L, infotypemap X) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
  addressarea P;
  P = AlokasiArea(X);
  if (P!=Nil) {
    FirstArea(*L) = P;
  }
}

void SetArea(addressarea P1, addressarea *P2, int N) {
/* I.S. L tidak kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen X di kiri ListArea sehingga Neighbor(*P2)[N] = P1 */
  Neighbor(*P2)[N] = P1;
}
