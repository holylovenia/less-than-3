// Deskripsi: Modifikasi ADT Mesin Karakter dan ADT Mesin Kata V1 untuk membaca data lawan dari file eksternal


#ifndef __BASESTATS_H__
#define __BASESTATS_H__

#include "../Boolean/boolean.h"

#define NMaxNAMA 21
#define NMaxDESC 200

#define MaxElBST 40

typedef char NAMA[NMaxNAMA];
typedef struct {
	NAMA N;
	int BHP;
	int BSTR;
	int BDEF;
	int BLUC;
	int BEXP;
	char DESC[200];
	int SPRITE;
	boolean isBOSS;
} BST;

#define NAMA(E) (E).N
#define BHP(E) (E).BHP
#define BSTR(E) (E).BSTR
#define BDEF(E) (E).BDEF
#define BLUC(E) (E).BLUC
#define BEXP(E) (E).BEXP
#define DESC(E)	(E).DESC
#define SPRITE(E) (E).SPRITE
#define BISB(E) (E).isBOSS

/* Cara pemakaian:
	NAMA(E), BHP(E), ... mengakses komponen yang sudah dispesifikasi dalam struktur BST
*/

typedef struct {
	BST Base[MaxElBST+1];
	int NbElmt;
	int BossIndex;
} dbBST;

#define basestats(B,i) (B).Base[(i)]
#define dbBST_NbElmt(B) (B).NbElmt
#define dbBST_BossIndex(B) (B).BossIndex

/* Cara pemakaian:
	basestats(B,i) mengakses elemen ke-i dalam tabel base stats B
	dbBST_NbElmt(B) mengembalikan jumlah elemen dalam tabel base stats B
*/

void LoadBST(dbBST* Data);
/* Mengakuisisi seluruh data base stat dari file eksternal
	I.S. : Data sembarang, berkas dengan nama FILENAME terisi
	F.S. : Struktur data internal berisi seluruh data base stat yang didapat dari FILENAME */

int SearchBST(dbBST Data, char* Nama);
/* Fungsi mengembalikan INDEKS tabel data base stat yang komponen namanya berisi Nama */

#endif
