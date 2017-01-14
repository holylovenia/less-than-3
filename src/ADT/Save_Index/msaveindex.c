// Deskripsi: Driver ADT Save Index. ADT Save Index digunakan untuk membuat daftar save file yang ada.
// Kompilasi: gcc msaveindex.c saveindex.c waktu.c general.c mesinkata.c mesinkar.c -std=gnu99 -o msaveindex.exe

#include <stdio.h>
#include "../Character/character.h"
#include "../Waktu/waktu.h"
#include "../Save_Index/saveindex.h"

int main () {
	// KAMUS
	int i;
	SaveFileIndex saveFileIndex;
	NAMA name = "TEST";
	WAKTU now = GetCurrWAKTU();


	// ALGORITMA
	// Test ReadSaveFileIndex
	ReadSaveFileIndex(&saveFileIndex);
	printf("Pembacaan awal:\n");
	for (i = 1; i <= NbSaves(saveFileIndex); i++) {
		printf("\"%s\" ", SaveName(saveFileIndex,i));
		printf("%d %d %d ", Year(SaveTime(saveFileIndex,i)), Month(SaveTime(saveFileIndex,i)), Day(SaveTime(saveFileIndex,i)));
		printf("%d %d %d  \n", Hour(SaveTime(saveFileIndex,i)), Minute(SaveTime(saveFileIndex,i)), Second(SaveTime(saveFileIndex,i)));
	}

	// Test UpdateSaveFileIndex
	UpdateSaveFileIndex(&saveFileIndex,name,now);
	printf("Test update:\n");
	for (i = 1; i <= NbSaves(saveFileIndex); i++) {
		printf("\"%s\" ", SaveName(saveFileIndex,i));
		printf("%d %d %d ", Year(SaveTime(saveFileIndex,i)), Month(SaveTime(saveFileIndex,i)), Day(SaveTime(saveFileIndex,i)));
		printf("%d %d %d  \n", Hour(SaveTime(saveFileIndex,i)), Minute(SaveTime(saveFileIndex,i)), Second(SaveTime(saveFileIndex,i)));
	}

	// Test SearchSaveFileIndex
	i = SearchSaveFileIndex(saveFileIndex,name);
	printf("%s ada di indeks %d\n",name,i);

	// Test WriteSaveFileIndex
	WriteSaveFileIndex(saveFileIndex);
	// Lihat /save/__saveindex dengan text editor
}
