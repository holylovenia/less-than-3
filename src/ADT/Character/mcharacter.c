//Deskripsi : Contoh program dengan implementasi fungsi dan prosedur dari header tipe bentukan player dan musuh

#include <stdio.h>
#include "../Character/character.h"

int main ()
{
	// Menciptakan karakter awal pemain
	Player P1;
	NAMA W;
	scanf("%s",W);
	CreatePlayerAwal(&P1,W);
	printf("Nama karakter : %s\n",NAMA(P1));
	printf("Stats Awal :\n");
	printf("Level player : %d\n",LV(P1));
	printf("HP Max player : %d\n",HP(P1));
	printf("Base strength player : %d\n",STR(P1));
	printf("Base defense player : %d\n",DEF(P1));
	printf("Base luck player : %d\n",LUC(P1));
	printf("EXP player : %d\n",EXP(P1));
	printf("Attribute point player : %d\n",AP(P1));
	printf("Skill point player : %d\n",SP(P1));

	// Menciptakan karakter musuh
	Enemy E;
	NAMA X = "Lilim";
	dbBST EnemyData;
	LoadBST(&EnemyData);
	CreateEnemy(P1,&E,X,EnemyData);
    printf("Nama: %s\n", NAMA(E));
    printf("HP: %d\n", HP(E));
    printf("STR: %d\n", STR(E));
    printf("DEF: %d\n", DEF(E));
    printf("LUC: %d\n", LUC(E));
    printf("EXPGAIN: %d\n", EXPGAIN(E));
    if (ISBOSS(E))
    {
        printf("Is Boss\n\n");
    } else
    {
        printf("Not Boss\n\n");
    }

    Player P2;
	NAMA Y = "Serenade";
	CreatePlayerAwal(&P2,Y);
	printf("Nama karakter : %s\n",NAMA(P2));
	printf("Stats Awal :\n");
	printf("Level player : %d\n",LV(P2));
	printf("HP Max player : %d\n",HP(P2));
	printf("Base strength player : %d\n",STR(P2));
	printf("Base defense player : %d\n",DEF(P2));
	printf("Base luck player : %d\n",LUC(P2));
	printf("EXP player : %d\n",EXP(P2));
	printf("Attribute point player : %d\n",AP(P2));
	printf("Skill point player : %d\n",SP(P2));
	return 0;

}
