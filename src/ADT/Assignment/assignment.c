// Deskripsi: Implementasi ADT Assignment. ADT Assignment berfungsi untuk mencari semua enemy dan medicine di map dan menghasilkan titik di mana musuh berada, musuh apa yang ada di sana, serta titik di mana obat berada

#include "../Basestats/basestats.h"
#include "../Array/array.h"
#include "../Assignment/assignment.h"
#include "../General/general.h"
#include <stdlib.h>
#include <stdio.h>

void AssignEnemy(dbBST EnemyData, MATRIKS Map[MaxMap+1], TabEnemyMap *tabEnemy)
/*	Prosedur menerima masukan data musuh dan array of area, lalu mengembalikan tabEnemy yang berisi
 *	koordinat semua musuh dalam map serta nama musuh yang akan dilawan pada koordinat tersebut
 *	I.S : EnemyData dan Map terdefinisi
 *	F.S : tabEnemy terdefinisi */
{
	// KAMUS
	int index, i, j, k = 0, l = 0;
	TabInt idxEnemyData;

	// ALGORITMA
	MakeEmptyTab(&idxEnemyData);
	for (i = 1; i <= dbBST_NbElmt(EnemyData); i++) {
		idxEnemyData.TI[i] = i;
	}
	Neff(idxEnemyData) = dbBST_NbElmt(EnemyData);
	ShuffleTab(&idxEnemyData);

	LengthTabMap(*tabEnemy) = 0;
	for (index = 1; index <= MaxMap; index++) {
		LengthTabMap(*tabEnemy)++;
		LengthTabArea(*tabEnemy,index) = 0;
		for (i = 1; i <= 10; i++) {
			for (j = 1; j <= 10; j++) {
				if (Elmt(Map[index],i,j) == 'E') {
					Pos(*tabEnemy,index,++LengthTabArea(*tabEnemy,index)) = MakePOINT(j,i);
					if (dbBST_BossIndex(EnemyData) == k) ++k;
					CopyNama(NAMA(basestats(EnemyData,ElmtTab(idxEnemyData,++k))),Name(*tabEnemy,index,LengthTabArea(*tabEnemy,index)));
					if (CompareString(Name(*tabEnemy,index,LengthTabArea(*tabEnemy,index)),"")==0)
						CopyNama(NAMA(basestats(EnemyData,ElmtTab(idxEnemyData,1))),Name(*tabEnemy,index,LengthTabArea(*tabEnemy,index)));
				} else if (Elmt(Map[index],i,j) == 'B') {
					Pos(*tabEnemy,index,++LengthTabArea(*tabEnemy,index)) = MakePOINT(j,i);
					CopyNama(NAMA(basestats(EnemyData,dbBST_BossIndex(EnemyData))),Name(*tabEnemy,index,LengthTabArea(*tabEnemy,index)));
				}
				if (k == Neff(idxEnemyData)) k = 1;
			}
		}
	}
}
