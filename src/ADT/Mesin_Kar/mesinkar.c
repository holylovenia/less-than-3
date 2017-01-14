/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include "../Mesin_Kar/mesinkar.h"
#include <stdio.h>
#include <stdlib.h>

char CC;
boolean EOP;

static FILE * pita;
static int retval;

void STARTUI() {
/* Prosedur ini berguna untuk menstart pembacaan input dari pengguna */
	ADVUI();
}
void ADVUI() {
/* Prosedur ini berguna dalam pembacaan input dari pengguna */
	scanf("%c",&CC);
	EOP = (CC == '\n');
}
void START(char* import) {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	char* path = (char *) malloc((LengthString(import)+25)*sizeof(char));
	CopyNama("../../src/File_Eksternal/",path);
	path = ConcatString(path,import);
	pita = fopen(path,"r");
	ADV();
}

void ADV() {
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela =
          CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = MARK.
		  Jika  CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	retval = fscanf(pita,"%c",&CC);
	EOP = (CC == MARK);
	if (EOP) {
    fclose(pita);
 	}
}
