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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../ADT/General/general.h"
#include "../../ADT/Waktu/waktu.h"
#include "../../ADT/Save_Index/saveindex.h"
#include "../../Modul/Save_Load/saveload.h"
#include "../../Modul/Skill_Tree/skilltree.h"

// Prosedur penampung; menyimpan semua data
void Save (Player player, int nMedLeft, Koneksi con, int nCurrMap, POINT posP, POINT posB, TabEnemyMap tabEnemy, BinTree skillTree, ListLR acquiredSkill) {
/*	Prosedur menerima seluruh data yang ingin disimpan, lalu menyimpannya dalam bentuk text pada path "/save/<nama>.sav"
 *	I.S. 	Seluruh parameter terdefinisi
 *	F.S.	File dengan path "/save/<nama>.sav" dibuat (jika belum ada) atau ditimpa (jika sudah ada) dengan data save terbaru */
	// KAMUS
	FILE* save;
	char* filename, treeString;
	WAKTU currWaktu = GetCurrWAKTU();
	SaveFileIndex saveFileIndex;

	// ALGORITMA
	filename = ConcatString(ConcatString("../../src/File_Eksternal/save/",NAMA(player)),".sav");
	save = fopen(filename,"w");

	// Save nama dan waktu penyimpanan
	fprintf(save,"\"%s\"\n",NAMA(player));
	fprintf(save,"%d %d %d ", Year(currWaktu), Month(currWaktu), Day(currWaktu));
	fprintf(save,"%d %d %d  \n", Hour(currWaktu), Minute(currWaktu), Second(currWaktu));

	// Save data player
	PrintPlayerToFile(save,player,nMedLeft);
	fprintf(save,"\n");

	// Save Map
	PrintMapToFile(save,con,nCurrMap,posP,posB);
	fprintf(save,"\n");

	// Save Enemy Data
	PrintEnemyDataToFile(save,tabEnemy);
	fprintf(save,"\n");

	// Save Acquired Skill
	while (acquiredSkill != Nil) {
		fprintf(save,"\"");
		PrintTreeToFile(save,Info(acquiredSkill));
		fprintf(save,"\" \n");
		acquiredSkill = Next(acquiredSkill);
	}
	fprintf(save,"#  \n");

	// Terminasi
	fprintf(save,"|");
	fclose(save);

	// Update Index
	ReadSaveFileIndex(&saveFileIndex);
	UpdateSaveFileIndex(&saveFileIndex,NAMA(player),currWaktu);
	WriteSaveFileIndex(saveFileIndex);
}


// Prosedur untuk menyimpan data tertentu
void PrintPlayerToFile (FILE* file, Player player, int nMedLeft) {
/*	Prosedur mencetak data player pada file yang dispesifikasi
 *	I.S.	file terdefinisi dan sudah dibuka sebelumnya pada mode penulisan, player dan nMedLeft terdefinisi
 *	F.S.	Data player ditulis pada file */
	// ALGORITMA
	fprintf(file,"\"%s\"\n",NAMA(player));
	fprintf(file,"%d %d  \n",LV(player),HP(player));
	fprintf(file,"%d %d %d  \n",STR(player),DEF(player),LUC(player));
	fprintf(file,"%d %d %d %d  \n",EXP(player),AP(player),SP(player),nMedLeft);
}
void PrintMapToFile (FILE* file, Koneksi con, int nCurrMap, POINT posP, POINT posB) {
/*	Prosedur mencetak data map pada file yang dispesifikasi
 *	I.S.	file terdefinisi dan sudah dibuka sebelumnya pada mode penulisan, sisa parameter terdefinisi
 *	F.S.	Data map ditulis pada file */
	// ALGORITMA
	for (int i = 1; i <= con.Length; i++) {
		fprintf(file,"%d %d  \n", con.Pilihan[i].Arah, con.Pilihan[i].NomorMap);
	}
	fprintf(file,"#  \n");
	fprintf(file,"%d  \n", nCurrMap);
	fprintf(file,"%d %d  \n", Absis(posP), Ordinat(posP));
	fprintf(file,"%d %d  \n\n", Absis(posB), Ordinat(posB));
}
void PrintEnemyDataToFile (FILE* file, TabEnemyMap tabEnemy) {
/*	Prosedur mencetak data assignment musuh pada file yang dispesifikasi
 *	I.S.	file terdefinisi dan sudah dibuka sebelumnya pada mode penulisan, sisa parameter terdefinisi
 *	F.S.	Data assignment musuh ditulis pada file */
	// ALGORITMA
	for (int i = 1; i <= LengthTabMap(tabEnemy); i++) {
		for (int j = 1; j <= LengthTabArea(tabEnemy,i); j++) {
			fprintf(file,"%d %d \"%s\" ", Absis(Pos(tabEnemy,i,j)), Ordinat(Pos(tabEnemy,i,j)), Name(tabEnemy,i,j));
		}
		fprintf(file,";  \n");
	}
	fprintf(file,"#  \n");
}
void PrintTreeToFile (FILE* file, BinTree P) {
/*	Prosedur mencetak elemen ID dan Unlocked dari simpul pohon biner P pada file secara preorder
 *	I.S.	file terdefinisi dan sudah dibuka sebelumnya pada mode penulisan, P terdefinisi
 *	F.S.	Data pohon biner P dicetak pada file */
	// ALGORITMA
	fprintf(file,"(");
	if (IsTreeEmpty(P)) {	// Basis 0
		// Do nothing
	} else {	// Rekurens
		fprintf(file,"%d %d",ID(Akar(P)),Unlocked(Akar(P)));
		PrintTreeToFile(file,Left(P));
		PrintTreeToFile(file,Right(P));
	}
	fprintf(file,")");
}

// Prosedur untuk meload semua data
void Load (char* name, Player *player, int *nMedLeft, Koneksi *con, int *nCurrMap, POINT *posP, POINT *posB, TabEnemyMap *tabEnemy, ListLR *acquiredSkill) {
/*	Prosedur menerima data player yang hendak diload,
 *	kemudian membaca data dalam file "./save/<nama>.sav" dan mengembalikan dalam parameter keluaran
 *	I.S.	name terdefinisi, file dengan path ./save/<nama>.sav ada dan telah diisi dengan format yang benar
 * 	F.S.	seluruh data pada file dikembalikan dalam parameter keluaran */
	// KAMUS
	char* filename = (char*) malloc ((LengthString(NAMA(*player))+9)*sizeof(char));
	char* treeString[10];
	BinTree skillTree;
	int i, j, k;

	// ALGORITMA
	// Inisialisasi
	filename = ConcatString(ConcatString("save/",name),".sav");
	STARTKATA(filename);

	// Skip bacaan waktu
	for (i = 1; i <= 7; i++)
		ADVKATA();

	// Load Player
	CopyKataToString(CKata,NAMA(*player));
	ADVKATA();
	LV(*player) = KataToInt(CKata);
	ADVKATA();
	HP(*player) = KataToInt(CKata);
	ADVKATA();
	STR(*player) = KataToInt(CKata);
	ADVKATA();
	DEF(*player) = KataToInt(CKata);
	ADVKATA();
	LUC(*player) = KataToInt(CKata);
	ADVKATA();
	EXP(*player) = KataToInt(CKata);
	ADVKATA();
	AP(*player) = KataToInt(CKata);
	ADVKATA();
	SP(*player) = KataToInt(CKata);
	ADVKATA();
	*nMedLeft = KataToInt(CKata);
	ADVKATA();

	// Load Map
	i = 0;
	while (CKata.TabKata[1] != '#') {
		i++;
		con->Pilihan[i].Arah = KataToInt(CKata);
		ADVKATA();
		con->Pilihan[i].NomorMap = KataToInt(CKata);
		ADVKATA();
	}
	con->Length = i;
	ADVKATA();
	*nCurrMap = KataToInt(CKata);
	ADVKATA();
	Absis(*posP) = KataToInt(CKata);
	ADVKATA();
	Ordinat(*posP) = KataToInt(CKata);
	ADVKATA();
	Absis(*posB) = KataToInt(CKata);
	ADVKATA();
	Ordinat(*posB) = KataToInt(CKata);
	ADVKATA();

	// Load Enemy Data
	i = 0;
	while (CKata.TabKata[1] != '#') {
		i++;
		j = 0;
		while (CKata.TabKata[1] != ';') {
			j++;
			Absis(Pos(*tabEnemy,i,j)) = KataToInt(CKata);
			ADVKATA();
			Ordinat(Pos(*tabEnemy,i,j)) = KataToInt(CKata);
			ADVKATA();
			CopyKataToString(CKata,Name(*tabEnemy,i,j));
			ADVKATA();
		}
		LengthTabArea(*tabEnemy,i) = j;
		ADVKATA();
	}
	LengthTabMap(*tabEnemy) = i;
	ADVKATA();

	// Load Skill Tree
	i = 0;
	while (CKata.TabKata[1] != '#') {
		i++;
		treeString[i] = (char*) malloc (80*sizeof(char));
		CopyKataToString(CKata,treeString[i]);
		ADVKATA();
	}
	ADVKATA();
	*acquiredSkill = Nil;
	for (j = i; j > 0; j--) {
		k = 0;
		RebuildTreeFromString(&skillTree,treeString[j],&k);
		*acquiredSkill = Konso(skillTree,*acquiredSkill);
	}
}

void RebuildTreeFromString (BinTree *T, char *st, int *idx)
/* 	Prosedur membangun binary tree berdasarkan string masukan
 *	I.S.	st[*idx]==‘('
 *	F.S.	T terdefinisi
 *	Proses : Membaca string st dan membangun pohon secara rekursif  */
{	/* Kamus Lokal */
	int id;
	infotypeBT skill;

	/* Algoritma */
	(*idx)++;                           /* advance */
	if (st[*idx]==')')	/* Basis : pohon kosong */
		(*T)=Nil;
	else {              /* Rekurens */
		for (id = 0; st[*idx] != ' '; (*idx)++) {
			id *= 10;
			id += (int) st[*idx] - (int) '0';
		}
		switch (id) {
			case 1: skill = CreateSkillPassive(SkillLevel3, DeskripsiSkillLevel3, id); break;
			case 2: skill = CreateSkillPassive(SkillLevel51, DeskripsiSkillLevel51, id); break;
			case 3: skill = CreateSkillPassive(SkillLevel52, DeskripsiSkillLevel52, id); break;
			case 4: skill = CreateSkillActive(SkillLevel71, DeskripsiSkillLevel71, id); break;
			case 5: skill = CreateSkillActive(SkillLevel72, DeskripsiSkillLevel72, id); break;
			case 6: skill = CreateSkillPassive(SkillLevel101, DeskripsiSkillLevel101, id); break;
			case 7: skill = CreateSkillPassive(SkillLevel102, DeskripsiSkillLevel102, id); break;
			case 8: skill = CreateSkillPassive(SkillLevel103, DeskripsiSkillLevel103, id); break;
			case 9: skill = CreateSkillPassive(SkillLevel104, DeskripsiSkillLevel104, id); break;
		}
		while (st[*idx] == ' ') (*idx)++;
		Unlocked(skill) = (st[*idx] == '1');

		(*T) = AlokNode(skill);
		(*idx)++;                         /* advance */
		RebuildTreeFromString(&Left(*T),st,idx);
		RebuildTreeFromString(&Right(*T),st,idx);
	}
	(*idx)++;                           /* advance */
}
