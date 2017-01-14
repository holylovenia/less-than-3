#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../../ADT/Basestats/basestats.h"
#include "../../ADT/Character/character.h"
#include "../../ADT/Boolean/boolean.h"
#include "../../Modul/Statistic/statistic.h"

/*SELEKTOR PLAYER*/
int STRPlayer(Player P)
/*Fungsi menghasilkan STR Player berdasarkan Base Stats STR player*/
{
	int S = ((2 * (40 + STR(P)) + 15) * LV(P) / 100) + 5;
	return S;
}
int DEFPlayer(Player P)
/*Fungsi menghasilkan DEF Player berdasarkan Base Stats DEF player*/
{
	int D = ((2 * (40 + DEF(P)) + 15) * LV(P) / 100) + 5;
	return D;
}
int LUCPlayer(Player P)
/*Fungsi menghasilkan LUC Player berdasarkan Base Stats LUC player*/
{
	int L = ((2 * (40 + LUC(P)) + 15) * LV(P) / 100) + 5;
	if (L > 40)
	{
		L = 40;
	} else if (L < 0)
	{
		L = 0;
	}
	return L;
}
int HPMAXPlayer(Player P)
/*Fungsi menghasilkan HP maksimal Player berdasarkan Base Stats HP player*/
{
	int H = 10 * LV(P) + 40;
	return H;
}

long int EXPLimit(Player P)
/*Fungsi menghasilkan EXP point yang harus dicapai player agar dapat naik ke level yang lebih tinggi*/
{
	return 10 * (pow(LV(P),2));
}

void GetEXP(Player *P, Enemy E)
/*I.S. P dan E terdefinisi*/
/*F.S. EXP Player ditambahkan dari BaseEXP musuh. Apabila EXP Player >= EXPLimit-nya, EXP Player akan dikurangi EXPLimit,
	LV otomatis naik 1 angka, mendapat tambahan attribute points sebesar 10 points, dan mendapat tambahan 1 skill point
	apabila LV(P) mod 2 = 1 dan 1 < LV(P) < 20 setiap kali EXP Player >= EXPLimit
	hingga akhirnya EXP Player < EXPLimit*/
{
	EXP(*P) = EXP(*P) + (EXPGAIN(E));
	while (EXP(*P) >= EXPLimit(*P))
	{
		EXP(*P) = EXP(*P) - EXPLimit(*P);
		LV(*P)++;
		AP(*P) = AP(*P) + 10;
		if ((LV(*P) < 20) && (LV(*P) > 1) && (LV(*P) % 2 == 1))
		{
			SP(*P)++;
		}
	}
}

/*SELEKTOR ENEMY*/
int STREnemy(Player P, Enemy E)
/*Fungsi menghasilkan STR Enemy berdasarkan Base Stats STR musuh*/
{
	int S = ((2 * STR(E) + 15) * LV(P) / 100) + 5;
	return S;
}
int DEFEnemy(Player P, Enemy E)
/*Fungsi menghasilkan DEF Enemy berdasarkan Base Stats DEF musuh*/
{
	int D = ((2 * DEF(E) + 15) * LV(P) / 100) + 5;
	return D;
}
int LUCEnemy(Player P, Enemy E)
/*Fungsi menghasilkan LUC Enemy berdasarkan Base Stats LUC musuh*/
{
	int L = ((2 * (40 + LUC(E)) + 15) * LV(P) / 100) + 5;
	if (L > 30)
	{
		L = 30;
	} else if (L < 0)
	{
		L = 0;
	}
	return L;
}
int HPMAXEnemy(Player P, Enemy E)
/*Fungsi menghasilkan HP maksimal Enemy berdasarkan Base Stats HP musuh*/
{
	int H = 4 * (((2 * BHP(E) + 15) * LV(P) / 100) + LV(P) + 10);
	return H;
}

/*Generator float number*/
void randomnumbermod (float *mod)
/*I.S. mod terdefinisi*/
/*F.S. mod menghasilkan suatu bilangan real dengan range 0 sampai 100 yang nantinya akan diolah untuk menentukan
apakah serangan critical atau tidak*/
{
	time_t t;
	srand((unsigned) time(&t));
	*mod = fabs(((314 * rand()) % 100) / 100.0);
}

/*Peluang Critical Hit player dengan enemy*/
float CritChancePlayer(Player P)
/*Fungsi menghasilkan peluang Player melakukan serangan critical dari LUCPlayer*/
{
	float Crit;
	Crit = pow(2.0,(-5 + LUCPlayer(P) / 10.0));
	return Crit;
}

float CritChanceEnemy(Player P, Enemy E)
/*Fungsi menghasilkan peluang Pmusuh melakukan serangan critical dari LUCEnemy*/
{
	float Crit;
	Crit = pow(2.0,(-5 + LUCEnemy(P,E) / 10.0));
	return Crit;
}

/*Fungsi Critical (0 = tidak critical, 1 = critical)*/
int IsCritPlayer(Player P)
/*Fungsi menghasilkan apakah serangan yang dilakukan Player critical atau tidak dengan menggunakan generator mod*/
{
	float mod;
	int c;
	randomnumbermod(&mod);
	if (mod <= CritChancePlayer(P))
	{
		c = 1;
	} else
	{
		c = 0;
	}
	return c;
}

int IsCritEnemy(Player P, Enemy E)
/*Fungsi menghasilkan apakah serangan yang dilakukan musuh critical atau tidak dengan menggunakan generator mod*/
{
	float mod;
	int c;
	randomnumbermod(&mod);
	if (mod <= CritChanceEnemy(P,E))
	{
		c = 1;
	} else
	{
		c = 0;
	}
	return c;
}

/*Generator random damage*/
void randomdamagemod (float *mod)
/*I.S. mod terdefinisi*/
/*F.S. mod menghasilkan suatu konstanta sebagai bilangan pengali dengan nilai
konstanta antara 0.85 hingga 1.15*/
{
	time_t t;
	srand((unsigned) time(&t));
	*mod = (0.85 + 0.3 * fabs(((314 * rand()) % 100)) / 100);
}

/*Final damage yang dihasilkan player ataupun enemy*/
int DamagePlayer(Player P, Enemy E)
/*Fungsi menghasilkan damage yang dihasilkan Player setelah melakukan serangan musuh*/
{
	float mod;
	randomdamagemod(&mod);

	int damage = 3.0 * STRPlayer(P) / DEFEnemy(P,E) * mod * (1 + IsCritPlayer(P));
	return damage;
}

int DamageEnemy(Player P, Enemy E)
/*Fungsi menghasilkan damage yang dihasilkan musuh setelah melakukan serangan Player*/
{
	float mod;
	randomdamagemod(&mod);
	int damage = 3.0 * STREnemy(P,E) / DEFPlayer(P) * mod * (1 + IsCritEnemy(P,E));
	return damage;
}

void PlayerCreation (Player *P)
/*I.S. P terdefinisi*/
/*F.S. Attribute Point Player berkurang atau sama dengan sebelumnya. Attribute point
dialokasikan untuk menambah base stats player itu sendiri*/
{
	char typestat;
	int spend;
	printf("PLAYER CREATION\n");
	printf("Increase your base stats to make your character become more powerful!\n");
	printf("Type 'S' and then Skill Points that you want to increase STR base stats\n");
	printf("Type 'D' and then Skill Points that you want to increase DEF base stats\n");
	printf("Type 'L' and then Skill Points that you want to increase LUC base stats\n");
	printf("Type 'E' to exit\n");
	printf("Your Attribute Points = %d\n",AP(*P));
	scanf("\n%c",&typestat);
	while (typestat != 'E')
	{
		if ((typestat != 'S') && (typestat != 'D') && (typestat != 'L'))
		{
			printf("Wrong stats type\n");
		} else
		{
			scanf("%d",&spend);
			if ((spend < 0) || (spend > AP(*P)))
			{
				printf("Wrong attribute points\n");
			} else
			{
				if (typestat == 'S')
				{
					printf("STR Base has increased by %d pts\n",spend);
					STR(*P) = STR(*P) + spend;
					AP(*P) = AP(*P) - spend;
					printf("Your Skill Points = %d\n",AP(*P));
				} else if (typestat == 'D')
				{
					printf("DEF Base has increased by %d pts\n",spend);
					DEF(*P) = DEF(*P) + spend;
					AP(*P) = AP(*P) - spend;
					printf("Your Skill Points = %d\n",AP(*P));
				} else if (typestat == 'L')
				{
					printf("STR Base has increased by %d pts\n",spend);
					LUC(*P) = LUC(*P) + spend;
					AP(*P) = AP(*P) - spend;
					printf("Your Skill Points = %d\n",AP(*P));
				}
			}
		}
		scanf("\n%c",&typestat);
	}
}
