// Deskripsi: Implementasi ADT Save Index. ADT Save Index digunakan untuk membuat daftar save file yang ada.
#ifndef __SAVEINDEX_H__
#define __SAVEINDEX_H__

#define MaxSave 30

#include "../Waktu/waktu.h"
#include "../Character/character.h"

typedef struct {
	NAMA Name;
	WAKTU SaveTime;
} SaveFileData;
typedef struct {
	SaveFileData Data[MaxSave+1];
	unsigned int Length;
} SaveFileIndex;

#define NbSaves(S) (S).Length
#define SaveName(S,i) (S).Data[i].Name
#define SaveTime(S,i) (S).Data[i].SaveTime

void WriteSaveFileIndex (SaveFileIndex saveFileIndex) ;
/*	Prosedur menerima masukan SaveFileIndex dan menulisnya pada file "./save/__saveindex"
 *	I.S.	saveFileIndex terdefinisi
 *	F.S.	isi saveFileIndex dituliskan pada file "./save/__saveindex" */

void ReadSaveFileIndex (SaveFileIndex *saveFileIndex) ;
/*	Prosedur membaca file "./save/__saveindex", lalu menyimpannya dalam saveFileIndex
 *	I.S.	file "./save/__saveindex" ada, berisi setidaknya guard '|' di akhir
 *	F.S.	data dari "./save/__saveindex" disimpan dalam saveFileIndex */

int SearchSaveFileIndex (SaveFileIndex saveFileIndex, NAMA name) ;
/*	Fungsi mengembalikan indeks saveFileIndex yang komponen namanya berisi name
 *	Fungsi mengembalikan 0 jika tidak ditemukan */

void UpdateSaveFileIndex (SaveFileIndex *saveFileIndex, NAMA name, WAKTU time) ;
/*	Prosedur menerima masukan saveFileIndex, lalu memperbaruinya dengan data masukan name dan time
 *	Jika sudah ada data yang berisi name di berkas, waktu lama ditimpa waktu masukan
 *	Jika tidak ada, data name dan time dimasukkan di akhir saveFileIndex
 *	I.S.	saveFileIndex dapat kosong, name dan time terdefinisi
 *	F.S.	saveFileIndex diperbarui dengan data masukan */

#endif
