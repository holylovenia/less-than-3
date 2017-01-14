// Deskripsi: Implementasi ADT Save Index. ADT Save Index digunakan untuk membuat daftar save file yang ada.

#include <stdio.h>
#include "../General/general.h"
#include "../Mesin_Kata/mesinkata.h"
#include "../Save_Index/saveindex.h"

void WriteSaveFileIndex (SaveFileIndex saveFileIndex) {
/*	Prosedur menerima masukan SaveFileIndex dan menulisnya pada file "./save/__saveindex"
 *	I.S.	saveFileIndex terdefinisi
 *	F.S.	isi saveFileIndex dituliskan pada file "./save/__saveindex" */
	// KAMUS
	FILE* indexFile;

	// ALGORITMA
	indexFile = fopen("../../src/File_Eksternal/save/__saveindex","w");
	for (int i = 1; i <= NbSaves(saveFileIndex); i++) {
		fprintf(indexFile,"\"%s\" ", SaveName(saveFileIndex,i));
		fprintf(indexFile,"%d %d %d ", Year(SaveTime(saveFileIndex,i)), Month(SaveTime(saveFileIndex,i)), Day(SaveTime(saveFileIndex,i)));
		fprintf(indexFile,"%d %d %d  \n", Hour(SaveTime(saveFileIndex,i)), Minute(SaveTime(saveFileIndex,i)), Second(SaveTime(saveFileIndex,i)));
	}
	fprintf(indexFile,"|");
	fclose(indexFile);
}

void ReadSaveFileIndex (SaveFileIndex *saveFileIndex) {
/*	Prosedur membaca file "./save/__saveindex", lalu menyimpannya dalam saveFileIndex
 *	I.S.	file "./save/__saveindex" ada, berisi setidaknya guard '|' di akhir
 *	F.S.	data dari "./save/__saveindex" disimpan dalam saveFileIndex */
	// KAMUS
	int i = 0;
	//char* filename;
	//FILE* save;

	// ALGORITMA
	STARTKATA("save/__saveindex");
	while (!EndKata) {
		i++;
		CopyKataToString(CKata,SaveName(*saveFileIndex,i));
		ADVKATA();
		Year(SaveTime(*saveFileIndex,i)) = KataToInt(CKata);
		ADVKATA();
		Month(SaveTime(*saveFileIndex,i)) = KataToInt(CKata);
		ADVKATA();
		Day(SaveTime(*saveFileIndex,i)) = KataToInt(CKata);
		ADVKATA();
		Hour(SaveTime(*saveFileIndex,i)) = KataToInt(CKata);
		ADVKATA();
		Minute(SaveTime(*saveFileIndex,i)) = KataToInt(CKata);
		ADVKATA();
		Second(SaveTime(*saveFileIndex,i)) = KataToInt(CKata);
		ADVKATA();

		/*filename = (char*) malloc ((12+LengthString(SaveName(*saveFileIndex,i)))*sizeof(char));
		filename = ConcatString(ConcatString("./save/",SaveName(*saveFileIndex,i)),".sav");
		if ((save = fopen(filename,"r")) == NULL)
			i--;
		else
			fclose(save);*/

	}
	NbSaves(*saveFileIndex) = i;
}

int SearchSaveFileIndex (SaveFileIndex saveFileIndex, NAMA name) {
/*	Fungsi mengembalikan indeks saveFileIndex yang komponen namanya berisi name
 *	Fungsi mengembalikan 0 jika tidak ditemukan */
	// KAMUS
	int i;

	// ALGORITMA
	if (NbSaves(saveFileIndex) == 0) {
		return 0;
	} else {
		i = NbSaves(saveFileIndex);
		while ((i > 0) && CompareString(SaveName(saveFileIndex,i),name))
			i--;
		return i;
	}
}

void UpdateSaveFileIndex (SaveFileIndex *saveFileIndex, NAMA name, WAKTU time) {
/*	Prosedur menerima masukan saveFileIndex, lalu memperbaruinya dengan data masukan name dan time
 *	Jika sudah ada data yang berisi name di berkas, waktu lama ditimpa waktu masukan
 *	Jika tidak ada, data name dan time dimasukkan di akhir saveFileIndex
 *	I.S.	saveFileIndex dapat kosong, name dan time terdefinisi
 *	F.S.	saveFileIndex diperbarui dengan data masukan */
	// KAMUS
	int i = SearchSaveFileIndex(*saveFileIndex,name);

	// ALGORITMA
	if (i == 0){
		i = ++NbSaves(*saveFileIndex);
		CopyNama(name,SaveName(*saveFileIndex,i));
	}
	SaveTime(*saveFileIndex,i) = time;
}
