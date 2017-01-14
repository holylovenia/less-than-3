//Deskripsi : Kumpulan definisi fungsi dan prosedur untuk mengolah data angka

#ifndef STATISTIC_H
#define STATISTIC_H

#include "../../ADT/Basestats/basestats.h"
#include "../../ADT/Character/character.h"
#include "../../ADT/Boolean/boolean.h"


/*SELEKTOR PLAYER*/
int STRPlayer(Player P);
/*Fungsi menghasilkan STR Player berdasarkan Base Stats STR player*/
int DEFPlayer(Player P);
/*Fungsi menghasilkan DEF Player berdasarkan Base Stats DEF player*/
int LUCPlayer(Player P);
/*Fungsi menghasilkan LUC Player berdasarkan Base Stats LUC player*/
int HPMAXPlayer(Player P);
/*Fungsi menghasilkan HP maksimal Player berdasarkan Base Stats HP player*/
long int EXPLimit(Player P);
/*Fungsi menghasilkan EXP point yang harus dicapai player agar dapat naik ke level yang lebih tinggi*/
void GetEXP(Player *P, Enemy E);
/*I.S. P dan E terdefinisi*/
/*F.S. EXP Player ditambahkan dari BaseEXP musuh. Apabila EXP Player >= EXPLimit-nya, EXP Player akan dikurangi EXPLimit,
	LV otomatis naik 1 angka, mendapat tambahan attribute points sebesar 10 points, dan mendapat tambahan 1 skill point
	apabila LV(P) mod 2 = 1 dan LV(P) > 1 setiap kali EXP Player >= EXPLimit
	hingga akhirnya EXP Player < EXPLimit*/

/*SELEKTOR ENEMY*/
int STREnemy(Player P, Enemy E);
/*Fungsi menghasilkan STR Enemy berdasarkan Base Stats STR musuh*/
int DEFEnemy(Player P, Enemy E);
/*Fungsi menghasilkan DEF Enemy berdasarkan Base Stats DEF musuh*/
int LUCEnemy(Player P, Enemy E);
/*Fungsi menghasilkan LUC Enemy berdasarkan Base Stats LUC musuh*/
int HPMAXEnemy(Player P, Enemy E);
/*Fungsi menghasilkan HP maksimal Enemy berdasarkan Base Stats HP musuh*/

/*Generator float number*/
void randomnumbermod (float *mod);
/*I.S. mod terdefinisi*/
/*F.S. mod menghasilkan suatu bilangan real dengan range 0 sampai 100 yang nantinya akan diolah untuk menentukan
apakah serangan critical atau tidak*/

/*Peluang Critical Hit player dengan enemy*/
float CritChancePlayer(Player P);
/*Fungsi menghasilkan peluang Player melakukan serangan critical dari LUCPlayer*/
float CritChanceEnemy(Player P, Enemy E);
/*Fungsi menghasilkan peluang musuh melakukan serangan critical dari LUCEnemy*/

/*Fungsi Critical (0 = tidak critical, 1 = critical)*/
int IsCritPlayer(Player P);
/*Fungsi menghasilkan apakah serangan yang dilakukan Player critical atau tidak dengan menggunakan generator mod*/
int IsCritEnemy(Player P, Enemy E);
/*Fungsi menghasilkan apakah serangan yang dilakukan musuh critical atau tidak dengan menggunakan generator mod*/

/*Generator random damage*/
void randomdamagemod (float *mod);
/*I.S. mod terdefinisi*/
/*F.S. mod menghasilkan suatu konstanta sebagai bilangan pengali dengan nilai
konstanta antara 0.85 hingga 1.15*/

/*Final damage yang dihasilkan player ataupun enemy*/
int DamagePlayer(Player P, Enemy E);
/*Fungsi menghasilkan damage yang dihasilkan Player setelah melakukan serangan musuh*/
int DamageEnemy(Player P, Enemy E);
/*Fungsi menghasilkan damage yang dihasilkan musuh setelah melakukan serangan Player*/

void PlayerCreation (Player *P);
/*I.S. P terdefinisi*/
/*F.S. Attribute Point Player berkurang atau sama dengan sebelumnya. Attribute point
dialokasikan untuk menambah base stats player itu sendiri*/
#endif
