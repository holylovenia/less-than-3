// NIM		: 13515065
// Nama		: Felix Limanta
// Tanggal	: 27 November 2016
// File		: massignment.c
// Topik	: Tugas Besar
// Deskripsi: Driver ADT Assignment. ADT Assignment berfungsi untuk mencari semua enemy dan medicine di map dan menghasilkan titik di mana musuh berada, musuh apa yang ada di sana, serta titik di mana obat berada
// Kompilasi: gcc massignment.c assignment.c map.c matriks.c basestats.c mesinkata.c mesinkar.c array.c point.c grafarea.c general.c -o massignment.exe

#include "../../ADT/Assignment/assignment.h"
#include <stdio.h>
#include "../../ADT/Map/map.h"
#include "../../ADT/Basestats/basestats.h"

void TulisMATRIKSTerminal (MATRIKS M, int Px, int Py);
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
#..
..#
###
*/


int main () {
	// KAMUS
	MATRIKS area[11];
	dbBST enemyData;
	TabEnemyMap tabEnemy;
	int i,j;

	// ALGORITMA
	Baca_Area(area);
	LoadBST(&enemyData);

	// Test AssignEnemy
	AssignEnemy(enemyData,area,&tabEnemy);
	for (i = 1; i <= LengthTabMap(tabEnemy); i++) {
		TulisMATRIKSTerminal(area[i],0,0);
		for (j = 1; j <= LengthTabArea(tabEnemy,i); j++) {
			printf("(%d,%d:%s)",Absis(Pos(tabEnemy,i,j)),Ordinat(Pos(tabEnemy,i,j)),Name(tabEnemy,i,j));
		}
		printf("\n");
	}
}


// Fungsi tambahan
void TulisMATRIKSTerminal (MATRIKS M, int Px, int Py) {
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
#..
..#
###
*/
	int i,j;
	for (j = GetFirstIdxKol(M); j<=GetLastIdxKol(M) + 2; j++) {
		printf("-");
	}
	printf("\n");
	for (i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++) {
		for (j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++) {
			if (j == 1) {
				printf("|");
			}
			if (i == Py && j == Px) {
				printf("P");
			} else {
				printf("%c", Elmt(M,i,j) );
			}
		}
		printf( "|\n");
	}
	for (j = GetFirstIdxKol(M); j<=GetLastIdxKol(M) + 2; j++) {
		printf("-");
	}
	printf("\n");
}
