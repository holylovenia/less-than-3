//Deskripsi : Header dari tipe bentukan player dan musuh

#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Basestats/basestats.h"
#include "../Boolean/boolean.h"

/* *** Definisi PLAYER dan STATS *** */
typedef char NAMA[21];
typedef int LV;
typedef int HP;
typedef int HPCurrent;
typedef int BaseHP;
typedef int EXP;
typedef int EXPGAIN;
typedef int AP;
typedef int SP;
typedef boolean ISBOSS;
typedef struct {
	int STR; /* Base Stats STR player / enemy dalam tipe stats */
	int DEF; /* Base Stats DEF player / enemy dalam tipe stats */
	int LUC; /* Base Stats LUC player / enemy dalam tipe stats */
} STATS;
typedef struct {
	NAMA N; /* Nama player max 20 karakter */
	LV L; /* Level player */
	HP H; /* Health point player dalam tipe integer */
	STATS S; /* Stats player */
	EXP X; /* EXP pemain player dalam tipe integer*/
	AP AP; /* Attribute point player dalam tipe integer*/
	SP SP; /* Skill point player dalam tipe integer */
} Player;
typedef struct {
	NAMA N; /* Nama player max 20 karakter */
	LV L; /* Level enemy */
	BaseHP BHP; /* BaseHP enemy dalam tipe integer */
	HP H; /* HP enemy dalam tipe integer */
	STATS S; /*Stats enemy */
	EXPGAIN XG; /* EXP yang didapat player apabila mengalahkan enemy tersebut dalam tipe integer */
	ISBOSS ISB; /* Boolean apakah enemy merupakan final boss atau bukan*/
    char Desc[200];
    int Sprite;
} Enemy;


/* *** Notasi Akses: selektor PLAYER dan ENEMY *** */
#define NAMA(E) (E).N
#define LV(E) (E).L
#define BaseHP(E) (E).BHP
#define HP(E) (E).H
#define STATS(E) (E).S
#define EXP(E) (E).X
#define AP(E) (E).AP
#define SP(E) (E).SP
#define Desc(E) (E).Desc
#define EXPGAIN(E) (E).XG
#define ISBOSS(E) (E).ISB
#define Sprite(E) (E).Sprite

/* *** Notasi Akses: selektor STATS *** */
#define STR(E) (E).S.STR
#define DEF(E) (E).S.DEF
#define LUC(E) (E).S.LUC

/* ********** KONSTRUKTOR ********** */

/* Konstruktor : create player awal */
void CreatePlayerAwal (Player *P, char* Nama);
/* I.S. Player *P terdefinisi
   F.S. Player *P terbentuk dengan nilai-nilai dalam tipe bentukan yang telah diatur, yaitu
   Nama player sesuai input pengguna, LV player = 1, STR, DEF, dan LUC = 50, EXP player = 0
   Attribute point awal = 10, Skill point awal = 0, dan HP yang telah disesuaikan sesuai leveln playernya */

/* Konstruktor : create enemy */
void CreateEnemy (Player P, Enemy *E, NAMA X, dbBST Data);
/* I.S. P, E, X, Data terdefinisi dan sembarang
   F.S. Enemy E terbentuk dengan nama enemy sesuai variabel X, LV Enemy = LV Player, BaseHP, STR, DEF, LUC
   EXPGAIN, ISBOSS sesuai angka yang terbaca pada file eksternal "enemy.txt", HP Enemy sesuai nilai yang dikembalikan
   dari fungsi HPMAXEnemy */

#endif
