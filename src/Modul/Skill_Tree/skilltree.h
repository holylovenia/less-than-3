/* File: skilltree.h */
/* ADT Skill Tree */
/* Implementasi binary tree dan list rekursif */

#ifndef skilltree_H
#define skilltree_H

/* KAMUS */
#include <ncurses.h>

#include <stdlib.h>
#include "../../ADT/Character/character.h"
#include "../../ADT/Boolean/boolean.h"
#include "../../ADT/Binary_Tree/bintree.h"
#include "../../ADT/List_Rekursif/listrek.h"
#include "../../Modul/Statistic/statistic.h"


/* SKILLS */


// Mengubah stats player
#define SkillLevel3 "Not Less Than 3" // Base STR dan DEF masing-masing +10
#define DeskripsiSkillLevel3 "Congratulations! (not really)\nYou've become very, very slightly\nmore knowledgable on the human\nritual of romance.\nYou can now unlock more powerful\nskills as you grow! Isn't it great?\n\n(+STR & +DEF)"


// Berpengaruh pada awal pertarungan

#define SkillLevel51 "Charming Persona" // -10% HP Enemy
#define DeskripsiSkillLevel51 "Your winning personality conquers\nthe heart of everyone you encounter!That, or you're pitiful enough that\neveryone accepted your advances out\nof pity.\n\n(-10% HP Enemy on encounter)"

#define SkillLevel52 "Hard to Get" // +10% HP Player
#define DeskripsiSkillLevel52 "You can now actually think with yourbrain and refuse instead of being\nstrung along by every prospective\npartner you meet.\n\n(+10% HP Player on encounter)"


// Skill aktif yang dapat digunakan dalam pertarungan

#define SkillLevel71 "All of Me" // Damage x 3 dan Recoil 10% dari HP Max Player
#define DeskripsiSkillLevel71 "You've done the unthinkable and\nactually open up your deepest,\ntruest heart to the (possible)\nlove of your life!\n\n== Active Skill ('S' in battle) ==\n(3x Attract & -10% HP recoil)\n(Ignore Block from Enemy)"

#define SkillLevel72 "Me, Myself, and I" // HP Regeneration (+10%)
#define DeskripsiSkillLevel72 "Your boundless narcissism basks in\nthe (seemingly, to you) complete\nand undivided attention of the\nswooning masses.\n\n == Active Skill ('D' in battle) ==\n(Regenerate +10% HP)"


// Skill pasif yang bekerja setiap ronde pertarungan
#define SkillLevel101 "Irresistible" // Super effective F vs B move
#define DeskripsiSkillLevel101 "After countless hours spent on this\ngame, you've finally perfected your\nflirting technique.\nNone of these poor souls could\nresist your charm now.\n\n(Successful Flirt will deal\n2.5x damage!)"

#define SkillLevel102 "Cassanova" // Life steal 20% dari damage yang diberikan
#define DeskripsiSkillLevel102 "You toy with the hearts of young\nmaidens and drink their infatuation\nto become stronger and prey on\nmore clueless maidens.\n\n(Recover 10% damage done to Enemy)"

#define SkillLevel103 "How Deep is Your Love" // ++5% dari HP Max Player per turn
#define DeskripsiSkillLevel103 "Not as deep as the ocean apparently.You, enemy of mankind, have actuallyfallen in love with the act\nof romancing itself instead of your fellow humans!\n\n(Recover 2% HP every turn)\n(There are 4 turns in 1 round)"

#define SkillLevel104 "Untouchable" // Mirror damage 30% for Enemy
#define DeskripsiSkillLevel104 "You've transcended obliviousness andanyone whom you rebuff will,\ncompletely paradoxically, fall\neven more in love with you!\n\n(Reflect 30% damage when using Bore)(Not effective if Enemy Flirted)"



/* PROSEDUR DAN FUNGSI */

void BuildSkillTree (BinTree *ST, ListLR * AS);
/* MEMBANGUN SKILL TREE DAN ACQUIRED SKILL UNTUK PLAYER
I.S: ST adalah binary tree sembarang, AS adalah recursive list of binary tree.
F.S:  ST terdefinisi, semua skill locked. AS terdefinisi sebagai list kosong.
*/

infotypeBT CreateSkillPassive (StringNama Nama, StringDeskripsi Deskripsi, int ID);
/* MEMBUAT PASSIVE SKILL
Menghasilkan infotypeBT sebagai skill pasif yang locked dengan nama "Nama" dan deskripsi "Deskripsi", dan integer "ID" sebagai identitas.
Pre-kondisi: "Nama", "Deskripsi", dan "ID" terdefinisi.
*/

infotypeBT CreateSkillActive (StringNama Nama, StringDeskripsi Deskripsi, int ID);
/* MEMBUAT ACTIVE SKILL
Menghasilkan infotypeBT sebagai skill aktif yang locked dengan nama "Nama" dan deskripsi "Deskripsi", dan integer "ID" sebagai identitas.
Pre-kondisi: "Nama", "Deskripsi", dan "ID" terdefinisi.
*/

boolean CanItBeUnlocked (ListLR AS, int ID);

void UnlockSkill (BinTree * Output, Player * P, ListLR * AS);
/* MENG-UNLOCK SKILL
Prosedur mengunlock skill dalam Skill Tree berdasarkan level Player.
I.S: Output adalah binary tree terdefinisi, berisi skill yang mau diunlock (masih terkunci).
F.S: Output diunlock.
*/

void TurnOnPassiveSkillLevel3 (Player *P);
/* MENGAKTIFKAN PASSIVE SKILL (LEVEL 3)
Hanya perlu diaktifkan sekali, karena memengaruhi stats Player.
I.S: ST adalah binary tree terdefinisi, Player terdefinisi.
F.S: ST (skill pasif pada level 3) aktif, stats Player berubah sesuai efek dari skill.
*/

void TurnOnPassiveSkillLevel5 (WINDOW* infoWin, ListLR AS, Player *P, Enemy * E);
/* MENGAKTIFKAN PASSIVE SKILL (LEVEL 5)
Hanya perlu diaktifkan sekali per battle, karena memengaruhi HP Player / Enemy pada awal pertarungan.
I.S: AS adalah list rekursif terdefinisi, Player dan Enemy terdefinisi.
F.S: Skill pasif level 5 aktif apabila sudah di-acquire, terjadi perubahan pada Player dan Enemy sesuai dengan efek skill.
*/

void UseActiveSkill (WINDOW* win, ListLR AS, Player *P, Enemy *E, char Input);
/* MENGAKTIFKAN ACTIVE SKILL (LEVEL 7)
Hanya bisa digunakan maksimal satu per ronde battle.
I.S: Acquired Skill, Skill Tree, Player, Enemy, input Player sudah terdefinisi.
F.S: Mengimplementasikan skill aktif yang sudah unlocked pada Player dan Enemy.
*/

void UsePassiveSkill (WINDOW* win, ListLR AS, Player *P, Enemy *E, char InputP, char InputE);
/* MENGAKTIFKAN PASSIVE SKILL (LEVEL 10)
Bisa digunakan bersamaan tiap ronde battle.
I.S: Acquired Skill, Skill Tree, Player, Enemy, input Player, dan input Enemy sudah terdefinisi.
F.S: Mengimplementasikan skill pasif yang sudah unlocked pada Player dan Enemy.
*/

void ShowLockedOptions (ListLR AS);
/* MENAMPILKAN OPSI LOCKED SKILL YANG DAPAT DIPILIH
Skill yang dapat dipilih merupakan child dari parent yang sudah di-unlock.
I.S: Acquired Skill terdefinisi.
F.S: Menampilkan skill yang dapat dipilih.
*/

void ShowUnlockedSkills (ListLR AS);
/* MENAMPILKAN SKILL YANG SUDAH DIMILIKI
I.S: Acquired Skill terdefinisi.
F.S: Menampilkan skill yang dimiliki oleh Player.
*/

void ChooseSkill (int Input, BinTree ST, Player * P, ListLR * AS);
/* MEMILIH SKILL DARI OPSI YANG DITAMPILKAN
Masukan player selalu sesuai dengan pilihan yang tersedia (ditampilkan oleh ShowLockedOptions).
I.S: Skill Tree, Player, dan Acquired Skill terdefinisi.
F.S: Acquired Skill bertambah sesuai pilihan Player.
*/

void SearchSkill (BinTree ST, StringNama SkillName, BinTree * Output);
/* MENCARI SKILL BERDASARKAN NAMA SKILL
I.S: Skill Tree terdefinisi, SkillName merupakan nama dari skill yang ada pada Skill Tree, Output adalah binary tree kosong.
F.S: Output adalah binary tree yang berisi skill yang sesuai dengan SkillName.
*/

void SearchID (BinTree ST, int ID, BinTree * Output);
/* MENCARI SKILL BERDASARKAN ID
I.S: Skill Tree terdefinisi, ID merupakan identitas dari skill yang ada pada Skill Tree, Output adalah binary tree kosong.
F.S: Output adalah binary tree yang berisi skill yang sesuai dengan ID.
*/

boolean SearchAcquiredSkill (ListLR AS, StringNama Nama);
/* MENENTUKAN APAKAH SKILL SUDAH DI-ACQUIRE APA BELUM
Bernilai true apabila skill sudah dimiliki, false bila belum.
Pre-kondisi: AS adalah recursive list of binary tree terdefinisi, Nama sembarang.
*/


#endif
