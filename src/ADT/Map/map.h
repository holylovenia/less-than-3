#ifndef map_H
#define map_H

#include "../Graf/grafarea.h"

/* Definisi Type Data */
typedef struct {
	int Arah;
	int NomorMap;
} Pilih;
typedef struct {
	Pilih Pilihan[50];
	int Length;
} Koneksi;

typedef struct {
	POINT PositionEnemy[MaxEnemy+1];
	int Length;
} POINTOFENEMY;

/* Selektor */
#define Pilihan(K) (K).Pilihan
#define LengthKoneksi(K) (K).Length
#define LengthPOINTOFENEMY(E) (E).Length
#define PositionEnemy(E) (E).PositionEnemy
#define Arah(P) (P).Arah
#define NomorMap(P) (P).NomorMap
#define GridX 10
#define GridY 10
/* Algoritma */


void HapusGate(addressarea *P);
/*  I.S : P terdefinisi, P dapat berisi nilai Nil
    F.S : Setiap node yang tidak memiliki koneksi, gate akan dihapus
    Setiap node akan dikunjungi dan akan dicek apakah setiap gate akan memiliki addressarea Neighbor
		yang berkorenspodensi dengannya, jika tidak maka gate akan dihapus, jika berisi suatu
    addressarea maka node tersebut akan dikunjungi untuk dicek lagi jika belum pernah
    dikunjungi sebelumnya
*/

void DealokasiMap(addressarea *P);
/*
  I.S : P terdefinisi, P dapat berisi nilai Nil
  F.S : Semua nilai visited dari P diset false dan setiap addressarea area akan didealokasi
*/
//void GetMapAddressFromIndex(int nCurrMap, addressarea *currMap);
void SetAllVisitedAreaToFalse(addressarea *P);
void GetMapAddressFromIndex(int nCurrMap, addressarea mapAddr, addressarea *currMap);
/*  I.S : P terdefinisi (dapat bernilai Nil), currMap bernilai nil
    F.S : currMap berisi alamat area dengan indeks nCurrMap. Jika tidak ada, *currMap tetap bernilai nil
*/
void LoadEnemy(POINTOFENEMY PosEnemy[MaxMap+1], infotypemap *X);
/*
  I.S : X terdefinisi dan array PosEnemy berisi setiap koordinat musuh di suatu map
  F.S : Map dari infotypemap akan dirubah kembali posisi musuhnya sehingga menjadi seperti awalnya
				yaitu enemy dapat respawn kembali
*/
void SaveEnemyPoint(MATRIKS A[MaxMap+1], POINTOFENEMY *PosEnemy);
/*
    I.S : A adalah array of area yang terdefinisi dan tidak kosong
    F.S : Setiap posisi musuh di suatu map akan di catat dan di simpan di array of Point PosEnemy
*/

void Baca_Area(MATRIKS *A);
/*
  I.S : Matriks A terdefinisi
  F.S : Matriks A berisi semua area yang telah dibaca dari file eksternal
*/
void EmptyGateInfo(infotypemap *X);
/* I.S : X terdefinisi
   F.S : Nilai yang berhubungan dengan Gate akan diassign menjadi Point(0,0).
*/
void SearchGateCopyMatrix(infotypemap *X,MATRIKS A[MaxMap+1], int arrrandomnumber[MaxMap+1]);
/*
  Mencari setiap koordinat gate dari masing - masing area dan mencopy matriks A ke matriks infotype X
  I.S : X berisi array of infotypemap yang kosong, A berisi array of area dimana area adalah matrix of char
        dan arrrandomnumber berisi bilangan random yang unik dan telah berisi nilai
  F.S : X berisi array of infotypemap yang setiap elemennya berisi area A[index] dimana setiap index diambil
        dari arrandomnumber[i]
*/
void LoadMap(ListArea *L, MATRIKS A[MaxMap+1], Koneksi Connection, POINT PBos);
/*
  I.S : ListArea L kosong, Connection berisi nilai koneksi, MATRIKS A[MaxMap+1] akan berisi semua area yang dibaca dari file eksternal
				dan berisi koordinat dari bos pada map yang paling jauh
  F.S : Akan terbentuk map yang sama dari parameter input connection
  Koneksi Connection akan dibaca dan dari koneksi tersebut akan digenerate map yang sama dengan
  yang tertulis di koneksi
*/

void Init_List(ListArea *L, MATRIKS A[11], Koneksi *Con, POINT *PosB);
/*  I.S : ListArea L memiliki nilai Nil
    F.S : Terbentuk peta yang saling terhubung dari setiap node yang memiliki area
          yang diambil dari array of matriks A
*/
void PlaceMedicine(int N, MATRIKS A[MaxMap+1]);
/*
	I.S : array of matriks A terdefinisi, N menandakan berapa medicine yang ingin ditaruh pada area acak yang dipilih dari
				array of matriks A indeks acak
	F.S : array of matriks A akan berisi N medicine
*/

void PlaceBoss(MATRIKS *M, POINT *Position);
/* Menaruh bos di area acak kecuali yang pertama
   I.S : M terdefinisi
   F.S : Matriks M dengan nilai titik random akan diganti menjadi karakter 'B'
*/
POINT Random_Pos_Player(MATRIKS M);
/*
  Menghasilkan Posisi Random Player saat di awal permainan dengan beberapa constraint
  I.S : Matriks M terdefinisi dan tidak kosong
  F.S : Menghasilkan posisi random untuk player dimana di point tersebut tidak terdapat simbol 'E', simbol 'M'
        ataupun simbol '#'
*/

void InitializeNewMap(ListArea *listArea, MATRIKS *area, int nMedLeft, POINT *posP, POINT *posB, POINTOFENEMY *enemyLoc, addressarea *currMap);
/*
	Berguna saat new game penyesuaian terhadap main program
*/
#endif
