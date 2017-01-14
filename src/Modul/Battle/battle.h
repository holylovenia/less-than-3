/* File: battle.h */
/* ADT Battle */
/* Implementasi stack, queue, array, binary tree, list rekursif, skill tree, pembacaan string, dan ADT lainnya */

#ifndef __BATTLE_H__
#define __BATTLE_H__

#include <ncurses.h>

#include "../../ADT/Character/character.h"
#include "../../ADT/Boolean/boolean.h"
#include "../../ADT/Queue/queue.h"
#include "../../ADT/Stack/stackt.h"
#include "../../ADT/Array/array.h"
#include "../../Modul/Skill_Tree/skilltree.h"

#define NRonde 10
#define NRondeFB 20
//extern int CountAksi;


void BattleEnemy (ListLR AS, Player * P, Enemy E, boolean * Win);
/* SISTEM PERTARUNGAN
I.S: Acquired Skill (List Rekursif), Player, dan Enemy terdefinisi.
F.S: Player berubah sesuai dengan apa yang terjadi pada mode pertarungan. Boolean Win bernilai true apabila Player berhasil mengalahkan Enemy.
*/

void LoadAksiMusuh (TabInt *T);
/* MEMBACA AKSI MUSUH DARI FILE EKSTERNAL
I.S: T adalah array of integer sembarang.
F.S: T berisi aksi musuh dari file eksternal.
*/

void InputAksiMusuh (Stack * S);
/* MEMASUKKAN AKSI MUSUH KE STACK OF QUEUE
Baca aksi musuh dari file eksternal, dimasukkan ke array of integer, indeks array diacak. Isi array ditransformasi menjadi char dan dimasukkannya ke stack of queue.
I.S: S adalah stack of queue sembarang.
F.S: S berisi aksi musuh.
*/

char TransformAksi (int N);
/* MENTRANSFORMASI INTEGER MENJADI CHAR
Ketentuan transformasi:
0 adalah A, 1 adalah B, dan 2 adalah F.
Pre-kondisi: Integer N sudah pasti 0, 1, atau 2.
*/

void DamageTaken (WINDOW* win, char InputP, char InputE, Player * P, Enemy * E, ListLR AS);
/* MENENTUKAN DAMAGE YANG DITERIMA PLAYER DAN ENEMY
Membandingkan input aksi player dan musuh dengan mempertimbangkan stats PLayer dan Enemy, juga skill-skill yang dimiliki Player.
I.S: Masukan aksi Player, masukan aksi Enemy, Player, Enemy, dan Acquired Skill terdefinisi.
F.S: HP Player dan Enemy berubah sesuai dengan damage yang diterima.
*/

void PrintAksiMusuh (WINDOW* win, Queue Q, int CountAksi);
/* MENAMPILKAN AKSI ENEMY
I.S: Q adalah queue of char terdefinisi, CountAksi terdefinisi sebagai penanda aksi ke-berapa.
F.S: Mencetak aksi Enemy per ronde (4 buah) dan menampilkan aksi kedua & keempat sebagai '#' saat awal.
*/

boolean IsOver (Player P, Enemy E, int N);
/* MENENTUKAN KEBERLANGSUNGAN PERTARUNGAN
Bernilai true apabila pertarungan sudah berakhir, false apabila pertarungan belum selesai.
Pre-kondisi: N adalah banyak ronde yang sudah berlangsung, Player dan Enemy terdefinisi.
*/

boolean IsWinner (Player P, Enemy E);
/* MENENTUKAN PEMENANG PERTARUNGAN
Bernilai true jika dan hanya jika Player menang dan Enemy kalah.
Pre-kondisi: Player dan Enemy terdefinisi.
*/

void InputAksiPlayer (WINDOW* cmdWin, WINDOW* infoWin, Queue * Q, Player P, ListLR AS);
/* MEMBACA INPUT AKSI DARI PLAYER
Input aksi yang diterima adalah 4 buah (1 ronde). Aksi dimasukkan secara individu. Apabila masukan salah, program akan menampilkan pesan error dan meminta kembali input Player hingga benar.
I.S: Q adalah queue of char sembarang, Player dan Acquired Skill terdefinisi.
F.S: Q berisi input aksi Player yang valid.
*/

void PrintAksiPlayer (WINDOW* win, Queue Q, int CountAksi);
/* MENAMPILKAN AKSI PLAYER
I.S: Q adalah queue of char terdefinisi, CountAksi terdefinisi sebagai penanda aksi ke-berapa.
F.S: Mencetak aksi Player per ronde (4 buah).
*/

#endif
