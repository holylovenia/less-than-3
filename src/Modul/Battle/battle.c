/* File: battle.c */
/* ADT Battle */
/* Implementasi stack, queue, array, binary tree, list rekursif, skill tree, pembacaan string, dan ADT lainnya */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../Modul/Battle/battle.h"
#include "../../Modul/Statistic/statistic.h"
#include "../../ADT/Stack/stackt.h"
#include "../../Modul/Interface/interface.h"
#include "../../ADT/Basestats/basestats.h"
#include "../../Modul/Skill_Tree/skilltree.h"
#include "../../ADT/Mesin_Kata/mesinkata.h"


void BattleEnemy (ListLR AS, Player * P, Enemy E, boolean * Win)
{
	// KAMUS
	int CountAksi, CountRonde;
	Stack S; // Penyimpanan aksi musuh
	Queue Q, QCopy, X, XCopy;
	char InputP, InputE;

		// ALGORITMA
		CountRonde = 0;

		// Menampilkan HP awal player dan musuh
		printf("Enemy: %s\n", NAMA(E));
		printf("HP Player: %d \n", HP(*P));
		printf("HP Musuh: %d \n", HP(E));

		// Membaca masukan musuh dari file eksternal
		InputAksiMusuh(&S);

		// Mengaktifkan skill level 5 (sekali pakai)
		//TurnOnPassiveSkillLevel5(AS, P, &E);

		while (!IsOver(*P, E, CountRonde))
		{
			CountRonde++;
			CountAksi = 0;

			// Menampilkan aksi musuh dan player ke layar
			printf("Aksi Musuh (Ronde %d)\n", CountRonde);
			//PrintAksiMusuh(InfoTop(S), CountAksi);
			printf("\n\n");
			PopStack(&S, &X);
			XCopy = X;

			// Membaca masukan pengguna
			//InputAksiPlayer(&Q, *P, AS);
			QCopy = Q;

			while ((CountAksi < 4) && (!IsOver(*P, E, CountRonde)))
			{
				CountAksi++;

				// Menampilkan aksi musuh dan player ke layar
				printf("---------------------\n\n");
				printf("Aksi Musuh (Aksi %d)\n", CountAksi);
				//PrintAksiMusuh(X, CountAksi);
				printf("\n\n");
				printf("Aksi Player (Aksi %d)\n", CountAksi);
				//PrintAksiPlayer(Q, CountAksi);
				printf("\n\n");

				// Mengambil aksi dari player
				DelQ(&QCopy, &InputP);

				// Mengambil aksi dari musuh
				DelQ(&XCopy, &InputE);

				// Mengkalkulasi perubahan yang terjadi pada HP player dan musuh
				//DamageTaken(InputP, InputE, P, &E, AS);

				// Menampilkan HP player dan musuh
				printf("Ronde %d Aksi %d\n", CountRonde, CountAksi);
				printf("Enemy: %s\n", NAMA(E));
				printf("HP Player: %d \n", HP(*P));
				printf("HP Musuh: %d \n", HP(E));
			}
			printf("\n\n");
		}

		// Hasil pertarungan
		*Win = IsWinner(*P, E);
		if (*Win)
		{
			GetEXP(P, E);
			printf("EXP Player: %d\n", EXP(*P));
			printf("Level Player: %d\n", LV(*P));

			// Mekanisme Unlock Skill
			// Mau dipindahin ke main program aja nanti
			// Jangan dihapus dulu buat jaga-jaga
			// Hanya bisa dilakukan tiap naik 2 level
			/*
			if (LV(*P) == 3)
			{
				printf("Level 3 Skill Unlocked: %s\n", SkillLevel3);
				UnlockSkill(ST, P, AS);
			}
			else if ((LV(*P) >= 5) && (LV(*P) % 2 == 1))
			{
				printf("Acquired Skills:\n");
				ShowUnlockedSkills(*AS);
				printf("\nWhich one do you want to choose?\n");
				ShowLockedOptions(*AS);
				ChooseSkill(*ST, P, AS);
			}
			*/
		}
}
/* SISTEM PERTARUNGAN
I.S: Acquired Skill (List Rekursif), Player, dan Enemy terdefinisi.
F.S: Player berubah sesuai dengan apa yang terjadi pada mode pertarungan. Boolean Win bernilai true apabila Player berhasil mengalahkan Enemy.
*/

void LoadAksiMusuh (TabInt *T)
{	// KAMUS
	int i;

	// ALGORITMA
	MakeEmptyTab(T);
	i = GetFirstIdxTab(*T);
	START("aksi musuh.txt");
	while (CC != '|') {
		ElmtTab(*T,i) = (int) CC - (int) '0';
		Neff(*T)++;
		i++;
		ADV();
	}
}
/* MEMBACA AKSI MUSUH DARI FILE EKSTERNAL
I.S: T adalah array of integer sembarang.
F.S: T berisi aksi musuh dari file eksternal.
*/

void InputAksiMusuh (Stack * S)
{
	// KAMUS
	int i;
	TabInt T;
	Queue Q;

		// ALGORITMA

		/* Baca dari file eksternal */
		LoadAksiMusuh(&T);

		/* Shuffle urutan array */
		ShuffleTab(&T);

		/* Memasukkan ke dalam stack */
		CreateEmptyStack(S);
		CreateEmptyQ(&Q, 4);
		for (i = GetFirstIdxTab(T); i <= GetLastIdxTab(T); i++)
		{
			AddQ(&Q, TransformAksi(ElmtTab(T, i)));
			if (i % 4 == 0)
			{
				PushStack(S, Q);
				CreateEmptyQ(&Q, 4);
			}
		}
}
/* MEMASUKKAN AKSI MUSUH KE STACK OF QUEUE
Baca aksi musuh dari file eksternal, dimasukkan ke array of integer, indeks array diacak. Isi array ditransformasi menjadi char dan dimasukkannya ke stack of queue.
I.S: S adalah stack of queue sembarang.
F.S: S berisi aksi musuh.
*/

char TransformAksi (int N)
{
	N = N % 3;
	if (N == 0)
	{
		return ('A');
	}
	else if (N == 1)
	{
		return ('B');
	}
	else // N == 2
	{
		return ('F');
	}
}
/* MENTRANSFORMASI INTEGER MENJADI CHAR
Ketentuan transformasi:
0 adalah A, 1 adalah B, dan 2 adalah F.
Pre-kondisi: Integer N sudah pasti 0, 1, atau 2.
*/

void DamageTaken (WINDOW* win, char InputP, char InputE, Player * P, Enemy * E, ListLR AS)
{
	// KAMUS
	int DamageByEnemy = 0;
	int DamageByPlayer = 0;

		// ALGORITMA

		if ((InputP == 'A') && (InputE == 'A'))
		{
			DamageByEnemy = DamageEnemy(*P, *E);
			HP(*P) -= DamageByEnemy;
			DamageByPlayer = DamagePlayer(*P, *E);
			HP(*E) -= DamageByPlayer;
		}
		else if ((InputP == 'A') && (InputE == 'F'))
		{
			DamageByPlayer = DamagePlayer(*P, *E);
			HP(*E) -= DamageByPlayer;
			DamageByEnemy = trunc(0.5*DamageEnemy(*P, *E));
			HP(*P) -= DamageByEnemy;
		}
		else if ((InputP == 'F') && (InputE == 'A'))
		{
			DamageByEnemy = DamageEnemy(*P, *E);
			HP(*P) -= DamageByEnemy;
			DamageByPlayer = trunc(0.5*DamagePlayer(*P, *E));
			HP(*E) -= DamageByPlayer;
		}
		else if ((InputP == 'B') && (InputE == 'F'))
		{
			DamageByEnemy = trunc(1.5*DamageEnemy(*P, *E));
			HP(*P) -= DamageByEnemy;
		}
		else if ((InputP == 'F') && (InputE == 'B'))
		{
			DamageByPlayer = trunc(1.5*DamagePlayer(*P, *E));
			HP(*E) -= DamageByPlayer;
		}
		else if ((InputP == 'F') && (InputE == 'F'))
		{
			DamageByEnemy = trunc(0.5*DamageEnemy(*P, *E));
			HP(*P) -= DamageByEnemy;
			DamageByPlayer = trunc(0.5*DamagePlayer(*P, *E));
			HP(*E) -= DamageByPlayer;
		}
		else if (((InputP == 'S') || (InputP == 'D')) && (InputE == 'A'))
		{
			DamageByEnemy = DamageEnemy(*P, *E);
			HP(*P) -= DamageByEnemy;
			UseActiveSkill(win, AS, P, E, InputP);
		}
		else if (((InputP == 'S') || (InputP == 'D')) && (InputE == 'B'))
		{
			UseActiveSkill(win, AS, P, E, InputP);
		}
		else if (((InputP == 'S') || (InputP == 'D')) && (InputE == 'F'))
		{
			DamageByEnemy = trunc(0.5*DamageEnemy(*P, *E));
			HP(*P) -= DamageByEnemy;
			UseActiveSkill(win, AS, P, E, InputP);
		}
		// else  (((InputP == 'A') && (InputE == 'B')) || ((InputP == 'B') && (InputE == 'A')) ||
		// ((InputP == 'B') && (InputE == 'B')))


		wprintw(win, "You ");
		if (InputP == 'A')
		{
			wprintw(win, "used Attract ");
			wprintw(win, "and dealt %d damage.\n", DamageByPlayer);
			if (IsCritPlayer(*P)) {
				wprintw(win, "It was a critical hit!\n");
			}
		}
		else if (InputP == 'B')
		{
			if (InputE == 'F') {
				wprintw(win, "used Bore. But it failed!\n");
			}
			else {
				wprintw(win, "used Bore and protected yourself.\n");
			}

		}
		else if (InputP == 'F')
		{
			wprintw(win, "used Flirt ");
			if (InputE == 'B') {
				wprintw(win, "and dealt %d damage. It's very effective!\n", DamageByPlayer);
			}
			else {
				wprintw(win, "and dealt %d damage. It's not very effective...\n", DamageByPlayer);
			}
			if (IsCritPlayer(*P)) {
				wprintw(win, "It was a critical hit!\n");
			}
		}
		else
		{
		}

		wrefresh(win);
		Pause(500);

		wprintw(win, "%s ", NAMA(*E));
		if (InputE == 'A')
		{
			wprintw(win, "used Attract ");
			wprintw(win, "and dealt %d damage.\n", DamageByEnemy);
			if (IsCritEnemy(*P, *E)) {
				wprintw(win, "It was a critical hit!\n");
			}
		}
		else if (InputE == 'B')
		{
			if ((InputP == 'F') || (InputP == 'D')) {
				wprintw(win, "used Bore. But she failed!\n");
			}
			else {
				wprintw(win, "used Bore and protected herself.\n");
				if (InputP == 'B') {
					wprintw(win, "An awkward silence moment ensues...\n");
				}
			}
		}
		else // InputE == 'F'
		{
			wprintw(win, "used Flirt ");
			if (InputP == 'B') {
				wprintw(win, "and dealt %d damage. It's very effective!\n", DamageByEnemy);
			}
			else {
				wprintw(win, "and dealt %d damage. It's not very effective...\n", DamageByEnemy);
			}
			if (IsCritEnemy(*P, *E)) {
				wprintw(win, "It was a critical hit!\n");
			}
		}
		wrefresh(win);

		UsePassiveSkill(win, AS, P, E, InputP, InputE);

		if (HP(*E) < 0) {
			HP(*E) = 0;
		}

		if (HP(*P) < 0) {
			HP(*P) = 0;
		}

		if (HP(*E) > HPMAXEnemy(*P, *E)) {
			HP(*E) = HPMAXEnemy(*P, *E);
		}

		if (HP(*P) > HPMAXPlayer(*P)) {
			HP(*P) = HPMAXPlayer(*P);
		}

		wrefresh(win);
		Pause(1500);

}
/* MENENTUKAN DAMAGE YANG DITERIMA PLAYER DAN ENEMY
Membandingkan input aksi player dan musuh dengan mempertimbangkan stats PLayer dan Enemy, juga skill-skill yang dimiliki Player.
I.S: Masukan aksi Player, masukan aksi Enemy, Player, Enemy, dan Acquired Skill terdefinisi.
F.S: HP Player dan Enemy berubah sesuai dengan damage yang diterima.
*/
void PrintAksiMusuh (WINDOW* win, Queue Q, int CountAksi)
{
	// KAMUS
	int i;
	Queue QCopy;
	char X;

		// ALGORITMA
		i = 1;
		QCopy = Q;
		while (!IsEmptyQ(QCopy))
		{
			DelQ(&QCopy, &X);
			if (i == CountAksi)
			{
				mvwprintw(win, 2, (i*3-1), ">%c ", X);
			}
			else if ((i % 2 == 0) && (i > CountAksi))
			{
				mvwprintw(win, 2, (i*3-1), "# ");
			}
			else
			{
				mvwprintw(win, 2, (i*3-1), "%c ", X);
			}
			i++;
		}

}
/* MENAMPILKAN AKSI ENEMY
I.S: Q adalah queue of char terdefinisi, CountAksi terdefinisi sebagai penanda aksi ke-berapa.
F.S: Mencetak aksi Enemy per ronde (4 buah) dan menampilkan aksi kedua & keempat sebagai '#' saat awal.
*/

boolean IsOver (Player P, Enemy E, int N)
{
	// KAMUS

		// ALGORITMA
		if ((ISBOSS(E)) && (N == NRondeFB))
		{
			return (true);
		}
		else if ((!ISBOSS(E)) && (N == NRonde))
		{
			return (true);
		}
		else if ((HP(P) == 0) || (HP(E) == 0))
		{
			return (true);
		}
		else
		{
			return (false);
		}
}
/* MENENTUKAN KEBERLANGSUNGAN PERTARUNGAN
Bernilai true apabila pertarungan sudah berakhir, false apabila pertarungan belum selesai.
Pre-kondisi: N adalah banyak ronde yang sudah berlangsung, Player dan Enemy terdefinisi.
*/

boolean IsWinner (Player P, Enemy E)
{
	return ((HP(P) > 0) && (HP(E) == 0));
}
/* MENENTUKAN PEMENANG PERTARUNGAN
Bernilai true jika dan hanya jika Player menang dan Enemy kalah.
Pre-kondisi: Player dan Enemy terdefinisi.
*/

void InputAksiPlayer (WINDOW* cmdWin, WINDOW* infoWin, Queue * Q, Player P, ListLR AS)
{
	// KAMUS
	int N = 4;
	int i;
	char X;
	int MaxElQueue;
	int IsUsed;


		// ALGORITMA
		CreateEmptyQ(Q, N);
		//IsUsed = false;

		echo();
		curs_set(true);

		IsUsed = 0;

		while (NBElmtQ(*Q) < N)
		{
			mvwprintw(cmdWin, 2, (NBElmtQ(*Q)*3+2), " ");
			mvwgetnstr(cmdWin, 2, (NBElmtQ(*Q)*3+2), &X, 1);
			if ((X == 'A') || (X == 'B') || (X == 'F') || ((X == 'S') && (SearchAcquiredSkill(AS, SkillLevel71)) && (IsUsed == 0)) || ((X == 'D') && (SearchAcquiredSkill(AS, SkillLevel72)) && (IsUsed == 0)))
			{
				AddQ (Q, X);
				if ((X == 'S') || (X == 'D'))
				{
					wprintw(infoWin, "%d %c\n", IsUsed, X);
					IsUsed = 1;
				}
			}
			else if (X == 'E')
			{
				mvwprintw(cmdWin, 2, (NBElmtQ(*Q)*3+2), " ");
				MaxElQueue = NBElmtQ(*Q) - 1;
				i = 0;
				while (i < MaxElQueue)
				{
					i++;
					DelQ(Q, &X);
					AddQ(Q, X);
				}

				char Xtrash;
				DelQ(Q, &Xtrash);

				if ((X == 'S') || (X == 'D'))
				{
					IsUsed = 0;
				}
			}
			else // Masukan salah
			{
				// Mengeluarkan error message
				if ((X == 'a') || (X == 'b') || (X == 'f') || (X == 'd') || (X == 's')) {
					wprintw (infoWin, "\nInvalid Command. Please use capital letters.\n");
				}
				else {
					wprintw (infoWin, "\nInvalid Command.\n");
				}

				if (IsUsed == 1)
				{
					wprintw(infoWin, "Active skill has been used this round\n");
				}
				if (((X == 'S') && (!SearchAcquiredSkill(AS, SkillLevel71))) || ((X == 'D') && (!SearchAcquiredSkill(AS, SkillLevel72))))
				{
					wprintw(infoWin, "Player doesn't have the skill ");
					if (X == 'S')
					{
						wprintw(infoWin, "%s.\n", SkillLevel71);
					}
					else // X == 'D'
					{
						wprintw(infoWin, "%s.\n", SkillLevel72);
					}
				}
			}
			wrefresh(cmdWin);
			wrefresh(infoWin);
		}

		noecho();
		curs_set(false);
}
/* MEMBACA INPUT AKSI DARI PLAYER
Input aksi yang diterima adalah 4 buah (1 ronde). Aksi dimasukkan secara individu. Apabila masukan salah, program akan menampilkan pesan error dan meminta kembali input Player hingga benar.
I.S: Q adalah queue of char sembarang, Player dan Acquired Skill terdefinisi.
F.S: Q berisi input aksi player yang valid.
*/

void PrintAksiPlayer (WINDOW* win, Queue Q, int CountAksi)
{
	// KAMUS
	Queue QCopy;
	char X;
	int i, N;

		// ALGORITMA
		N = 4;
		QCopy = Q;
		for (i = 1; i <= N; i++)
		{
			DelQ(&QCopy, &X);
			if (i == CountAksi)
			{
				mvwprintw(win, 2, (i*3-1), ">%c ", X);
			}
			else
			{
				mvwprintw(win, 2, (i*3-1), "%c ", X);
			}
		}
}
/* MENAMPILKAN AKSI PLAYER
I.S: Q adalah queue of char terdefinisi, CountAksi terdefinisi sebagai penanda aksi ke-berapa.
F.S: Mencetak aksi Player per ronde (4 buah).
*/
