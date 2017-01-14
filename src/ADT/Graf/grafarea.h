/* ADT Graf */
/* Representasi berkait dengan addressarea adalah pointer */
/* infotypemap adalah matriks dan gate */

#ifndef grafarea_H
#define grafarea_H

#include "../Boolean/boolean.h"
#include "../Point/point.h"
#include "../Matriks/matriks.h"

#define Nil NULL
#define MaxNeighbor 4
#define MaxMap 10
#define MaxEnemy 4
#define GridX 10
#define GridY 10
/* Definisi Type Data */

typedef struct{
	MATRIKS MAP;
	POINT GateArrived[MaxNeighbor+1];
	POINT GateDepart[MaxNeighbor+1];
	int IndeksMap;
} infotypemap;
typedef struct tElmtlist *addressarea;
typedef struct tElmtlist {
	infotypemap infomap;
	addressarea Neighbor[MaxNeighbor+1];
	boolean visited;
} ElmtListArea;

typedef struct {
	addressarea FirstArea;
} ListArea;

/* Definisi ListArea : */
/* ListArea kosong : FirstArea(L) = Nil  */
/* Setiap elemen dengan addressarea P dapat diacu Neighbor(P) */

/* Notasi Akses */
#define InfoMap(P) 	(P)->infomap
#define Neighbor(P) (P)->Neighbor
#define Visited(P) (P)->visited
#define Map(P) 		(InfoMap(P)).MAP
#define MapInfo(X) (X).MAP
#define IndeksMap(X) (X).IndeksMap
#define GateArrived(X)		X.GateArrived
#define GateDepart(X)		X.GateDepart
#define ElmtGateArrived(X,i) (X).GateArrived[i]
#define ElmtGateDeparted(X,i) (X).GateDepart[i]
#define FirstArea(L)	((L).FirstArea)

/* PROTOTYPE */
/****************** TEST ListArea KOSONG ******************/
boolean IsEmptyArea (ListArea L);
/* Mengirim true jika ListArea kosong. Lihat definisi di atas. */

/****************** PEMBUATAN ListArea KOSONG ******************/
void CreateEmptyArea (ListArea *L);
/* I.S. L sembarang  */
/* F.S. Terbentuk ListArea kosong. Lihat definisi di atas. */

/****************** Manajemen Memori ******************/
addressarea AlokasiArea (infotypemap X);
/* Mengirimkan addressarea hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressarea tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Neighbor(P)[1]=Nil, Neighbor(P)[2]=Nil, Neighbor(P)[3]=Nil, Neighbor(P)[4]=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
void DealokasiArea (addressarea P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressarea P */


/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void SetArea(addressarea P1, addressarea *P2, int N);
/* I.S. L tidak kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen X di kiri ListArea sehingga Neighbor(*P2)[N] = P1 */

void SetFirstArea (ListArea *L, infotypemap X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */


#endif
