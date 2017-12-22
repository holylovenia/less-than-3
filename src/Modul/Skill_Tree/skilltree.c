/* File: skilltree.c */
/* ADT Skill Tree */
/* Implementasi binary tree dan list rekursif */

#include <ncurses.h>
#include <stdio.h>
#include "../../ADT/General/general.h"
#include "../../Modul/Skill_Tree/skilltree.h"
#include <math.h>

void* Nil = NULL;

void BuildSkillTree (BinTree *ST, ListLR * AS)
{
	// KAMUS
	BinTree L, R, T, U;

		// ALGORITMA

		// Level 3 kanan
		R = Tree (CreateSkillPassive(SkillLevel104, DeskripsiSkillLevel104, 9), NilBT, NilBT);
		L = Tree (CreateSkillPassive(SkillLevel103, DeskripsiSkillLevel103, 8), NilBT, NilBT);
		T = Tree (CreateSkillActive(SkillLevel72, DeskripsiSkillLevel72, 5), L, R);

		// Level 3 kiri
		R = Tree (CreateSkillPassive(SkillLevel102, DeskripsiSkillLevel102, 7), NilBT, NilBT);
		L = Tree (CreateSkillPassive(SkillLevel101, DeskripsiSkillLevel101, 6), NilBT, NilBT);
		U = Tree (CreateSkillActive(SkillLevel71, DeskripsiSkillLevel71, 4), L, R);

		// Level 2 kanan
		R = T;
		CreateEmptyTree(&L);
		T = Tree (CreateSkillPassive(SkillLevel52, DeskripsiSkillLevel52, 3), L, R);

		// Level 2 kiri
		L = U;
		CreateEmptyTree(&R);
		U = Tree (CreateSkillPassive(SkillLevel51, DeskripsiSkillLevel51, 2), L, R);

		// Level 1
		L = U;
		R = T;
		*ST = Tree(CreateSkillPassive(SkillLevel3, DeskripsiSkillLevel3, 1), L, R);

		// Membuat list rekursif berisi skill yang telah diperoleh
		*AS = NilLR;
}
/* MEMBANGUN SKILL TREE DAN ACQUIRED SKILL UNTUK PLAYER
I.S: ST adalah binary tree sembarang, AS adalah recursive list of binary tree.
F.S:  ST terdefinisi, semua skill locked. AS terdefinisi sebagai list kosong.
*/

infotypeBT CreateSkillPassive (StringNama Nama, StringDeskripsi Deskripsi, int ID)
{
	// KAMUS
	infotypeBT X;

		// ALGORITMA
		ID(X) = ID;
		CopyNama(Nama, NamaBT(X));
		CopyNama(Deskripsi, Deskripsi(X));
		Unlocked(X) = false;
		IsPassive(X) = true;
		return (X);
}
/* MEMBUAT PASSIVE SKILL
Menghasilkan infotypeBT sebagai skill pasif yang locked dengan nama "Nama" dan deskripsi "Deskripsi", dan integer "ID" sebagai identitas.
Pre-kondisi: "Nama", "Deskripsi", dan "ID" terdefinisi.
*/

infotypeBT CreateSkillActive (StringNama Nama, StringDeskripsi Deskripsi, int ID)
{
	// KAMUS
	infotypeBT X;

		// ALGORITMA
		ID(X) = ID;
		CopyNama(Nama, NamaBT(X));
		CopyNama(Deskripsi, Deskripsi(X));
		Unlocked(X) = false;
		IsPassive(X) = false;
		return (X);
}
/* MEMBUAT ACTIVE SKILL
Menghasilkan infotypeBT sebagai skill aktif yang locked dengan nama "Nama" dan deskripsi "Deskripsi", dan integer "ID" sebagai identitas.
Pre-kondisi: "Nama", "Deskripsi", dan "ID" terdefinisi.
*/

void UnlockSkill (BinTree * Output, Player * P, ListLR * AS)
{
	// KAMUS

		// ALGORITMA
		Unlocked(Akar(*Output)) = true;
		*AS = KonsB(*AS, *Output);
}
/* MENG-UNLOCK SKILL
Prosedur mengunlock skill dalam Skill Tree berdasarkan level Player.
I.S: Output adalah binary tree terdefinisi, berisi skill yang mau diunlock (masih terkunci).
F.S: Output diunlock.
*/

void TurnOnPassiveSkillLevel3 (Player *P)
{
	// KAMUS


		// ALGORITMA
		STR(*P) += 10;
		DEF(*P) += 10;
}
/* MENGAKTIFKAN PASSIVE SKILL (LEVEL 3)
Hanya perlu diaktifkan sekali, karena memengaruhi stats Player.
I.S: ST adalah binary tree terdefinisi, Player terdefinisi.
F.S: ST (skill pasif pada level 3) aktif, stats Player berubah sesuai efek dari skill.
*/

void TurnOnPassiveSkillLevel5 (WINDOW* infoWin, ListLR AS, Player *P, Enemy * E)
{
	// KAMUS


		// ALGORITMA
		if (LV(*P) >= 5)
		{
			if (SearchAcquiredSkill(AS, SkillLevel51))
			{
				// -10% HP Enemy
				HP(*E) -= 0.1 * HPMAXEnemy(*P, *E);
				wprintw(infoWin, "%s skill activated! ", SkillLevel51);
				wprintw(infoWin, "Enemy HP has been reduced.\n");
				wrefresh(infoWin);
			}
			if (SearchAcquiredSkill(AS, SkillLevel52))
			{
				// +10% HP Player
				HP(*P) += 0.1 * HPMAXPlayer(*P);
				if (HP(*P) > HPMAXPlayer(*P)) {
					HP(*P) = HPMAXPlayer(*P);
				}
				wprintw(infoWin, "%s skill activated! ", SkillLevel52);
				wprintw(infoWin, "You have recovered some HP.\n");
				wrefresh(infoWin);
			}
		}
}
/* MENGAKTIFKAN PASSIVE SKILL (LEVEL 5)
Hanya perlu diaktifkan sekali per battle, karena memengaruhi HP Player / Enemy pada awal pertarungan.
I.S: AS adalah list rekursif terdefinisi, Player dan Enemy terdefinisi.
F.S: Skill pasif level 5 aktif apabila sudah di-acquire, terjadi perubahan pada Player dan Enemy sesuai dengan efek skill.
*/

void UseActiveSkill (WINDOW* win, ListLR AS, Player *P, Enemy *E, char Input)
{
	// KAMUS
	int DamageForEnemyByPlayer, RecoilForPlayer, Regeneration;

		// ALGORITMA
		if (LV(*P) >= 7)
		{
			if ((SearchAcquiredSkill(AS, SkillLevel71)) && (Input == 'S'))
			{
				// Damage x 3 dan Recoil 10% dari HP Max Player
				DamageForEnemyByPlayer = trunc(3 * DamagePlayer(*P, *E));
				RecoilForPlayer = trunc(0.1 * HPMAXPlayer(*P));
				HP(*E) -= DamageForEnemyByPlayer;
				HP(*P) -= RecoilForPlayer;

				wprintw(win, "You used the skill %s!\n", SkillLevel71);
				wprintw(win, "You dealt %d damage to enemy.\n", DamageForEnemyByPlayer);
				wprintw(win, "You took %d damage from recoil.\n", RecoilForPlayer);
			}
			if ((SearchAcquiredSkill(AS, SkillLevel72)) && (Input == 'D'))
			{
				// HP Regeneration (+10%)
				Regeneration = trunc(0.1 * HPMAXPlayer(*P));
				HP(*P) += Regeneration;

				wprintw(win, "You used the skill %s!\n", SkillLevel72);
				wprintw(win, "You recovered %d HP.\n", Regeneration);
			}
		}
}
/* MENGAKTIFKAN ACTIVE SKILL (LEVEL 7)
Hanya bisa digunakan maksimal satu per ronde battle.
I.S: Acquired Skill, Skill Tree, Player, Enemy, input Player sudah terdefinisi.
F.S: Mengimplementasikan skill aktif yang sudah unlocked pada Player dan Enemy.
*/

void UsePassiveSkill (WINDOW* win, ListLR AS, Player *P, Enemy *E, char InputP, char InputE)
{
	// KAMUS
	int DamageForEnemyByPlayer, LifeSteal, Regeneration, MirrorDamage;

		// ALGORITMA
		if (LV(*P) >= 10)
		{
			if (SearchAcquiredSkill(AS, SkillLevel101))
			{
				// Super effective F vs B move
				if ((InputP == 'F') && (InputE == 'B'))
				{
					DamageForEnemyByPlayer = trunc(2.5 * DamagePlayer(*P, *E));
					HP(*E) -= DamageForEnemyByPlayer;

					wprintw(win, "%s activated! ", SkillLevel101);
					wprintw(win, "You dealt %d damage.\n", DamageForEnemyByPlayer);
				}
			}
			if (SearchAcquiredSkill(AS, SkillLevel102))
			{
				// Life steal 10% dari damage yang diberikan
				if ((InputP == 'A') && ((InputE == 'F') || (InputE == 'A')))
				{
					LifeSteal = trunc(0.1 * DamagePlayer(*P, *E));
					HP(*P) += LifeSteal;
					wprintw(win, "%s activated! ", SkillLevel102);
					wprintw(win, "You recovered %d HP\n", LifeSteal);
				}
				else if (InputP == 'F')
				{
					LifeSteal = trunc(0.1 * DamagePlayer(*P, *E));
					HP(*P) += LifeSteal;
					wprintw(win, "%s activated! ", SkillLevel102);
					wprintw(win, "You recovered %d HP.\n", LifeSteal);
				}
				else
				{
				}
			}
			if (SearchAcquiredSkill(AS, SkillLevel103))
			{
				// ++5% dari HP Max Player per turn
				Regeneration = trunc(0.02 * HPMAXPlayer(*P));
				HP(*P) += Regeneration;

				wprintw(win, "%s activated! ", SkillLevel103);
				wprintw(win, "You recovered %d HP.\n", Regeneration);
			}
			if (SearchAcquiredSkill(AS, SkillLevel104))
			{
				// Mirror damage 30% for Enemy
				if ((InputP == 'B') && (InputE == 'A'))
				{
					MirrorDamage = trunc(0.3 * DamageEnemy(*P, *E));
					HP(*E) -= MirrorDamage;

					wprintw(win, "%s activated! ", SkillLevel104);
					wprintw(win, "You dealt %d damage.\n", MirrorDamage);
				}
			}
		}
}
/* MENGAKTIFKAN PASSIVE SKILL (LEVEL 10)
Bisa digunakan bersamaan tiap ronde battle.
I.S: Acquired Skill, Skill Tree, Player, Enemy, input Player, dan input Enemy sudah terdefinisi.
F.S: Mengimplementasikan skill pasif yang sudah unlocked pada Player dan Enemy.
*/

void ShowLockedOptions (ListLR AS)
{
	// KAMUS


		// ALGORITMA
		if (IsEmptyLR(AS) == 1)
		{
		}
		else
		{
			if (Unlocked(Akar(FirstElmt(AS))))
			{
				if (((Left(FirstElmt(AS))) != NilBT) && (!Unlocked(Akar(Left(FirstElmt(AS))))))
				{
					printf("%d) %s\n", ID(Akar(Left(FirstElmt(AS)))), NamaBT(Akar(Left(FirstElmt(AS)))));
				}
				if (((Right(FirstElmt(AS))) != NilBT) && (!Unlocked(Akar(Right(FirstElmt(AS))))))
				{
					printf("%d) %s\n", ID(Akar(Right(FirstElmt(AS)))), NamaBT(Akar(Right(FirstElmt(AS)))));
				}
			}
			ShowLockedOptions(TailLR(AS));
		}
}
/* MENAMPILKAN OPSI LOCKED SKILL YANG DAPAT DIPILIH
Skill yang dapat dipilih merupakan child dari parent yang sudah di-unlock.
I.S: Acquired Skill terdefinisi.
F.S: Menampilkan skill yang dapat dipilih.
*/

boolean CanItBeUnlocked (ListLR AS, int ID)
{
	// KAMUS


		// ALGORITMA
		if (IsEmptyLR(AS) == 1)
		{
			return (false);
		}
		else
		{
			if (((Left(FirstElmt(AS)) != Nil) && (ID == ID(Akar(Left(FirstElmt(AS))))) && (!Unlocked(Akar(Left(FirstElmt(AS)))))) || ((Right(FirstElmt(AS)) != Nil) && (ID == ID(Akar(Right(FirstElmt(AS))))) && (!Unlocked(Akar(Right(FirstElmt(AS)))))))
			{
				return (true);
			}
			else
			{
				return (CanItBeUnlocked(TailLR(AS), ID));
			}
		}
}

void ShowUnlockedSkills (ListLR AS)
{
	// KAMUS


		// ALGORITMA
		PrintListLR(AS);
}
/* MENAMPILKAN SKILL YANG SUDAH DIMILIKI
I.S: Acquired Skill terdefinisi.
F.S: Menampilkan skill yang dimiliki oleh Player.
*/

void ChooseSkill (int Input, BinTree ST, Player * P, ListLR * AS)
{
	// KAMUS
	BinTree NextST;

		// ALGORITMA
		if (Input == 1) {
			TurnOnPassiveSkillLevel3(P);
		}
		CreateEmptyTree(&NextST);
		do
		{
			SearchID(ST, Input, &NextST);
			if (SearchLR(*AS, NextST))
			{
				CreateEmptyTree(&NextST);
			}
		}
		while (NextST == NilBT);

		UnlockSkill(&NextST, P, AS);
}
/* MEMILIH SKILL DARI OPSI YANG DITAMPILKAN
Masukan player selalu sesuai dengan pilihan yang tersedia (ditampilkan oleh ShowLockedOptions).
I.S: Skill Tree, Player, dan Acquired Skill terdefinisi.
F.S: Acquired Skill bertambah sesuai pilihan Player.
*/

void SearchSkill (BinTree ST, StringNama SkillName, BinTree * Output)
{
	// KAMUS
	BinTree OutputL, OutputR;

		// ALGORITMA
		if (IsTreeEmpty(ST))
		{
			*Output = Nil;
		}
		else if (SkillName == NamaBT(Akar(ST)))
		{
			*Output = ST;
		}
		else
		{
			SearchSkill(Left(ST), SkillName, &OutputR);
			SearchSkill(Right(ST), SkillName, &OutputL);
			if (OutputL == Nil)
			{
				*Output = OutputR;
			}
			else
			{
				*Output = OutputL;
			}
		}
}
/* MENCARI SKILL BERDASARKAN NAMA SKILL
I.S: Skill Tree terdefinisi, SkillName merupakan nama dari skill yang ada pada Skill Tree, Output adalah binary tree kosong.
F.S: Output adalah binary tree yang berisi skill yang sesuai dengan SkillName.
*/

void SearchID (BinTree ST, int ID, BinTree * Output)
{
	// KAMUS
	BinTree OutputL, OutputR;

		// ALGORITMA
		if (IsTreeEmpty(ST))
		{
			*Output = Nil;
		}
		else if (ID == ID(Akar(ST)))
		{
			*Output = ST;
		}
		else
		{
			SearchID(Left(ST), ID, &OutputR);
			SearchID(Right(ST), ID, &OutputL);
			if (OutputL == Nil)
			{
				*Output = OutputR;
			}
			else
			{
				*Output = OutputL;
			}
		}
}
/* MENCARI SKILL BERDASARKAN ID
I.S: Skill Tree terdefinisi, ID merupakan identitas dari skill yang ada pada Skill Tree, Output adalah binary tree kosong.
F.S: Output adalah binary tree yang berisi skill yang sesuai dengan ID.
*/

boolean SearchAcquiredSkill (ListLR AS, StringNama Nama)
{
	// KAMUS


		// ALGORITMA
		if (IsEmptyLR(AS) == 1)
		{
			return (false);
		}
		else
		{
			if (CompareString(NamaBT(Akar(FirstElmt(AS))), Nama) == 0)
			{
				return (true);
			}
			else
			{
				return (SearchAcquiredSkill(TailLR(AS), Nama));
			}
		}
}
/* MENENTUKAN APAKAH SKILL SUDAH DI-ACQUIRE APA BELUM
Bernilai true apabila skill sudah dimiliki, false bila belum.
Pre-kondisi: AS adalah recursive list of binary tree terdefinisi, Nama sembarang.
*/
