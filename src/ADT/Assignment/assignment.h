// Deskripsi: Definisi ADT Assignment. ADT Assignment berfungsi untuk mencari semua enemy dan medicine di map dan menghasilkan titik di mana musuh berada, musuh apa yang ada di sana, serta titik di mana obat berada

#ifndef __ASSIGNMENT_H__
#define __ASSIGNMENT_H__

#include "../Map/map.h"
#include "../Character/character.h"
#include "../Matriks/matriks.h"

typedef struct {
	POINT EnemyPos;
	NAMA EnemyName;
} ENEMYLOC;
typedef struct {
	ENEMYLOC Enemy[MaxEnemy+1];
	int Length;
} TabEnemyArea;
typedef struct {
	TabEnemyArea Area[MaxMap+1];
	int Length;
} TabEnemyMap;

#define Area(T,i) (T).Area[(i)]
#define Enemy(T,i,j) (T).Area[(i)].Enemy[(j)]
#define Pos(T,i,j) (T).Area[(i)].Enemy[(j)].EnemyPos
#define Name(T,i,j) (T).Area[(i)].Enemy[(j)].EnemyName
#define LengthTabMap(T) (T).Length
#define LengthTabArea(T,i) (T).Area[(i)].Length


void AssignEnemy(dbBST EnemyData, MATRIKS Map[MaxMap+1], TabEnemyMap *tabEnemy);
/*	Prosedur menerima masukan data musuh dan array of area, lalu mengembalikan tabEnemy yang berisi
 *	koordinat semua musuh dalam map serta nama musuh yang akan dilawan pada koordinat tersebut
 *	I.S : EnemyData dan Map terdefinisi
 *	F.S : tabEnemy terdefinisi */

#endif
