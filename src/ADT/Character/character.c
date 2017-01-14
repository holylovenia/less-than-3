//Deskripsi : Implementasi fungsi dan prosedur dari header tipe bentukan player dan musuh

#include "../Boolean/boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../Basestats/basestats.h"
#include "../Character/character.h"
#include "../../Modul/Statistic/statistic.h"
#include "../General/general.h"
/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create player awal */
void CreatePlayerAwal (Player *P, char* Nama)
/* I.S. Player *P terdefinisi
   F.S. Player *P terbentuk dengan nilai-nilai dalam tipe bentukan yang telah diatur, yaitu
   Nama player sesuai input pengguna, LV player = 1, STR, DEF, dan LUC = 50, EXP player = 0
   Attribute point awal = 10, Skill point awal = 0, dan HP yang telah disesuaikan sesuai leveln playernya */
{
    CopyNama(Nama, NAMA(*P));
	LV(*P) = 1;
	STR(*P) = 50;
	DEF(*P) = 50;
	LUC(*P) = 50;
	EXP(*P) = 0;
	AP(*P) = 10;
	SP(*P) = 0;
    HP(*P) = HPMAXPlayer(*P);
}

/* Konstruktor : create enemy */
void CreateEnemy (Player P, Enemy *E, NAMA X, dbBST Data)
/* I.S. P, E, X, Data terdefinisi dan sembarang
   F.S. Enemy E terbentuk dengan nama enemy sesuai variabel X, LV Enemy = LV Player, BaseHP, STR, DEF, LUC
   EXPGAIN, ISBOSS sesuai angka yang terbaca pada file eksternal "enemy.txt", HP Enemy sesuai nilai yang dikembalikan
   dari fungsi HPMAXEnemy */
{
	CopyNama(X,NAMA(*E));
	LV(*E) = LV(P);
	BaseHP(*E) = BHP(basestats(Data,SearchBST(Data,X)));
	HP(*E) = HPMAXEnemy(P,*E);
	STR(*E) = BSTR(basestats(Data,SearchBST(Data,X)));
	DEF(*E) = BDEF(basestats(Data,SearchBST(Data,X)));
	LUC(*E) = BLUC(basestats(Data,SearchBST(Data,X)));
    EXPGAIN(*E) = BEXP(basestats(Data,SearchBST(Data,X)));
    ISBOSS(*E) = BISB(basestats(Data,SearchBST(Data,X)));
    CopyNama(DESC(basestats(Data, SearchBST(Data,X))), Desc(*E));
    Sprite(*E) = SPRITE(basestats(Data, SearchBST(Data,X)));
}
