// Deskripsi: Definisi modul Save/Load; berisi prosedur dan fungsi untuk menulis dan membaca data permainan ke/dari file eksternal.


/*	FORMAT SAVEFILE:
nama
LV HP
STR DEF LUC
EXP AP SP nMedLeft

Koneksi ke-1
Koneksi ke-2
...
Koneksi ke-n
#
currMapIdx
PosP.X PosP.Y
PosB.X PosB.Y

acquiredSkill
#
|
*/

#ifndef __SAVELOAD_H__
#define __SAVELOAD_H__

#include "../../ADT/Character/character.h"
#include "../../ADT/List_Rekursif/listrek.h"
#include "../../ADT/Map/map.h"
#include "../../ADT/Assignment/assignment.h"
#include "../../ADT/Mesin_Kata/mesinkata.h"

// Prosedur penampung; menyimpan semua data
void Save (Player player, int nMedLeft, Koneksi con, int nCurrMap, POINT posP, POINT posB, TabEnemyMap tabEnemy, BinTree skillTree, ListLR acquiredSkill);
/*	Prosedur menerima seluruh data yang ingin disimpan, lalu menyimpannya dalam bentuk text pada path "/save/<nama>.sav"
 *	I.S. 	Seluruh parameter terdefinisi
 *	F.S.	File dengan path "/save/<nama>.sav" dibuat (jika belum ada) atau ditimpa (jika sudah ada) dengan data save terbaru */

// Prosedur untuk menyimpan data tertentu
void PrintPlayerToFile (FILE* file, Player player, int nMedLeft);
/*	Prosedur mencetak data player pada file yang dispesifikasi
 *	I.S.	file terdefinisi dan sudah dibuka sebelumnya pada mode penulisan, player dan nMedLeft terdefinisi
 *	F.S.	Data player ditulis pada file */
void PrintMapToFile (FILE* file, Koneksi con, int nCurrMap,  POINT posP, POINT posB);
/*	Prosedur mencetak data map pada file yang dispesifikasi
 *	I.S.	file terdefinisi dan sudah dibuka sebelumnya pada mode penulisan, sisa parameter terdefinisi
 *	F.S.	Data map ditulis pada file */
void PrintEnemyDataToFile (FILE* file, TabEnemyMap tabEnemy);
/*	Prosedur mencetak data assignment musuh pada file yang dispesifikasi
 *	I.S.	file terdefinisi dan sudah dibuka sebelumnya pada mode penulisan, sisa parameter terdefinisi
 *	F.S.	Data assignment musuh ditulis pada file */
void PrintTreeToFile(FILE* file, BinTree P);
/*	Prosedur mencetak elemen ID dan Unlocked dari simpul pohon biner P pada file secara preorder
 *	I.S.	file terdefinisi dan sudah dibuka sebelumnya pada mode penulisan, P terdefinisi
 *	F.S.	Data pohon biner P dicetak pada file */

// Prosedur untuk meload semua data
void Load (char* name, Player *player, int *nMedLeft, Koneksi *con, int *nCurrMap, POINT *posP, POINT *posB, TabEnemyMap *tabEnemy, ListLR *acquiredSkill);
/*	Prosedur menerima data player yang hendak diload,
 *	kemudian membaca data dalam file "./save/<nama>.sav" dan mengembalikan dalam parameter keluaran
 *	I.S.	name terdefinisi, file dengan path ./save/<nama>.sav ada dan telah diisi dengan format yang benar
 * 	F.S.	seluruh data pada file dikembalikan dalam parameter keluaran */

// Prosedur antara untuk Load
void RebuildTreeFromString (BinTree *T, char *st, int *idx);
/* 	Prosedur membangun binary tree berdasarkan string masukan
 *	I.S.	st[*idx]==‘('
 *	F.S.	T terdefinisi
 *	Proses : Membaca string st dan membangun pohon secara rekursif  */

#endif
