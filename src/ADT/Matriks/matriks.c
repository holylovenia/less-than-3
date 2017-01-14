#include <stdio.h>
#include "../Matriks/matriks.h"


void MakeMATRIKS (int NB, int NK, MATRIKS * M) {
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
	NBrsEff(*M) = NB;
	NKolEff(*M) = NK;
}


/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M) {
/* Mengirimkan indeks baris terkecil M */
	return (BrsMin);
}
indeks GetFirstIdxKol (MATRIKS M) {
/* Mengirimkan indeks kolom terkecil M */
	return (KolMin);
}
indeks GetLastIdxBrs (MATRIKS M) {
/* Mengirimkan indeks baris terbesar M */
	return (NBrsEff(M));
}
indeks GetLastIdxKol (MATRIKS M) {
/* Mengirimkan indeks kolom terbesar M */
	return (NKolEff(M));
}
boolean IsIdxEff (MATRIKS M, indeks i, indeks j) {
/* Mengirimkan true jika i, j adakolMaxlah indeks efektif bagi M */
	return ( (i>=GetFirstIdxBrs(M)) && (i<=GetLastIdxBrs(M)) &&
			 (j>=GetFirstIdxKol(M)) && (j<=GetLastIdxKol(M)) );
}
/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl) {
/* Melakukan assignment MHsl  MIn */
	int i,j;
	MakeMATRIKS (NBrsEff(MIn) , NKolEff(MIn) , MHsl) ;
	for (i=GetFirstIdxBrs(MIn); i<=GetLastIdxBrs(MIn); i++) {
		for (j=GetFirstIdxKol(MIn); j<=GetLastIdxKol(MIn); j++) {
			Elmt(*MHsl,i,j) = Elmt(MIn,i,j);
		}
	}
}
void TulisMATRIKS (WINDOW* win, MATRIKS M, int Px, int Py) {
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

	for (i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++) {
		for (j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++) {
			if (i == Py && j == Px) {
				mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-5, " ");
				mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-4, " ");
				mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-3, " ");
				mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-5, "[");
				mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-4, "P");
				mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-3, "]");
			} else {
				if (Elmt(M, i, j) == '.') {
					mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-5, " ");
					mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-4, " ");
					mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-3, " ");
					mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-5, " ");
					mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-4, " ");
					mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-3, " ");
				}
				else if ((Elmt(M, i, j) == 'E') || (Elmt(M, i, j) == 'M')) {
					mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-5, " ");
					mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-4, " ");
					mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-3, " ");
					mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-5, " ");
					mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-4, "%c", Elmt(M, i, j));
					mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-3, " ");
				}
				else if (Elmt(M, i, j) == 'B') {
					mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-5, " ");
					mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-4, " ");
					mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-3, " ");
					mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-5, " ");
					mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-4, "Q");
					mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-3, " ");
				}
				else {
					mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-5, "%c", Elmt(M, i, j));
					mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-4, "%c", Elmt(M, i, j));
					mvwprintw(win, i*MapRowMultiplier-1, j*MapColumnMultiplier-3, "%c", Elmt(M, i, j));
					mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-5, "%c", Elmt(M, i, j));
					mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-4, "%c", Elmt(M, i, j));
					mvwprintw(win, i*MapRowMultiplier-2, j*MapColumnMultiplier-3, "%c", Elmt(M, i, j));
				}
			}

		}
	}
}
