/* File: listrek.h */
/* ADT list linier dengan representasi pointer */
/* Implementasi list linier secara rekursif dengan binary tree sebagai infonya */

#ifndef _ListREK_H_
#define _ListREK_H_

#include "../Boolean/boolean.h"
#include "../Binary_Tree/bintree.h"

#define NilLR NULL

/* Definisi Type */
typedef struct tElmtListLR *address;
typedef struct tElmtListLR {
	BinTree infoLR;
	address next;
} ElmtListLR;

/* Definisi ListLR : */
/* ListLR kosong : L = NilLR */
typedef address ListLR;

/* Deklarasi  nama untuk variabel kerja */
/*  	L : ListLR */
/*  	P : address 	*/
/* Maka penulisan First(L) menjadi L */
/*                P.info menjadi Info(P); P.next menjadi Next(P) */

/* Selektor */
#define Info(P) (P)->infoLR
#define Next(P) (P)->next

/* *** Manajemen Memori *** */
address AlokasiLR (BinTree X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak NilLR, dan misalnya menghasilkan P,
  maka Info(P) = X, Next(P) = NilLR */
/* Jika alokasi gagal, mengirimkan NilLR */
void DealokasiLR (address P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/* *** Primitif-primitif yang harus direalisasikan *** */

/* Pemeriksaan Kondisi ListLR */
int IsEmptyLR(ListLR L);
/* Mengirimkan 1 jika L kosong dan 0 jika L tidak kosong */
int IsOneElmtLR(ListLR L);
/* Mengirimkan 1 jika L berisi 1 elemen dan 0 jika > 1 elemen atau kosong */

/* *** Selektor *** */
BinTree FirstElmt (ListLR L);
/* Mengirimkan elemen pertama sebuah ListLR L yang tidak kosong */
ListLR TailLR(ListLR L);
/* Mengirimkan ListLR L tanpa elemen pertamanya, mungkin menjadi ListLR kosong */

/* *** Konstruktor *** */
ListLR Konso(BinTree e, ListLR L);
/* Mengirimkan ListLR L dengan tambahan e sebagai elemen pertamanya.
e dialokasi terlebih dahulu. Jika alokasi gagal, mengirimkan L. */
ListLR KonsB(ListLR L, BinTree e);
/* Mengirimkan ListLR L dengan tambahan e sebagai elemen pertamanya */
/* e harus dialokasi terlebih dahulu */
/* Jika alokasi e gagal, mengirimkan L */

/* *** Operasi Lain *** */
void PrintListLR (ListLR L);
/* I.S. L terdefinisi. */
/* F.S. Setiap elemen ListLR dicetak. */
int NbElmtListLR (ListLR L);
/* Mengirimkan banyaknya elemen ListLR L, Nol jika L kosong */
boolean SearchLR (ListLR L, BinTree X);
/* Mengirim true jika X adalah anggota ListLR, false jika tidak */

/*** Pencarian NilLRai ekstrim ***/
/* Prekondisi untuk Max/Min/Sum/Average : ListLR tidak kosong */
//BinTree MaxListLR (ListLR L);
/* Mengirimkan NilLRai info(P) yang maksimum */

//BinTree MinListLR (ListLR L);
/* Mengirimkan NilLRai info(P) yang minimum */

//BinTree SumListLR (ListLR L);
/* Mengirimkan total jumlah elemen ListLR L */

//float AverageListLR (ListLR L);
/* Mengirimkan NilLRai rata-rata elemen ListLR L */

#endif
