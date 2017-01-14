// Deskripsi: Modifikasi ADT Mesin Karakter dan ADT Mesin Kata V1 untuk membaca data base stats lawan dari file eksternal

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Basestats/basestats.h"
#include "../Mesin_Kar/mesinkar.h"
#include "../Mesin_Kata/mesinkata.h"

void LoadBST(dbBST* Data)
/* Mengakuisisi seluruh data base stat dari file eksternal
	I.S. : Data sembarang, berkas dengan nama FILENAME terisi
	F.S. : Data diisi seluruh data base stat yang didapat dari FILENAME */
{	// KAMUS
	int i = 0;

	// ALGORITMA
	STARTKATA("enemy.txt");
	while (!EndKata) {
		i++;
		CopyKataToString(CKata,NAMA(basestats(*Data,i)));
		ADVKATA();
		BHP(basestats(*Data,i)) = KataToInt(CKata);
		ADVKATA();
		BSTR(basestats(*Data,i)) = KataToInt(CKata);
		ADVKATA();
		BDEF(basestats(*Data,i)) = KataToInt(CKata);
		ADVKATA();
		BLUC(basestats(*Data,i)) = KataToInt(CKata);
		ADVKATA();
		BEXP(basestats(*Data,i)) = KataToInt(CKata);
		ADVKATA();
		CopyKataToString(CKata,DESC(basestats(*Data,i)));
		ADVKATA();
		SPRITE(basestats(*Data,i)) = KataToInt(CKata);
		ADVKATA();
		if (BISB(basestats(*Data,i)) = KataToInt(CKata))
			dbBST_BossIndex(*Data) = i;
		ADVKATA();
	}
	dbBST_NbElmt(*Data) = i;
}



int SearchBST(dbBST Data, char* Nama)
/* Fungsi mengembalikan indeks tabel data base stat yang komponen namanya berisi Nama */
{	// KAMUS
	int i = dbBST_NbElmt(Data);

	// ALGORITMA
	if (i != 0) {
		while ((i > 0) && (strcmp(Nama,NAMA(basestats(Data,i))) != 0)) i--;
	}
	return i;
}
