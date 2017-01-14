/* File: bintree.h */
/* ADT Pohon Biner */
/* Implementasi dengan menggunakan pointer */
/* Penamaan type infotypeBT, type addrNode, dan beberapa fungsi disesuaikan */

#ifndef _BINTREE_H_
#define _BINTREE_H_

#include "../Boolean/boolean.h"


/* *** Definisi Type Pohon Biner *** */
#define MaxNama 30 // Jumlah karakter maksimal untuk nama skill
#define MaxDeskripsi 300 // Jumlah karakter maksimal untuk deskripsi skill
#define NilBT NULL

typedef char StringNama [MaxNama];
typedef char StringDeskripsi [MaxDeskripsi];

typedef struct{
  boolean Unlocked;
  boolean IsPassive;
  StringNama NamaBT;
  StringDeskripsi DeskripsiBT;
  int IdentityBT;
} infotypeBT;

typedef struct tNode *addrNode;
typedef struct tNode {
	infotypeBT info;
	addrNode left;
	addrNode right;
} Node;

/* Definisi PohonBiner : */
/* Pohon Biner kosong : P = Nil */
typedef addrNode BinTree;

/* *** PROTOTYPE *** */

/* *** Selektor *** */
#define Akar(P) (P)->info
#define Left(P) (P)->left
#define Right(P) (P)->right
#define Unlocked(info) (info).Unlocked
#define NamaBT(info) (info).NamaBT
#define Deskripsi(info) (info).DeskripsiBT
#define IsPassive(info) (info).IsPassive
#define ID(info) (info).IdentityBT

/* *** Konstruktor *** */
void CreateEmptyTree(BinTree *P);
/* Menghasilkan Tree kosong dimana P = NilBT */

BinTree Tree (infotypeBT Akar, BinTree L, BinTree R);
/* Menghasilkan sebuah pohon biner dari A, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */

/* Manajemen Memory */
addrNode AlokNode (infotypeBT X);
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P,
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokNode (addrNode P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */

/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty (BinTree P);
/* Mengirimkan true jika P adalah pohon biner kosong */
boolean IsTreeOneElmt (BinTree P);
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */

/* *** Searching *** */
boolean SearchTree (BinTree P, infotypeBT X);
/* Mengirimkan true jika ada node dari P yang bernilai X */

/* *** Traversal *** */
void PrintTreeL (BinTree P, int h, int CLevel);
void PrintTree (BinTree P, int h);
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

/* *** Fungsi-Fungsi Lain *** */
int NbElmt (BinTree P);
/* Mengirimkan banyaknya elemen (node) pohon biner P */
int Level (BinTree P, infotypeBT X);
/* Mengirimkan level dari node X yang merupakan salah satu simpul dari pohon biner P.
   Akar(P) level-nya adalah 1. Pohon P tidak kosong dan elemen-elemennya unik. */

#endif
